#include "vulkan_state.h"

static const _Float16 vertexData[] = {
  // x y u v
  (_Float16)-1.0, (_Float16)-1.0, (_Float16)0.0, (_Float16)0.0,
  (_Float16)1.0, (_Float16)-1.0, (_Float16)1.0, (_Float16)0.0,
  (_Float16)-1.0,  (_Float16)1.0, (_Float16)0.0, (_Float16)1.0,
  (_Float16)1.0,  (_Float16)1.0, (_Float16)1.0, (_Float16)1.0,
};
static const uint32_t vertexSize = (sizeof (vertexData));

static const uint16_t indexData[] = {
  0, 1, 2, 3,
};
static const uint32_t indexSize = (sizeof (indexData));


VulkanState::VulkanState(VkInstance instance,
                         VkDevice device,
                         VkQueue queue,
                         VkCommandPool commandPool,
                         VkPhysicalDeviceProperties const & physicalDeviceProperties,
                         VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                         VkFormat colorFormat,
                         VkFormat depthFormat)
  : instance(instance)
  , device(device)
  , queue(queue)
  , commandPool(commandPool)
  , physicalDeviceProperties(physicalDeviceProperties)
  , physicalDeviceMemoryProperties(physicalDeviceMemoryProperties)
  , colorFormat(colorFormat)
  , depthFormat(depthFormat)
{
  void const * vertexStart = (void const *)vertexData;
  void const * indexStart = (void const *)indexData;

  quadVertexIndex = createVertexIndexBuffer(device,
                                            physicalDeviceProperties,
                                            physicalDeviceMemoryProperties,
                                            vertexStart, vertexSize,
                                            indexStart, indexSize);
}
