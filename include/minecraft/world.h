#pragma once

#include <stdint.h>

#include "minecraft/entry_table.h"

namespace minecraft::world {
  struct vtx_cfg {
    const char * vtx;
    const char * cfg;
  };

  struct descriptor {
    int const region_count;
    vtx_cfg const * const vertex_paths;
    char const * const entry_table_path;
    char const * const lights_path;
    entry_table::hash_func_t * hash_func;
  };

  struct world_id {
    enum {
      GRANDLECTURN = 0,
      MIDNIGHTMEADOW = 1,
    };
  };

  // also update index_buffer_custom_offsets in include/minecraft_data.inc
  constexpr int custom_block_types = 7;
  constexpr int instance_cfg_length = 64 + custom_block_types;

  struct instance_cfg_entry {
    int count;
    int offset;
  };

  extern descriptor const descriptors[];
  extern int const descriptors_length;
}
