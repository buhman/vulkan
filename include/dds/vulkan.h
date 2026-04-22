#pragma once

#include <assert.h>

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "dds/dds.h"

namespace dds {
  inline constexpr VkFormat dxgi_to_vulkan(DXGI_FORMAT dxgiFormat)
  {
    switch (dxgiFormat) {
    case DXGI_FORMAT_BC1_UNORM: return VK_FORMAT_BC1_RGB_UNORM_BLOCK;
    case DXGI_FORMAT_BC1_UNORM_SRGB: return VK_FORMAT_BC1_RGB_SRGB_BLOCK;
    case DXGI_FORMAT_BC3_UNORM: return VK_FORMAT_BC3_UNORM_BLOCK;
    case DXGI_FORMAT_BC3_UNORM_SRGB: return VK_FORMAT_BC3_SRGB_BLOCK;
    case DXGI_FORMAT_BC7_UNORM: return VK_FORMAT_BC7_UNORM_BLOCK;
    case DXGI_FORMAT_BC7_UNORM_SRGB: return VK_FORMAT_BC7_SRGB_BLOCK;
    case DXGI_FORMAT_R8G8B8A8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return VK_FORMAT_B8G8R8A8_SRGB;
    case DXGI_FORMAT_R8G8B8A8_UINT: return VK_FORMAT_R8G8B8A8_UINT;
    case DXGI_FORMAT_R8G8B8A8_SNORM: return VK_FORMAT_R8G8B8A8_SNORM;
    case DXGI_FORMAT_R8G8B8A8_SINT: return VK_FORMAT_R8G8B8A8_SINT;
    default:
      assert(false);
    }
  }
}
