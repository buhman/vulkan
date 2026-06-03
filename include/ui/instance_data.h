#pragma once

#include <stdint.h>
#include <assert.h>

#include "mapped_instance_data.h"

namespace ui {

  struct SolidInstance {
    uint16_2 position;
    uint16_2 size;
    uint32_t color;
  };
  static_assert((sizeof (SolidInstance)) == 2 * 2 * 2 + 4);
}
