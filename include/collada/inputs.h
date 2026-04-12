#pragma once

#include "collada/types.h"

namespace collada::inputs {
  inline static uint32_t format_size(types::input_format format)
  {
    switch (format) {
    case types::input_format::FLOAT1: return 1 * 4;
    case types::input_format::FLOAT2: return 2 * 4;
    case types::input_format::FLOAT3: return 3 * 4;
    case types::input_format::FLOAT4: return 4 * 4;
    case types::input_format::INT1: return 1 * 4;
    case types::input_format::INT2: return 2 * 4;
    case types::input_format::INT3: return 3 * 4;
    case types::input_format::INT4: return 4 * 4;
    default: assert(false);
    }
  }

  static types::input_element const input_elements_blendindices_0_4_blendweight_0_4[] = {
    {
      .semantic = "BLENDINDICES",
      .semantic_index = 0,
      .format = types::input_format::INT4,
    },
    {
      .semantic = "BLENDWEIGHT",
      .semantic_index = 0,
      .format = types::input_format::FLOAT4,
    },
  };

  static types::inputs const skin_inputs = {
    .elements = input_elements_blendindices_0_4_blendweight_0_4,
    .elements_count = 2,
  };
}
