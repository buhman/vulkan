#include <stdio.h>
#include <string.h>

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "vulkan/vk_enum_string_helper.h"

#include "new.h"
#include "file.h"
#include "check.h"
#include "vulkan_helper.h"

#include "minecraft/vulkan/per_world.h"

namespace minecraft::vulkan {

  void per_world::load_regions(VkDevice device,
                               VkPhysicalDeviceProperties const & physicalDeviceProperties,
                               VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                               world::descriptor const * const descriptor)
  {
    uint32_t * sizes = NewM<uint32_t>(descriptor->region_count);
    void const ** starts = NewM<void const *>(descriptor->region_count);

    VkMemoryRequirements * memoryRequirements = NewM<VkMemoryRequirements>(descriptor->region_count);
    for (int i = 0; i < descriptor->region_count; i++) {
      starts[i] = file::open(descriptor->vertex_paths[i].vtx, &sizes[i]);

      VkBufferCreateInfo bufferCreateInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = sizes[i],
        .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      };
      VK_CHECK(vkCreateBuffer(device, &bufferCreateInfo, nullptr, &regions[i].vertexBuffer));
      vkGetBufferMemoryRequirements(device, regions[i].vertexBuffer, &memoryRequirements[i]);
    }

    VkDeviceSize * offsets = NewM<VkDeviceSize>(descriptor->region_count);
    VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
    VkMemoryAllocateFlags memoryAllocateFlags{ };
    allocateFromMemoryRequirements2(device,
                                    physicalDeviceProperties.limits.nonCoherentAtomSize,
                                    physicalDeviceMemoryProperties,
                                    memoryPropertyFlags,
                                    memoryAllocateFlags,
                                    descriptor->region_count,
                                    memoryRequirements,
                                    &regionVertexMemory,
                                    offsets);

    VkDeviceSize offset{ 0 };
    VkDeviceSize size{ VK_WHOLE_SIZE };
    VkMemoryMapFlags flags{ 0 };
    void * mappedData;
    VK_CHECK(vkMapMemory(device, regionVertexMemory, offset, size, flags, &mappedData));

    for (int i = 0; i < descriptor->region_count; i++) {
      VK_CHECK(vkBindBufferMemory(device, regions[i].vertexBuffer, regionVertexMemory, offsets[i]));
      void * data = (void *)(((size_t)mappedData) + offsets[i]);
      memcpy(data, starts[i], sizes[i]);
    }

    VkMappedMemoryRange mappedMemoryRange{
      .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
      .memory = regionVertexMemory,
      .offset = 0,
      .size = VK_WHOLE_SIZE,
    };
    vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);

    vkUnmapMemory(device, regionVertexMemory);

    free(offsets);
    free(sizes);
    free(starts);

    // instance-cfg
    for (int i = 0; i < descriptor->region_count; i++) {
      uint32_t size;
      void const * start = file::open(descriptor->vertex_paths[i].cfg, &size);
      assert(size == (world::instance_cfg_length * (sizeof (world::instance_cfg_entry))));
      regions[i].instanceCFG = (world::instance_cfg_entry *)start;
    }
  }

  void per_world::load(VkDevice device,
                       VkPhysicalDeviceProperties const & physicalDeviceProperties,
                       VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                       world::descriptor const * const descriptor)
  {
    this->descriptor = descriptor;
    regions = NewM<region>(descriptor->region_count);
    load_regions(device,
                 physicalDeviceProperties,
                 physicalDeviceMemoryProperties,
                 descriptor);

    // collision data
    entry_table::load_entry_table(descriptor->entry_table_path,
                                  &entry_table,
                                  &entry_table_length,
                                  descriptor->hash_func);
  }
}
