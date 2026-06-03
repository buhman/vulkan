#pragma once

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "vulkan_helper.h"

struct VulkanState {
  VkInstance instance;
  VkDevice device;
  VkQueue queue;
  VkCommandPool commandPool;
  VkPhysicalDeviceProperties physicalDeviceProperties;
  VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
  VkFormat colorFormat;
  VkFormat depthFormat;

  VertexIndex quadVertexIndex;

  VulkanState(VkInstance instance,
              VkDevice device,
              VkQueue queue,
              VkCommandPool commandPool,
              VkPhysicalDeviceProperties const & physicalDeviceProperties,
              VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
              VkFormat colorFormat,
              VkFormat depthFormat);
};
