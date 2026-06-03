#pragma once

#include "vulkan_state.h"
#include "ui/instance_data.h"

#include "font/instance_data.h"

namespace ui {
  struct vulkan {
    static constexpr int maximumUIElements = 1024;
    static constexpr VkDeviceSize instanceBufferSize{ maximumUIElements * (sizeof (SolidInstance)) };

    VulkanState const * const vk;

    VkPipelineLayout pipelineLayout;
    VkPipeline pipeline;
    ::InstanceBuffer instanceBuffer;
    SolidInstance * solidInstance[2];

    vulkan(VulkanState const * vk)
      : vk(vk)
    {
      createPipeline();

      createInstanceBuffer(vk->device,
                           vk->physicalDeviceProperties,
                           vk->physicalDeviceMemoryProperties,
                           instanceBufferSize,
                           &instanceBuffer);

      solidInstance[0] = (SolidInstance *)(((ptrdiff_t)instanceBuffer.mappedData) + instanceBuffer.offset[0]);
      solidInstance[1] = (SolidInstance *)(((ptrdiff_t)instanceBuffer.mappedData) + instanceBuffer.offset[1]);
    }

    int update(uint32_t frameIndex,
               MappedInstanceData<font::BitmapInstance> & bitmapData) const;

    void draw(VkCommandBuffer commandBuffer,
              uint32_t frameIndex,
              MappedInstanceData<font::BitmapInstance> & bitmapData) const;

  private:
    void createPipeline();
  };
}
