#pragma once

#include <assert.h>

inline static constexpr VkDeviceSize roundAlignment(VkDeviceSize offset, VkDeviceSize alignment)
{
  // must be a power of two
  assert(alignment && ((alignment & (alignment - 1)) == 0));
  return (offset + (alignment - 1)) & (-alignment);
}

VkDeviceSize allocateFromMemoryRequirements(VkDevice device,
                                            VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                            VkMemoryRequirements const & memoryRequirements,
                                            VkMemoryPropertyFlags memoryPropertyFlags,
                                            VkMemoryAllocateFlags memoryAllocateFlags,
                                            uint32_t count,
                                            VkDeviceMemory * memory);
