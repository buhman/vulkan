#include <assert.h>
#include <stdint.h>

#include "new.h"
#include "dds/validate.h"

static inline uint32_t max(uint32_t a, uint32_t b)
{
  return (a > b) ? a : b;
}

struct dds_size_levels {
  uint32_t const size;
  uint32_t const levels;
};

static inline uint32_t bc(uint32_t d)
{
  return max(4, d) / 4;
}

static inline uint32_t mip_size(DXGI_FORMAT dxgiFormat, uint32_t height, uint32_t width)
{
  switch (dxgiFormat) {
  case DXGI_FORMAT_BC1_TYPELESS: [[fallthrough]];
  case DXGI_FORMAT_BC1_UNORM: [[fallthrough]];
  case DXGI_FORMAT_BC1_UNORM_SRGB:
    return bc(height) * bc(width) * 8;
  case DXGI_FORMAT_BC3_TYPELESS: [[fallthrough]];
  case DXGI_FORMAT_BC3_UNORM: [[fallthrough]];
  case DXGI_FORMAT_BC3_UNORM_SRGB: [[fallthrough]];
  case DXGI_FORMAT_BC7_TYPELESS: [[fallthrough]];
  case DXGI_FORMAT_BC7_UNORM: [[fallthrough]];
  case DXGI_FORMAT_BC7_UNORM_SRGB:
    return bc(height) * bc(width) * 16;
  case DXGI_FORMAT_R8G8B8A8_TYPELESS: [[fallthrough]];
  case DXGI_FORMAT_R8G8B8A8_UNORM: [[fallthrough]];
  case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: [[fallthrough]];
  case DXGI_FORMAT_R8G8B8A8_UINT: [[fallthrough]];
  case DXGI_FORMAT_R8G8B8A8_SNORM: [[fallthrough]];
  case DXGI_FORMAT_R8G8B8A8_SINT:
    return height * width * 4;
  default:
    assert(false);
  }
}

static inline dds_size_levels dds_mip_total_size(DXGI_FORMAT dxgiFormat,
                                                 uint32_t height,
                                                 uint32_t width,
                                                 uint32_t max_mip_levels,
                                                 uint32_t * offsets)
{
  uint32_t mip_total_size = 0;
  uint32_t mip_levels = 0;
  while (true) {
    offsets[mip_levels] = mip_total_size;
    mip_levels += 1;
    assert(mip_levels <= max_mip_levels);

    uint32_t mip_offset = mip_size(dxgiFormat, height, width);
    mip_total_size += mip_offset;

    if (max_mip_levels == 1 || (width == 1 && height == 1))
      break;

    height = max(1, height / 2);
    width = max(1, width / 2);
  }

  return {mip_total_size, mip_levels};
}

namespace dds {
  DDS_FILE const * validate(void const * data, uint32_t size, uint32_t ** out_offsets, void ** out_data, uint32_t * out_size)
  {
    DDS_FILE const * const dds = (DDS_FILE const *)data;
    assert(dds->dwMagic == DDS_MAGIC);
    assert(dds->header.dwSize == 124);
    assert(dds->header.ddspf.dwSize == 32);
    assert(dds->header.ddspf.dwFlags == DDS_FOURCC);
    //assert(dds->header.ddspf.dwFourCC == MAKEFOURCC('D','X','T','1'));
    assert(dds->header.ddspf.dwFourCC == MAKEFOURCC('D','X','1','0'));

    uint32_t * offsets = NewM<uint32_t>(dds->header.dwMipMapCount);

    uintptr_t image_data = ((uintptr_t)dds) + (sizeof (DDS_FILE));
    dds_size_levels ret = dds_mip_total_size(dds->header10.dxgiFormat,
                                             dds->header.dwHeight,
                                             dds->header.dwWidth,
                                             dds->header.dwMipMapCount,
                                             offsets);
    assert(ret.size + (sizeof (DDS_FILE)) == size);
    assert(ret.levels == dds->header.dwMipMapCount);

    *out_offsets = offsets;
    *out_data = (void *)image_data;
    *out_size = ret.size;
    return dds;
  }
}
