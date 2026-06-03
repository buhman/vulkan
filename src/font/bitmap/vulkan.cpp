#include <stdio.h>

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "vulkan/vk_enum_string_helper.h"

#include "vulkan_helper.h"
#include "check.h"
#include "file.h"

#include "font/bitmap/vulkan.h"

namespace font::bitmap {

  //////////////////////////////////////////////////////////////////////
  // pipeline
  //////////////////////////////////////////////////////////////////////

  void vulkan::createPipeline()
  {
    uint32_t pushConstantRangeCount = 0;
    VkPushConstantRange const * pushConstantRanges = nullptr;
    VkShaderModule shaderModule = loadShader(vk->device, "shader/font/bitmap.spv");
    uint32_t perInstanceStride = (sizeof (BitmapInstance));
    constexpr uint32_t instanceAttributeDescriptionCount = 2;
    VkVertexInputAttributeDescription instanceAttributeDescriptions[instanceAttributeDescriptionCount] {
      { // position
        .location = 2,
        .binding = 1,
        .format = VK_FORMAT_R16G16_UINT,
        .offset = 0,
      },
      { // glyph
        .location = 3,
        .binding = 1,
        .format = VK_FORMAT_R16G16_UINT,
        .offset = 4,
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

  //////////////////////////////////////////////////////////////////////
  // descriptor sets
  //////////////////////////////////////////////////////////////////////

  void vulkan::createDescriptorSets()
  {
    //
    // pool
    //
    constexpr int descriptorPoolSizesCount = 1;
    VkDescriptorPoolSize descriptorPoolSizes[descriptorPoolSizesCount]{
      {
        .type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
        .descriptorCount = 1,
      },
    };
    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .maxSets = 1,
      .poolSizeCount = descriptorPoolSizesCount,
      .pPoolSizes = descriptorPoolSizes
    };
    VK_CHECK(vkCreateDescriptorPool(vk->device, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

    //
    // (set 0, constant)
    //
    {
      constexpr int bindingCount = 1;
      VkDescriptorSetLayoutBinding descriptorSetLayoutBindings[bindingCount]{
        { // font image
          .binding = 0,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
      };

      VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = bindingCount,
        .pBindings = descriptorSetLayoutBindings
      };
      VK_CHECK(vkCreateDescriptorSetLayout(vk->device, &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayouts[0]));

      VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &descriptorSetLayouts[0]
      };
      VK_CHECK(vkAllocateDescriptorSets(vk->device, &descriptorSetAllocateInfo, &descriptorSet0));
    }
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor set writes
  //////////////////////////////////////////////////////////////////////

  void vulkan::writeDescriptorSets(VkImageView imageView)
  {
    constexpr uint32_t writeCount = 1;
    VkWriteDescriptorSet writeDescriptorSets[writeCount];
    uint32_t writeIndex = 0;

    // set0 bindings
    VkDescriptorImageInfo terrainDescriptorImageInfo = {
      .imageView = imageView,
      .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet0,
      .dstBinding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
      .pImageInfo = &terrainDescriptorImageInfo
    };

    assert(writeIndex == writeCount);
    vkUpdateDescriptorSets(vk->device, writeIndex, writeDescriptorSets, 0, nullptr);
  }

  //////////////////////////////////////////////////////////////////////
  // load font
  //////////////////////////////////////////////////////////////////////

  LoadedFont vulkan::loadFont()
  {
    uint32_t font_data_size;
    void const * font_data = file::open("data/font/bitmap/terminus_128x64_6x12.data", &font_data_size);
    assert(font_data != nullptr);

    void const * texture_data = font_data;
    uint32_t texture_size = font_data_size;
    uint32_t texture_width = 128;
    uint32_t texture_height = 64;

    // transfer texture

    VkCommandBuffer commandBuffer{};
    VkCommandBufferAllocateInfo commandBufferAllocateInfo{
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .commandPool = vk->commandPool,
      .commandBufferCount = 1
    };
    VK_CHECK(vkAllocateCommandBuffers(vk->device, &commandBufferAllocateInfo, &commandBuffer));

    VkFenceCreateInfo fenceCreateInfo{
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
    };
    VkFence fence{};
    VK_CHECK(vkCreateFence(vk->device, &fenceCreateInfo, nullptr, &fence));

    void const * imageData = texture_data;
    uint32_t imageDataSize = texture_size;
    VkFormat format = VK_FORMAT_R8_UNORM;
    uint32_t width = texture_width;
    uint32_t height = texture_height;
    uint32_t levelCount = 1;
    uint32_t levelOffset = 0;
    VkImage outImage;
    VkDeviceMemory outMemory;
    VkImageView outImageView;

    createImage(vk->device,
                vk->physicalDeviceProperties.limits.nonCoherentAtomSize,
                vk->physicalDeviceMemoryProperties,
                format,
                width,
                height,
                levelCount,
                &outImage,
                &outMemory,
                &outImageView);

    textureTransfer(vk->device,
                    vk->queue,
                    commandBuffer,
                    fence,
                    vk->physicalDeviceProperties.limits.nonCoherentAtomSize,
                    vk->physicalDeviceMemoryProperties,
                    imageDataSize,
                    imageData,
                    outImage,
                    width,
                    height,
                    levelCount,
                    &levelOffset);

    vkDestroyFence(vk->device, fence, nullptr);
    vkFreeCommandBuffers(vk->device,
                         vk->commandPool,
                         1,
                         &commandBuffer);

    // return
    return {
      .image = outImage,
      .memory = outMemory,
      .imageView = outImageView,
    };
  }

  void vulkan::update(uint32_t frameIndex, uint32_t glyphCount) const
  {
    constexpr int mappedMemoryRangesCount = 1;
    VkMappedMemoryRange mappedMemoryRanges[mappedMemoryRangesCount]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = instanceBuffer.memory,
        .offset = instanceBuffer.offset[frameIndex],
        .size = (sizeof (BitmapInstance)) * glyphCount,
      }
    };
    alignMappedMemoryRanges(vk->physicalDeviceProperties.limits.nonCoherentAtomSize,
                            instanceBuffer.memorySize,
                            mappedMemoryRangesCount,
                            mappedMemoryRanges);
    vkFlushMappedMemoryRanges(vk->device, mappedMemoryRangesCount, mappedMemoryRanges);
  }

  void vulkan::draw(VkCommandBuffer commandBuffer,
                    uint32_t frameIndex,
                    uint32_t glyphCount) const
  {
    update(frameIndex, glyphCount);
    //
    uint32_t outputIndex = glyphCount;

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

    VkDescriptorSet descriptorSets[1] = {
      descriptorSet0,
    };
    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipelineLayout,
                            0, 1, descriptorSets,
                            0, nullptr);

    vkCmdBindIndexBuffer(commandBuffer, vk->quadVertexIndex.buffer, vk->quadVertexIndex.indexOffset, VK_INDEX_TYPE_UINT16);

    VkDeviceSize vertexOffsets[2]{ 0, instanceBuffer.offset[frameIndex] };
    VkBuffer vertexBuffers[2]{ vk->quadVertexIndex.buffer, instanceBuffer.buffer };
    vkCmdBindVertexBuffers(commandBuffer, 0, 2, vertexBuffers, vertexOffsets);

    vkCmdDrawIndexed(commandBuffer, 4, outputIndex, 0, 0, 0);
  }
}
