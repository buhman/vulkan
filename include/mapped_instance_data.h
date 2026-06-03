#pragma once

#include <stdint.h>

struct uint16_2 {
  uint16_t x;
  uint16_t y;
};

template <typename T>
struct MappedInstanceData {
  T * buffer;
  int length;
  int index;

  void append(T const & value)
  {
    assert(index < length);
    buffer[index] = value;
    index += 1;
  }
};
