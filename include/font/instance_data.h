#pragma once

#include <stdint.h>
#include <assert.h>

#include "mapped_instance_data.h"

namespace font {

  struct BitmapInstance {
    uint16_2 position;
    uint16_2 glyph;
  };
  static_assert((sizeof (BitmapInstance)) == 2 * 2 + 4);
}
