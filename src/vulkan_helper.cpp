#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "vulkan/vulkan.h"
#include "vulkan/vk_enum_string_helper.h"

#include "minmax.h"
#include "new.h"
#include "file.h"
#include "check.h"

#include "dds/validate.h"
#include "dds/vulkan.h"
#include "tga/tga.h"

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
                                            VkDeviceSize nonCoherentAtomSize,
                                            VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                            VkMemoryRequirements const & memoryRequirements,
                                            VkMemoryPropertyFlags memoryPropertyFlags,
                                            VkMemoryAllocateFlags memoryAllocateFlags,
                                            uint32_t count,
                                            VkDeviceMemory * memory,
                                            VkDeviceSize * outStride)
{
  uint32_t memoryTypeIndex = findMemoryTypeIndex(physicalDeviceMemoryProperties,
                                                 memoryRequirements.memoryTypeBits,
                                                 memoryPropertyFlags);

  VkDeviceSize alignedSize = roundAlignment(memoryRequirements.size, memoryRequirements.alignment);
  VkDeviceSize stride = (count == 1) ? memoryRequirements.size : alignedSize;

  VkMemoryAllocateFlagsInfo memoryAllocateFlagsInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
    .flags = memoryAllocateFlags,
  };
  VkMemoryAllocateInfo memoryAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext = &memoryAllocateFlagsInfo,
    .allocationSize = roundAlignment(stride * count, nonCoherentAtomSize),
    .memoryTypeIndex = memoryTypeIndex,
  };
  VK_CHECK(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, memory));

  *outStride = stride;
  return memoryAllocateInfo.allocationSize;
}

VkDeviceSize allocateFromMemoryRequirements2(VkDevice device,
                                             VkDeviceSize nonCoherentAtomSize,
                                             VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                             VkMemoryPropertyFlags memoryPropertyFlags,
                                             VkMemoryAllocateFlags memoryAllocateFlags,
                                             uint32_t memoryRequirementsCount,
                                             VkMemoryRequirements const * memoryRequirements,
                                             VkDeviceMemory * memory,
                                             VkDeviceSize * offsets)
{
  assert(memoryRequirementsCount > 0);
  uint32_t memoryTypeBits = memoryRequirements[0].memoryTypeBits;
  for (uint32_t i = 1; i < memoryRequirementsCount; i++) {
    assert(memoryRequirements[i].memoryTypeBits == memoryTypeBits);
  }
  uint32_t memoryTypeIndex = findMemoryTypeIndex(physicalDeviceMemoryProperties,
                                                 memoryTypeBits,
                                                 memoryPropertyFlags);
  VkDeviceSize offset = 0;
  for (uint32_t i = 0; i < memoryRequirementsCount; i++) {
    offset = roundAlignment(offset, memoryRequirements[i].alignment);
    offsets[i] = offset;
    offset += memoryRequirements[i].size;
  }

  VkMemoryAllocateFlagsInfo memoryAllocateFlagsInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
    .flags = memoryAllocateFlags,
  };
  VkMemoryAllocateInfo memoryAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext = &memoryAllocateFlagsInfo,
    .allocationSize = roundAlignment(offset, nonCoherentAtomSize),
    .memoryTypeIndex = memoryTypeIndex,
  };
  VK_CHECK(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, memory));

  return memoryAllocateInfo.allocationSize;
}

// ddsFile->header.dwWidth
// ddsFile->header.dwHeight
// ddsFile->header.dwMipMapCount
// uint32_t * mipOffsets;

void textureTransfer(VkDevice device,
                     VkQueue queue,
                     VkCommandBuffer commandBuffer,
                     VkFence fence,
                     VkDeviceSize nonCoherentAtomSize,
                     VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                     uint32_t imageDataSize,
                     void * imageData,
                     VkImage image,
                     uint32_t width,
                     uint32_t height,
                     uint32_t levelCount,
                     uint32_t * levelOffsets)
{
  VkBuffer sourceBuffer{};
  VkBufferCreateInfo sourceBufferCreateInfo{
    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .size = imageDataSize,
    .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT
  };
  VK_CHECK(vkCreateBuffer(device, &sourceBufferCreateInfo, nullptr, &sourceBuffer));
  VkMemoryRequirements sourceBufferMemoryRequirements;
  vkGetBufferMemoryRequirements(device, sourceBuffer, &sourceBufferMemoryRequirements);
  VkMemoryPropertyFlags sourceBufferMemoryPropertyFlags{
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
  };
  VkMemoryAllocateFlags sourceBufferMemoryAllocateFlags{ };
  VkDeviceMemory sourceBufferMemory;
  VkDeviceSize sourceBufferStride;
  allocateFromMemoryRequirements(device,
                                 nonCoherentAtomSize,
                                 physicalDeviceMemoryProperties,
                                 sourceBufferMemoryRequirements,
                                 sourceBufferMemoryPropertyFlags,
                                 sourceBufferMemoryAllocateFlags,
                                 1,
                                 &sourceBufferMemory,
                                 &sourceBufferStride);
  VK_CHECK(vkBindBufferMemory(device, sourceBuffer, sourceBufferMemory, 0));

  void * sourceMappedData;
  VK_CHECK(vkMapMemory(device, sourceBufferMemory, 0, sourceBufferCreateInfo.size, 0, &sourceMappedData));
  memcpy((void *)(((ptrdiff_t)sourceMappedData) + 0), imageData, imageDataSize);
  vkUnmapMemory(device, sourceBufferMemory);

  // transfer: command buffer

  VkCommandBufferBeginInfo commandBufferBeginInfo{
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
  };
  VK_CHECK(vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo));
  VkImageMemoryBarrier2 imageBarrier{
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
    .srcStageMask = VK_PIPELINE_STAGE_2_NONE,
    .srcAccessMask = VK_ACCESS_2_NONE,
    .dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
    .dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
    .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    .image = image,
    .subresourceRange = {
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .levelCount = levelCount,
      .layerCount = 1
    }
  };
  VkDependencyInfo imageDependencyInfo{
    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
    .imageMemoryBarrierCount = 1,
    .pImageMemoryBarriers = &imageBarrier
  };
  vkCmdPipelineBarrier2(commandBuffer, &imageDependencyInfo);
  VkBufferImageCopy * copyRegions = NewM<VkBufferImageCopy>(levelCount);
  for (uint32_t level = 0; level < levelCount; level++) {
    copyRegions[level] = {
      .bufferOffset = levelOffsets[level],
      .imageSubresource{
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = level,
        .layerCount = 1
      },
      .imageExtent{
        .width = max(1u, width >> level),
        .height = max(1u, height >> level),
        .depth = 1
      },
    };
  }
  vkCmdCopyBufferToImage(commandBuffer, sourceBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, levelCount, copyRegions);
  free(copyRegions);

  VkImageMemoryBarrier2 readBarrier{
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
    .srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT,
    .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
    .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
    .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
    .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    .newLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL,
    .image = image,
    .subresourceRange = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .levelCount = levelCount, .layerCount = 1 }
  };
  VkDependencyInfo readDependencyInfo{
    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
    .imageMemoryBarrierCount = 1,
    .pImageMemoryBarriers = &readBarrier
  };
  vkCmdPipelineBarrier2(commandBuffer, &readDependencyInfo);

  VK_CHECK(vkEndCommandBuffer(commandBuffer));

  vkResetFences(device, 1, &fence);
  VkSubmitInfo submitInfo{
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .commandBufferCount = 1,
    .pCommandBuffers = &commandBuffer
  };
  VK_CHECK(vkQueueSubmit(queue, 1, &submitInfo, fence));
  VK_CHECK(vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX));

  vkDestroyBuffer(device, sourceBuffer, nullptr);
  vkFreeMemory(device, sourceBufferMemory, nullptr);
}

void createImage(VkDevice device,
                 VkDeviceSize nonCoherentAtomSize,
                 VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                 VkFormat format,
                 uint32_t width,
                 uint32_t height,
                 uint32_t levelCount,
                 VkImage * outImage,
                 VkDeviceMemory * outMemory,
                 VkImageView * outImageView)
{
  // image

  VkImage image;
  VkImageCreateInfo imageCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = format,
    .extent = {
      .width = width,
      .height = height,
      .depth = 1
    },
    .mipLevels = levelCount,
    .arrayLayers = 1,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .tiling = VK_IMAGE_TILING_OPTIMAL,
    .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
  };
  VK_CHECK(vkCreateImage(device, &imageCreateInfo, nullptr, &image));
  *outImage = image;

  // image view

  VkDeviceMemory imageMemory;
  VkMemoryRequirements imageMemoryRequirements;
  vkGetImageMemoryRequirements(device, image, &imageMemoryRequirements);
  VkMemoryPropertyFlags imageMemoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT };
  VkMemoryAllocateFlags imageMemoryAllocateFlags{ };
  VkDeviceSize stride;
  allocateFromMemoryRequirements(device,
                                 nonCoherentAtomSize,
                                 physicalDeviceMemoryProperties,
                                 imageMemoryRequirements,
                                 imageMemoryPropertyFlags,
                                 imageMemoryAllocateFlags,
                                 1,
                                 &imageMemory,
                                 &stride);
  *outMemory = imageMemory;
  VK_CHECK(vkBindImageMemory(device, image, imageMemory, 0));

  VkImageView imageView;
  VkImageViewCreateInfo textureViewCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = image,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = format,
    .subresourceRange{
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .levelCount = levelCount,
      .layerCount = 1
    }
  };
  VK_CHECK(vkCreateImageView(device, &textureViewCreateInfo, nullptr, &imageView));
  *outImageView = imageView;
}

void createImageFromFilenameDDS(VkDevice device,
                                VkQueue queue,
                                VkCommandBuffer commandBuffer,
                                VkFence fence,
                                VkDeviceSize nonCoherentAtomSize,
                                VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                char const * const filename,
                                VkImage * outImage,
                                VkDeviceMemory * outMemory,
                                VkImageView * outImageView)
{
  uint32_t imageSize;
  void const * imageStart = file::open(filename, &imageSize);
  void * imageData;
  uint32_t * levelOffsets;
  uint32_t imageDataSize;
  DDS_FILE const * ddsFile = dds::validate(imageStart, imageSize, &levelOffsets, &imageData, &imageDataSize);

  VkFormat format = dds::dxgi_to_vulkan(ddsFile->header10.dxgiFormat);
  uint32_t width = ddsFile->header.dwWidth;
  uint32_t height = ddsFile->header.dwHeight;
  uint32_t levelCount = ddsFile->header.dwMipMapCount;

  createImage(device,
              nonCoherentAtomSize,
              physicalDeviceMemoryProperties,
              format,
              width,
              height,
              levelCount,
              outImage,
              outMemory,
              outImageView);

  textureTransfer(device,
                  queue,
                  commandBuffer,
                  fence,
                  nonCoherentAtomSize,
                  physicalDeviceMemoryProperties,
                  imageDataSize,
                  imageData,
                  *outImage,
                  width,
                  height,
                  levelCount,
                  levelOffsets);

  free(levelOffsets);
  // imageData is not malloc'ed, it is a pointer to file:: data, which is also not malloc'ed
}

void createImageFromFilenameTGA(VkDevice device,
                                VkQueue queue,
                                VkCommandBuffer commandBuffer,
                                VkFence fence,
                                VkDeviceSize nonCoherentAtomSize,
                                VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                                char const * const filename,
                                VkImage * outImage,
                                VkDeviceMemory * outMemory,
                                VkImageView * outImageView)
{
  uint32_t imageSize;
  //void const * imageStart = file::open(filename, &imageSize);
  void * imageStart = file::openRelative(filename, &imageSize);
  void * imageData;
  uint32_t imageDataSize;
  tga::header const * tga = tga::validate(imageStart, imageSize, &imageData, &imageDataSize);

  VkFormat format = VK_FORMAT_B8G8R8A8_UNORM;
  uint32_t width = tga->image.width;
  uint32_t height = tga->image.height;
  uint32_t levelCount = 1;
  uint32_t levelOffset = 0;

  createImage(device,
              nonCoherentAtomSize,
              physicalDeviceMemoryProperties,
              format,
              width,
              height,
              levelCount,
              outImage,
              outMemory,
              outImageView);

  textureTransfer(device,
                  queue,
                  commandBuffer,
                  fence,
                  nonCoherentAtomSize,
                  physicalDeviceMemoryProperties,
                  imageDataSize,
                  imageData,
                  *outImage,
                  width,
                  height,
                  levelCount,
                  &levelOffset);

  free(imageStart);
}

VertexIndex createVertexIndexBuffer(VkDevice device,
                                    VkPhysicalDeviceProperties const& physicalDeviceProperties,
                                    VkPhysicalDeviceMemoryProperties const& physicalDeviceMemoryProperties,
                                    void const * vertexStart,
                                    uint32_t vertexSize,
                                    void const * indexStart,
                                    uint32_t indexSize)
{
  VertexIndex vertexIndex{};

  vertexIndex.indexOffset = vertexSize;

  // create buffer

  VkDeviceSize bufferSize{ vertexSize + indexSize };
  VkBufferCreateInfo vertexIndexBufferCreateInfo{
    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .size = bufferSize,
    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE
  };
  VK_CHECK(vkCreateBuffer(device, &vertexIndexBufferCreateInfo, nullptr, &vertexIndex.buffer));

  // allocate memory

  VkMemoryRequirements memoryRequirements;
  vkGetBufferMemoryRequirements(device, vertexIndex.buffer, &memoryRequirements);
  VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
  VkMemoryAllocateFlags memoryAllocateFlags{};
  VkDeviceSize stride;
  allocateFromMemoryRequirements(device,
                                 physicalDeviceProperties.limits.nonCoherentAtomSize,
                                 physicalDeviceMemoryProperties,
                                 memoryRequirements,
                                 memoryPropertyFlags,
                                 memoryAllocateFlags,
                                 1,
                                 &vertexIndex.memory,
                                 &stride);

  VK_CHECK(vkBindBufferMemory(device, vertexIndex.buffer, vertexIndex.memory, 0));

  // copy data

  void * vertexIndexMappedData;
  VK_CHECK(vkMapMemory(device, vertexIndex.memory, 0, VK_WHOLE_SIZE, 0, &vertexIndexMappedData));
  memcpy((void *)(((ptrdiff_t)vertexIndexMappedData) + 0), vertexStart, vertexSize);
  memcpy((void *)(((ptrdiff_t)vertexIndexMappedData) + vertexSize), indexStart, indexSize);

  VkMappedMemoryRange mappedMemoryRange{
    .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
    .memory = vertexIndex.memory,
    .offset = 0,
    .size = VK_WHOLE_SIZE,
  };
  vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);

  vkUnmapMemory(device, vertexIndex.memory);

  return vertexIndex;
}
