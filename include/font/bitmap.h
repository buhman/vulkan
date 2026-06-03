#pragma once

#include "instance_data.h"

namespace font::bitmap {
  static inline uint16_2 glyphIndex(int c)
  {
    assert(c >= 32 && c <= 127);

    c -= 32;

    int stride = 128 / 6;

    int x = c % stride;
    int y = c / stride;
    return {(uint16_t)x, (uint16_t)y};
  }
}
