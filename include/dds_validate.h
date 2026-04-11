#pragma once

#include "dds.h"

struct DDS_FILE {
  unsigned int dwMagic;
  DDS_HEADER header;
  DDS_HEADER_DXT10 header10;
};

DDS_FILE const * dds_validate(void const * data, uint32_t size, uint32_t ** out_offsets, void ** out_data);
