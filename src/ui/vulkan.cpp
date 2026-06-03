#include <stdio.h>

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "vulkan_helper.h"

#include "ui/vulkan.h"
#include "ui/instance_data.h"
#include "ui.h"

#include "font/bitmap.h"

namespace ui {

  void vulkan::createPipeline()
  {
    uint32_t descriptorSetLayoutCount = 0;
    VkDescriptorSetLayout const * descriptorSetLayouts = nullptr;
    uint32_t pushConstantRangeCount = 0;
    VkPushConstantRange const * pushConstantRanges = nullptr;
    VkShaderModule shaderModule = loadShader(vk->device, "shader/ui/solid.spv");
    uint32_t perInstanceStride = (sizeof (SolidInstance));
    constexpr uint32_t instanceAttributeDescriptionCount = 3;
    VkVertexInputAttributeDescription instanceAttributeDescriptions[instanceAttributeDescriptionCount] {
      { // position
        .location = 2,
        .binding = 1,
        .format = VK_FORMAT_R16G16_UINT,
        .offset = 0,
      },
      { // size
        .location = 3,
        .binding = 1,
        .format = VK_FORMAT_R16G16_UINT,
        .offset = 4,
      },
      { // color
        .location = 4,
        .binding = 1,
        .format = VK_FORMAT_R8G8B8A8_UNORM,
        .offset = 8,
      },
    };

    createQuadPipeline(vk->device,
                       vk->colorFormat,
                       vk->depthFormat,
                       descriptorSetLayoutCount,
                       descriptorSetLayouts,
                       pushConstantRangeCount,
                       pushConstantRanges,
                       shaderModule,
                       perInstanceStride,
                       instanceAttributeDescriptionCount,
                       instanceAttributeDescriptions,
                       &pipelineLayout,
                       &pipeline);
  }

  int vulkan::update(uint32_t frameIndex, MappedInstanceData<font::BitmapInstance> & bitmapData) const
  {
    MappedInstanceData<SolidInstance> solidData{ solidInstance[frameIndex], maximumUIElements, 0 };
    ui::draw(solidData, bitmapData);

    //////////////////////////////////////////////////////////////////////
    // flush
    //////////////////////////////////////////////////////////////////////

    constexpr int mappedMemoryRangesCount = 1;
    VkMappedMemoryRange mappedMemoryRanges[mappedMemoryRangesCount]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = instanceBuffer.memory,
        .offset = instanceBuffer.offset[frameIndex],
        .size = (sizeof (SolidInstance)) * solidData.index,
      }
    };
    alignMappedMemoryRanges(vk->physicalDeviceProperties.limits.nonCoherentAtomSize,
                            instanceBuffer.memorySize,
                            mappedMemoryRangesCount,
                            mappedMemoryRanges);
    vkFlushMappedMemoryRanges(vk->device, mappedMemoryRangesCount, mappedMemoryRanges);

    return solidData.index;
  }

  void vulkan::draw(VkCommandBuffer commandBuffer,
                    uint32_t frameIndex,
                    MappedInstanceData<font::BitmapInstance> & bitmapData) const
  {
    int outputIndex = update(frameIndex, bitmapData);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

    /*
    VkDescriptorSet descriptorSets[1] = {
      descriptorSet0,
    };
    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipelineLayout,
                            0, 1, descriptorSets,
                            0, nullptr);
    */

    vkCmdBindIndexBuffer(commandBuffer, vk->quadVertexIndex.buffer, vk->quadVertexIndex.indexOffset, VK_INDEX_TYPE_UINT16);

    VkDeviceSize vertexOffsets[2]{ 0, instanceBuffer.offset[frameIndex] };
    VkBuffer vertexBuffers[2]{ vk->quadVertexIndex.buffer, instanceBuffer.buffer };
    vkCmdBindVertexBuffers(commandBuffer, 0, 2, vertexBuffers, vertexOffsets);

    vkCmdDrawIndexed(commandBuffer, 4, outputIndex, 0, 0, 0);
  }
}
