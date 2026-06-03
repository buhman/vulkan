#pragma once

#include <assert.h>

inline static constexpr VkDeviceSize roundDownAlignment(VkDeviceSize offset, VkDeviceSize alignment)
{
  // must be a power of two
  assert(alignment && ((alignment & (alignment - 1)) == 0));
  return offset & ~(alignment - 1);
}

inline static constexpr VkDeviceSize roundAlignment(VkDeviceSize offset, VkDeviceSize alignment)
{
  // must be a power of two
  assert(alignment && ((alignment & (alignment - 1)) == 0));
  return (offset + (alignment - 1)) & (-alignment);
}

inline static constexpr void alignMappedMemoryRanges(uint32_t nonCoherentAtomSize,
                                                     VkDeviceSize memorySize,
                                                     uint32_t count,
                                                     VkMappedMemoryRange * ranges)
{
  for (uint32_t i = 0; i < count; i++) {
    VkDeviceSize alignedOffset{ roundDownAlignment(ranges[i].offset, nonCoherentAtomSize) };
    VkDeviceSize alignedSize{ roundAlignment(ranges[i].size + (ranges[i].offset - alignedOffset), nonCoherentAtomSize) };
    if (alignedOffset + alignedSize > memorySize) {
      alignedSize = VK_WHOLE_SIZE;
    }
    ranges[i].offset = alignedOffset;
    ranges[i].size = alignedSize;
  }
}

VkDeviceSize allocateFromMemoryRequirements(VkDevice device,
                                            VkDeviceSize nonCoherentAtomSize,
                                            VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                            VkMemoryRequirements const & memoryRequirements,
                                            VkMemoryPropertyFlags memoryPropertyFlags,
                                            VkMemoryAllocateFlags memoryAllocateFlags,
                                            uint32_t count,
                                            VkDeviceMemory * memory,
                                            VkDeviceSize * stride);

VkDeviceSize allocateFromMemoryRequirements2(VkDevice device,
                                             VkDeviceSize nonCoherentAtomSize,
                                             VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                             VkMemoryPropertyFlags memoryPropertyFlags,
                                             VkMemoryAllocateFlags memoryAllocateFlags,
                                             uint32_t memoryRequirementsCount,
                                             VkMemoryRequirements const * memoryRequirements,
                                             VkDeviceMemory * memory,
                                             VkDeviceSize * offsets);

void createImageFromFilenameDDS(VkDevice device,
                                VkQueue queue,
                                VkCommandBuffer commandBuffer,
                                VkFence fence,
                                VkDeviceSize nonCoherentAtomSize,
                                VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                char const * const filename,
                                VkImage * outImage,
                                VkDeviceMemory * outMemory,
                                VkImageView * outImageView,
                                int * width,
                                int * height);

void createImageFromFilenameTGA(VkDevice device,
                                VkQueue queue,
                                VkCommandBuffer commandBuffer,
                                VkFence fence,
                                VkDeviceSize nonCoherentAtomSize,
                                VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                char const * const filename,
                                VkImage * outImage,
                                VkDeviceMemory * outMemory,
                                VkImageView * outImageView);

void createImage(VkDevice device,
                 VkDeviceSize nonCoherentAtomSize,
                 VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                 VkFormat format,
                 uint32_t width,
                 uint32_t height,
                 uint32_t levelCount,
                 VkImage * outImage,
                 VkDeviceMemory * outMemory,
                 VkImageView * outImageView);

void textureTransfer(VkDevice device,
                     VkQueue queue,
                     VkCommandBuffer commandBuffer,
                     VkFence fence,
                     VkDeviceSize nonCoherentAtomSize,
                     VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                     uint32_t imageDataSize,
                     void const * imageData,
                     VkImage image,
                     uint32_t width,
                     uint32_t height,
                     uint32_t levelCount,
                     uint32_t * levelOffsets);

struct VertexIndex {
  VkDeviceSize indexOffset;
  VkBuffer buffer;
  VkDeviceMemory memory;
};

VertexIndex createVertexIndexBuffer(VkDevice device,
                                    VkPhysicalDeviceProperties const& physicalDeviceProperties,
                                    VkPhysicalDeviceMemoryProperties const& physicalDeviceMemoryProperties,
                                    void const * vertexStart,
                                    uint32_t vertexSize,
                                    void const * indexStart,
                                    uint32_t indexSize);

void createQuadPipeline(VkDevice device,
                        VkFormat colorFormat,
                        VkFormat depthFormat,
                        uint32_t descriptorSetLayoutCount,
                        VkDescriptorSetLayout const * descriptorSetLayouts,
                        uint32_t pushConstantRangeCount,
                        VkPushConstantRange const * pushConstantRanges,
                        VkShaderModule shaderModule,
                        uint32_t perInstanceStride,
                        uint32_t instanceAttributeDescriptionCount,
                        VkVertexInputAttributeDescription * instanceAttributeDescriptions,
                        VkPipelineLayout * pipelineLayout,
                        VkPipeline * pipeline);

VkShaderModule loadShader(VkDevice device,
                          char const * const path);

struct InstanceBuffer {
  VkDeviceSize offset[2];
  VkBuffer buffer;
  VkDeviceMemory memory;
  VkDeviceSize memorySize;
  void * mappedData;
};

void createInstanceBuffer(VkDevice device,
                          VkPhysicalDeviceProperties const & physicalDeviceProperties,
                          VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                          VkDeviceSize bufferSize,
                          InstanceBuffer * instanceBuffer);
