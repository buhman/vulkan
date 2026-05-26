#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "volk/volk.h"
#include "vulkan/vk_enum_string_helper.h"

#include "directxmath/directxmath.h"
#include "vulkan_helper.h"
#include "check.h"
#include "file.h"

#include "font/outline.h"
#include "font/outline_types.h"

namespace font::outline {
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

  void font::initial_state(VkInstance instance,
                           VkDevice device,
                           VkQueue queue,
                           VkCommandPool commandPool,
                           VkPhysicalDeviceProperties physicalDeviceProperties,
                           VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties,
                           VkFormat colorFormat,
                           VkFormat depthFormat,
                           VkSampler linearSampler)
  {
    this->instance = instance;
    this->device = device;
    this->queue = queue;
    this->commandPool = commandPool;

    this->physicalDeviceProperties = physicalDeviceProperties;
    this->physicalDeviceMemoryProperties = physicalDeviceMemoryProperties;

    this->colorFormat = colorFormat;
    this->depthFormat = depthFormat;

    this->linearSampler = linearSampler;
  }

  void font::init()
  {
    load_vertex_index_buffer();
    load_shader();
    create_descriptor_sets();
    loadedFont = load_font(uncial_antiqua[0]);
    create_glyphs_buffer(loadedFont.font, loadedFont.glyphs);
    write_descriptor_sets(loadedFont.allocatedImage.imageView);
    create_instance_buffers();
    create_pipeline();
  }

  //////////////////////////////////////////////////////////////////////
  // vertex index buffer
  //////////////////////////////////////////////////////////////////////

  void font::load_vertex_index_buffer()
  {
    void const * vertexStart = (void const *)vertexData;
    void const * indexStart = (void const *)indexData;

    vertexIndex = createVertexIndexBuffer(device,
                                          physicalDeviceProperties,
                                          physicalDeviceMemoryProperties,
                                          vertexStart, vertexSize,
                                          indexStart, indexSize);
  }

  //////////////////////////////////////////////////////////////////////
  // shader
  //////////////////////////////////////////////////////////////////////

  void font::load_shader()
  {
    uint32_t shaderSize;
    void const * shaderStart = file::open("shader/font.spv", &shaderSize);

    VkShaderModuleCreateInfo shaderModuleCreateInfo{
      .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .codeSize = shaderSize,
      .pCode = (uint32_t *)shaderStart
    };
    VK_CHECK(vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule));
  }

  //////////////////////////////////////////////////////////////////////
  // pipeline
  //////////////////////////////////////////////////////////////////////

  void font::create_pipeline()
  {
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      .setLayoutCount = descriptorSetLayoutCount,
      .pSetLayouts = descriptorSetLayouts,
      .pushConstantRangeCount = 0,
      .pPushConstantRanges = nullptr
    };
    VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
      .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP
    };

    VkPipelineShaderStageCreateInfo shaderStages[2]{
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = shaderModule,
        .pName = "VSMain"
      },
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = shaderModule,
        .pName = "PSMain"
      }
    };

    VkPipelineViewportStateCreateInfo viewportState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
      .viewportCount = 1,
      .scissorCount = 1
    };

    constexpr uint32_t dynamicStateCount = 2;
    VkDynamicState dynamicStates[dynamicStateCount]{
      VK_DYNAMIC_STATE_VIEWPORT,
      VK_DYNAMIC_STATE_SCISSOR,
    };
    VkPipelineDynamicStateCreateInfo dynamicState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
      .dynamicStateCount = dynamicStateCount,
      .pDynamicStates = dynamicStates
    };

    VkPipelineDepthStencilStateCreateInfo depthStencilState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
      .depthTestEnable = VK_FALSE,
      .depthWriteEnable = VK_FALSE,
      .depthCompareOp = VK_COMPARE_OP_ALWAYS,
      .stencilTestEnable = VK_FALSE,
      .front = {
        .failOp = VK_STENCIL_OP_REPLACE,
        .passOp = VK_STENCIL_OP_REPLACE,
        .depthFailOp = VK_STENCIL_OP_REPLACE,
        .compareOp = VK_COMPARE_OP_ALWAYS,
        .compareMask = 0x01,
        .writeMask = 0x01,
        .reference = 1,
      },
      .back = {
        .failOp = VK_STENCIL_OP_REPLACE,
        .passOp = VK_STENCIL_OP_REPLACE,
        .depthFailOp = VK_STENCIL_OP_REPLACE,
        .compareOp = VK_COMPARE_OP_ALWAYS,
        .compareMask = 0x01,
        .writeMask = 0x01,
        .reference = 1,
      },
    };

    VkPipelineRenderingCreateInfo renderingCreateInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
      .colorAttachmentCount = 1,
      .pColorAttachmentFormats = &colorFormat,
      .depthAttachmentFormat = depthFormat,
      .stencilAttachmentFormat = depthFormat
    };

    VkPipelineColorBlendAttachmentState blendAttachment{
      .colorWriteMask = 0xF
    };
    VkPipelineColorBlendStateCreateInfo colorBlendState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
      .attachmentCount = 1,
      .pAttachments = &blendAttachment
    };
    VkPipelineRasterizationStateCreateInfo rasterizationState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
      //.cullMode = VK_CULL_MODE_BACK_BIT,
      .cullMode = VK_CULL_MODE_NONE,
      .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
      .lineWidth = 1.0f
    };
    VkPipelineMultisampleStateCreateInfo multisampleState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
      .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
    };

    constexpr int vertexBindingDescriptionsCount = 2;
    VkVertexInputBindingDescription vertexBindingDescriptions[vertexBindingDescriptionsCount]{
      {
        .binding = 0,
        .stride = perVertexSize,
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
      },
      {
        .binding = 1,
        .stride = perInstanceSize,
        .inputRate = VK_VERTEX_INPUT_RATE_INSTANCE
      }
    };

    constexpr int vertexAttributeDescriptionsCount = 5;
    VkVertexInputAttributeDescription vertexAttributeDescriptions[vertexAttributeDescriptionsCount]{
      // per-vertex
      { // position
        .location = 0,
        .binding = 0,
        .format = VK_FORMAT_R16G16_SFLOAT,
        .offset = 0,
      },
      { // texture
        .location = 1,
        .binding = 0,
        .format = VK_FORMAT_R16G16_SFLOAT,
        .offset = 4,
      },
      // per-instance
      {
        .location = 2,
        .binding = 1,
        .format = VK_FORMAT_R16G16_UINT,
        .offset = 0,
      },
      {
        .location = 3,
        .binding = 1,
        .format = VK_FORMAT_R32_UINT,
        .offset = 4,
      },
      {
        .location = 4,
        .binding = 1,
        .format = VK_FORMAT_R8G8B8A8_UNORM,
        .offset = 8,
      },
    };

    VkPipelineVertexInputStateCreateInfo vertexInputState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
      .vertexBindingDescriptionCount = vertexBindingDescriptionsCount,
      .pVertexBindingDescriptions = vertexBindingDescriptions,
      .vertexAttributeDescriptionCount = vertexAttributeDescriptionsCount,
      .pVertexAttributeDescriptions = vertexAttributeDescriptions,
    };

    VkGraphicsPipelineCreateInfo pipelineCreateInfos[1]{
      {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = &renderingCreateInfo,
        .stageCount = 2,
        .pStages = shaderStages,
        .pVertexInputState = &vertexInputState,
        .pInputAssemblyState = &inputAssemblyState,
        .pViewportState = &viewportState,
        .pRasterizationState = &rasterizationState,
        .pMultisampleState = &multisampleState,
        .pDepthStencilState = &depthStencilState,
        .pColorBlendState = &colorBlendState,
        .pDynamicState = &dynamicState,
        .layout = pipelineLayout
      },
    };

    VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, pipelineCreateInfos, nullptr, &pipeline));
  }

  //////////////////////////////////////////////////////////////////////
  // load font
  //////////////////////////////////////////////////////////////////////

  LoadedFont font::load_font(font_desc const& desc)
  {
    uint32_t font_data_size;
    void const * font_data = file::open(desc.path, &font_data_size);
    assert(font_data != nullptr);

    types::font * font = (types::font *)font_data;
    types::glyph * glyphs = (types::glyph *)(((ptrdiff_t)font_data) + (sizeof (types::font)));

    void * texture_data = (void *)(((ptrdiff_t)glyphs) + (sizeof (types::glyph)) * font->glyph_count);

    ptrdiff_t font_end = ((ptrdiff_t)font_data) + font_data_size;
    int texture_size = font->texture_width * font->texture_height;
    assert(font_end - ((ptrdiff_t)texture_data) == texture_size);

    // transfer texture

    VkCommandBuffer commandBuffer{};
    VkCommandBufferAllocateInfo commandBufferAllocateInfo{
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .commandPool = commandPool,
      .commandBufferCount = 1
    };
    VK_CHECK(vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, &commandBuffer));

    VkFenceCreateInfo fenceCreateInfo{
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
    };
    VkFence fence{};
    VK_CHECK(vkCreateFence(device, &fenceCreateInfo, nullptr, &fence));

    void * imageData = texture_data;
    uint32_t imageDataSize = texture_size;
    VkFormat format = VK_FORMAT_R8_UNORM;
    uint32_t width = font->texture_width;
    uint32_t height = font->texture_height;
    uint32_t levelCount = 1;
    uint32_t levelOffset = 0;
    VkImage outImage;
    VkDeviceMemory outMemory;
    VkImageView outImageView;

    createImage(device,
                physicalDeviceProperties.limits.nonCoherentAtomSize,
                physicalDeviceMemoryProperties,
                format,
                width,
                height,
                levelCount,
                &outImage,
                &outMemory,
                &outImageView);

    textureTransfer(device,
                    queue,
                    commandBuffer,
                    fence,
                    physicalDeviceProperties.limits.nonCoherentAtomSize,
                    physicalDeviceMemoryProperties,
                    imageDataSize,
                    imageData,
                    outImage,
                    width,
                    height,
                    levelCount,
                    &levelOffset);

    vkDestroyFence(device, fence, nullptr);
    vkFreeCommandBuffers(device,
                         commandPool,
                         1,
                         &commandBuffer);

    // return
    return {
      .font = font,
      .glyphs = glyphs,
      .allocatedImage = {
        .image = outImage,
        .memory = outMemory,
        .imageView = outImageView,
      },
    };
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor sets
  //////////////////////////////////////////////////////////////////////

  void font::create_descriptor_sets()
  {
    //
    // pool
    //
    constexpr int descriptorPoolSizesCount = 3;
    VkDescriptorPoolSize descriptorPoolSizes[descriptorPoolSizesCount]{
      { // linear sampler
        .type = VK_DESCRIPTOR_TYPE_SAMPLER,
        .descriptorCount = 1,
      },
      {
        .type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
        .descriptorCount = 1,
      },
      {
        .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .descriptorCount = 1,
      },
    };
    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .maxSets = 1,
      .poolSizeCount = descriptorPoolSizesCount,
      .pPoolSizes = descriptorPoolSizes
    };
    VK_CHECK(vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

    //
    // (set 0, constant)
    //
    {
      constexpr int bindingCount = 3;
      VkDescriptorSetLayoutBinding descriptorSetLayoutBindings[bindingCount]{
        {
          .binding = 0,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
        { // font image
          .binding = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
        {
          .binding = 2,
          .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_VERTEX_BIT
        }
      };

      VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = bindingCount,
        .pBindings = descriptorSetLayoutBindings
      };
      VK_CHECK(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayouts[0]));

      VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &descriptorSetLayouts[0]
      };
      VK_CHECK(vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &descriptorSet0));
    }
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor set writes
  //////////////////////////////////////////////////////////////////////

  void font::write_descriptor_sets(VkImageView fontImageView)
  {
    constexpr uint32_t writeCount = 3;
    VkWriteDescriptorSet writeDescriptorSets[writeCount];
    uint32_t writeIndex = 0;

    // set1 bindings
    VkDescriptorImageInfo samplerDescriptorImageInfo = {
      .sampler = linearSampler,
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet0,
      .dstBinding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER,
      .pImageInfo = &samplerDescriptorImageInfo
    };
    VkDescriptorImageInfo terrainDescriptorImageInfo = {
      .imageView = fontImageView,
      .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet0,
      .dstBinding = 1,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
      .pImageInfo = &terrainDescriptorImageInfo
    };
    VkDescriptorBufferInfo glyphsDescriptorBufferInfo{
      .buffer = glyphsBuffer,
      .offset = 0,
      .range = glyphsBufferSize,
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet0,
      .dstBinding = 2,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
      .pBufferInfo = &glyphsDescriptorBufferInfo
    };
    assert(writeIndex == writeCount);
    vkUpdateDescriptorSets(device, writeIndex, writeDescriptorSets, 0, nullptr);
  }

  //////////////////////////////////////////////////////////////////////
  // create instance buffer
  //////////////////////////////////////////////////////////////////////

  void font::create_instance_buffers()
  {
    constexpr VkDeviceSize bufferSize{ maximumGlyphCount * (sizeof (GlyphInstance)) };
    instanceMemorySize = bufferSize * 2;
    instanceBufferOffset[0] = bufferSize * 0;
    instanceBufferOffset[1] = bufferSize * 1;

    // create buffer
    VkBufferCreateInfo bufferCreateInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = instanceMemorySize,
      .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };
    VK_CHECK(vkCreateBuffer(device, &bufferCreateInfo, nullptr, &instanceBuffer));

    // allocate memory

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, instanceBuffer, &memoryRequirements);
    VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
    VkMemoryAllocateFlags memoryAllocateFlags{};
    VkDeviceSize stride;
    allocateFromMemoryRequirements(device,
                                   physicalDeviceProperties.limits.nonCoherentAtomSize,
                                   physicalDeviceMemoryProperties,
                                   memoryRequirements,
                                   memoryPropertyFlags,
                                   memoryAllocateFlags,
                                   1,
                                   &instanceMemory,
                                   &stride);

    VK_CHECK(vkBindBufferMemory(device, instanceBuffer, instanceMemory, 0));

    // map memory

    VK_CHECK(vkMapMemory(device, instanceMemory, 0, VK_WHOLE_SIZE, 0, (void **)&instanceMappedData));
  }

  //////////////////////////////////////////////////////////////////////
  // create glyphs buffer
  //////////////////////////////////////////////////////////////////////

  void font::create_glyphs_buffer(types::font const * const font, types::glyph const * const glyphs)
  {
    glyphsBufferSize = (sizeof (Glyph)) * font->glyph_count;

    // create buffer
    VkBufferCreateInfo bufferCreateInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = glyphsBufferSize,
      .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };
    VK_CHECK(vkCreateBuffer(device, &bufferCreateInfo, nullptr, &glyphsBuffer));

    // allocate memory

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, glyphsBuffer, &memoryRequirements);
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
                                   &glyphsMemory,
                                   &stride);

    VK_CHECK(vkBindBufferMemory(device, glyphsBuffer, glyphsMemory, 0));

    // map memory
    Glyph * glyphsMappedData;
    VK_CHECK(vkMapMemory(device, glyphsMemory, 0, VK_WHOLE_SIZE, 0, (void **)&glyphsMappedData));

    for (int i = 0; i < font->glyph_count; i++) {
      glyphsMappedData[i].x = glyphs[i].bitmap.x;
      glyphsMappedData[i].y = glyphs[i].bitmap.y;
      glyphsMappedData[i].width = glyphs[i].bitmap.width;
      glyphsMappedData[i].height = glyphs[i].bitmap.height;
    }

    // flush
    constexpr int mappedMemoryRangesCount = 1;
    VkMappedMemoryRange mappedMemoryRanges[mappedMemoryRangesCount]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = glyphsMemory,
        .offset = 0,
        .size = VK_WHOLE_SIZE,
      }
    };
    vkFlushMappedMemoryRanges(device, mappedMemoryRangesCount, mappedMemoryRanges);

    vkUnmapMemory(device, glyphsMemory);
  }

  //////////////////////////////////////////////////////////////////////
  // draw
  //////////////////////////////////////////////////////////////////////

  void font::draw(VkCommandBuffer commandBuffer,
                  uint32_t frameIndex)
  {
    // transfer
    const char * string = "so when Nico wants to run this game on his\n4K monitor, he gets a dinky little 1280x720\nwindow instead?";
    int outputIndex = 0;
    int stringIndex = 0;

    uint32_t x = 64 << 6;
    uint32_t y = 64 << 6;
    while (true) {
      char c = string[stringIndex++];
      if (c == 0)
        break;

      if (c != ' ') {
        instanceMappedData[maximumGlyphCount * frameIndex + outputIndex++] = {
          (uint16_t)((x + loadedFont.glyphs[c - 32].metrics.horiBearingX) >> 6),
          (uint16_t)((y - loadedFont.glyphs[c - 32].metrics.horiBearingY) >> 6),
          (uint32_t)(c - 32),
          0xaabbccdd,
        };
      }

      if (c == '\n') {
        y += loadedFont.font->face_metrics.height * 1.2;
        x = 64 << 6;
      } else {
        x += loadedFont.glyphs[c - 32].metrics.horiAdvance;
      }
    };
    // flush
    constexpr int mappedMemoryRangesCount = 1;
    VkMappedMemoryRange mappedMemoryRanges[mappedMemoryRangesCount]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = instanceMemory,
        .offset = 0,
        .size = (sizeof (GlyphInstance)) * outputIndex,
      }
    };
    alignMappedMemoryRanges(physicalDeviceProperties.limits.nonCoherentAtomSize,
                            instanceMemorySize,
                            mappedMemoryRangesCount,
                            mappedMemoryRanges);
    vkFlushMappedMemoryRanges(device, mappedMemoryRangesCount, mappedMemoryRanges);

    // bind/draw

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

    VkDescriptorSet descriptorSets[1] = {
      descriptorSet0,
    };
    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipelineLayout,
                            0, 1, descriptorSets,
                            0, nullptr);

    vkCmdBindIndexBuffer(commandBuffer, vertexIndex.buffer, vertexIndex.indexOffset, VK_INDEX_TYPE_UINT16);

    VkDeviceSize vertexOffsets[2]{ 0, instanceBufferOffset[frameIndex] };
    VkBuffer vertexBuffers[2]{ vertexIndex.buffer, instanceBuffer };
    vkCmdBindVertexBuffers(commandBuffer, 0, 2, vertexBuffers, vertexOffsets);

    vkCmdDrawIndexed(commandBuffer, 4, outputIndex, 0, 0, 0);
  }
}
