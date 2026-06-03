#pragma once

#include "vulkan_state.h"
#include "font/instance_data.h"

namespace font::bitmap {
  struct LoadedFont {
    VkImage image;
    VkDeviceMemory memory;
    VkImageView imageView;
  };

  struct vulkan {
    static constexpr int maximumGlyphCount = 1024;
    static constexpr VkDeviceSize instanceBufferSize{ maximumGlyphCount * (sizeof (BitmapInstance)) };

    VulkanState const * const vk;

    VkPipelineLayout pipelineLayout;
    VkPipeline pipeline;
    ::InstanceBuffer instanceBuffer;
    BitmapInstance * bitmapInstance[2];

    VkDescriptorPool descriptorPool;
    static constexpr uint32_t descriptorSetLayoutCount = 1;
    VkDescriptorSetLayout descriptorSetLayouts[descriptorSetLayoutCount];
    VkDescriptorSet descriptorSet0;

    LoadedFont loadedFont;

    vulkan(VulkanState const * vk)
      : vk(vk)
    {
      createDescriptorSets();
      createPipeline();

      loadedFont = loadFont();
      writeDescriptorSets(loadedFont.imageView);

      createInstanceBuffer(vk->device,
                           vk->physicalDeviceProperties,
                           vk->physicalDeviceMemoryProperties,
                           instanceBufferSize,
                           &instanceBuffer);

      bitmapInstance[0] = (BitmapInstance *)(((ptrdiff_t)instanceBuffer.mappedData) + instanceBuffer.offset[0]);
      bitmapInstance[1] = (BitmapInstance *)(((ptrdiff_t)instanceBuffer.mappedData) + instanceBuffer.offset[1]);
    }

    LoadedFont loadFont();
    void createDescriptorSets();
    void writeDescriptorSets(VkImageView imageView);

    void update(uint32_t frameIndex,
                uint32_t glyphCount) const;

    void draw(VkCommandBuffer commandBuffer,
              uint32_t frameIndex,
              uint32_t glyphCount) const;

  private:
    void createPipeline();
  };
}
