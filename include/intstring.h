#pragma once

#include <stdint.h>
#include <assert.h>

namespace string {
  static inline int decLength(int32_t n)
  {
    if (n >= 1000000000) return 10;
    if (n >= 100000000) return 9;
    if (n >= 10000000) return 8;
    if (n >= 1000000) return 7;
    if (n >= 100000) return 6;
    if (n >= 10000) return 5;
    if (n >= 1000) return 4;
    if (n >= 100) return 3;
    if (n >= 10) return 2;
    return 1;
  }

  template <typename T, int fixed=0>
  static inline int dec(T * c, int len, int32_t n)
  {
    int index = 0;
    if (n < 0) {
      c[index++] = '-';
      n = -n;
    }
    int numLength = fixed > 0 ? fixed : decLength(n);
    assert(len >= (numLength + index));
    for (int i = (numLength - 1); i >= 0; i--) {
      const int32_t digit = n % 10;
      n = n / 10;
      c[index + i] = digit + 48;
    }
    return numLength + index;
  }

  template <typename T>
  static inline int flt(T * c, int len, float n)
  {
    int index = 0;
    if (n < 0) {
      c[index++] = '-';
      n = -n;
    }
    int32_t whole = n;
    index += dec<T>(&c[index], len - index, whole);
    c[index++] = '.';
    int32_t fraction = (int32_t)((n - (float)whole) * 1000.0f);
    index += dec<T, 3>(&c[index], len - index, fraction);
    return index;
  }
}
