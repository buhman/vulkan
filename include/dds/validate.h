#pragma once

#include "dds/dds.h"

struct DDS_FILE {
  unsigned int dwMagic;
  DDS_HEADER header;
  DDS_HEADER_DXT10 header10;
};

namespace dds {
  DDS_FILE const * validate(void const * data, uint32_t size, uint32_t ** out_offsets, void ** out_data, uint32_t * out_size);
}
