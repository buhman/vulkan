#pragma once

#include <stdint.h>

namespace file {
  void const * open(char const * filename, uint32_t * out_size);

  void * openRelative(char const * filename, uint32_t * out_size);
}
