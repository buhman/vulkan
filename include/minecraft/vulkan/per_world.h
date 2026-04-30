#pragma once

#include "minecraft/world.h"

namespace minecraft::vulkan {
  struct region {
    VkBuffer vertexBuffer;
    world::instance_cfg_entry * instanceCFG;
  };

  struct per_world {
    world::descriptor const * descriptor;
    region * regions; // malloc region_count
    VkDeviceMemory regionVertexMemory;
    entry_table::global_entry_t * entry_table;
    int entry_table_length;

    void load_regions(VkDevice device,
                      VkPhysicalDeviceProperties const & physicalDeviceProperties,
                      VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                      world::descriptor const * const descriptor);
    void load(VkDevice device,
              VkPhysicalDeviceProperties const & physicalDeviceProperties,
              VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
              world::descriptor const * const descriptor);
  };
}
