#include <stdio.h>
#include <stdlib.h>

#include "volk/volk.h"
#include "vulkan/vk_enum_string_helper.h"

#include "check.h"

#include "vulkan_helper.h"

inline static uint32_t findMemoryTypeIndex(VkPhysicalDeviceMemoryProperties const & memoryProperties, uint32_t memoryTypeBits, VkMemoryPropertyFlags propertyFlags)
{
  // find an exact match
  for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
    if (!(memoryTypeBits & (1u << i)))
      continue;

    if (memoryProperties.memoryTypes[i].propertyFlags == propertyFlags) {
      return i;
    }
  }

  // find a partial match
  for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
    if (!(memoryTypeBits & (1u << i)))
      continue;

    if ((memoryProperties.memoryTypes[i].propertyFlags & propertyFlags) == propertyFlags) {
      return i;
    }
  }

  ASSERT(false, "no memory type index matching memoryTypeBits and propertyFlags");
  UNREACHABLE();
}

VkDeviceSize allocateFromMemoryRequirements(VkDevice device,
                                            VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                            VkMemoryRequirements const & memoryRequirements,
                                            VkMemoryPropertyFlags memoryPropertyFlags,
                                            VkMemoryAllocateFlags memoryAllocateFlags,
                                            uint32_t count,
                                            VkDeviceMemory * memory)
{
  uint32_t memoryTypeIndex = findMemoryTypeIndex(physicalDeviceMemoryProperties,
                                                 memoryRequirements.memoryTypeBits,
                                                 memoryPropertyFlags);

  VkDeviceSize stride = (count == 1) ? memoryRequirements.size : roundAlignment(memoryRequirements.size, memoryRequirements.alignment);

  VkMemoryAllocateFlagsInfo memoryAllocateFlagsInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
    .flags = memoryAllocateFlags,
  };
  VkMemoryAllocateInfo memoryAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext = &memoryAllocateFlagsInfo,
    .allocationSize = stride * count,
    .memoryTypeIndex = memoryTypeIndex,
  };
  VK_CHECK(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, memory));

  return stride;
}
