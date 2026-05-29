#include <string.h>

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "vulkan/vk_enum_string_helper.h"

#include "dds/validate.h"
#include "vulkan_helper.h"
#include "check.h"
#include "new.h"
#include "file.h"

#include "renpy/vulkan.h"
#include "renpy/script.h"
#include "renpy/interact.h"

namespace renpy {
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

  void vulkan::initial_state(VkInstance instance,
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

  void vulkan::init()
  {
    load_vertex_index_buffer();
    load_shader();
    create_descriptor_sets();
    load_images();
    write_descriptor_sets();
    create_pipeline();
    create_instance_buffers();
  }

  //////////////////////////////////////////////////////////////////////
  // vertex index buffer
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_vertex_index_buffer()
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

  void vulkan::load_shader()
  {
    uint32_t shaderSize;
    void const * shaderStart = file::open("shader/renpy.spv", &shaderSize);

    VkShaderModuleCreateInfo shaderModuleCreateInfo{
      .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .codeSize = shaderSize,
      .pCode = (uint32_t *)shaderStart
    };
    VK_CHECK(vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule));
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor sets
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_descriptor_sets()
  {
    //
    // pool
    //
    constexpr int descriptorPoolSizesCount = 2;
    VkDescriptorPoolSize descriptorPoolSizes[descriptorPoolSizesCount]{
      { // linear sampler
        .type = VK_DESCRIPTOR_TYPE_SAMPLER,
        .descriptorCount = 1,
      },
      {
        .type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
        .descriptorCount = (uint32_t)script::images_length,
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
      constexpr int bindingCount = 2;
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
          .descriptorCount = (uint32_t)script::images_length,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
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

  void vulkan::write_descriptor_sets()
  {
    constexpr uint32_t writeCount = 2;
    VkWriteDescriptorSet writeDescriptorSets[writeCount];
    uint32_t writeIndex = 0;

    // set0 bindings
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

    VkDescriptorImageInfo * sceneDescriptorImageInfos = NewM<VkDescriptorImageInfo>(script::images_length);
    for (int i = 0; i < script::images_length; i++) {
      sceneDescriptorImageInfos[i] = {
        .imageView = images[i].imageView,
        .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
      };
    }

    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet0,
      .dstBinding = 1,
      .descriptorCount = (uint32_t)script::images_length,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
      .pImageInfo = sceneDescriptorImageInfos
    };

    assert(writeIndex == writeCount);
    vkUpdateDescriptorSets(device, writeIndex, writeDescriptorSets, 0, nullptr);
    //free(sceneDescriptorImageInfos);
  }

  //////////////////////////////////////////////////////////////////////
  // images
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_image_inner(VkCommandBuffer commandBuffer, VkFence fence, int i, char const * filename)
  {
    size_t length = strlen(filename);
    if (dds::isDDSExtension(filename, length)) {
      createImageFromFilenameDDS(device,
                                 queue,
                                 commandBuffer,
                                 fence,
                                 physicalDeviceProperties.limits.nonCoherentAtomSize,
                                 physicalDeviceMemoryProperties,
                                 filename,
                                 &images[i].image,
                                 &images[i].memory,
                                 &images[i].imageView);
    } else {
      fprintf(stderr, "filename: %s\n", filename);
      ASSERT(false, "invalid image filename extension");
    }
  }

  void vulkan::load_images()
  {
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

    // images
    images = NewM<Image>(script::images_length);

    for (int i = 0; i < script::images_length; i++) {
      char const * filename = script::images[i].path;
      load_image_inner(commandBuffer, fence, i, filename);
    }

    // cleanup

    vkDestroyFence(device, fence, nullptr);
    vkFreeCommandBuffers(device,
                         commandPool,
                         1,
                         &commandBuffer);
  }

  //////////////////////////////////////////////////////////////////////
  // create instance buffer
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_instance_buffers()
  {
    constexpr VkDeviceSize bufferSize{ maximumImageCount * (sizeof (ImageInstance)) };
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
  // pipeline
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_pipeline()
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
      .blendEnable = VK_TRUE,
      .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
      .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
      .colorBlendOp = VK_BLEND_OP_ADD,
      .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
      .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
      .alphaBlendOp = VK_BLEND_OP_ADD,
      .colorWriteMask = 0xF,
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
      },
    };

    constexpr int vertexAttributeDescriptionsCount = 6;
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
        .format = VK_FORMAT_R16G16_SINT,
        .offset = 0,
      },
      {
        .location = 3,
        .binding = 1,
        .format = VK_FORMAT_R16G16_SINT,
        .offset = 4,
      },
      {
        .location = 4,
        .binding = 1,
        .format = VK_FORMAT_R8G8B8A8_UNORM,
        .offset = 8,
      },
      {
        .location = 5,
        .binding = 1,
        .format = VK_FORMAT_R16_SINT,
        .offset = 12,
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
  // draw
  //////////////////////////////////////////////////////////////////////

  void vulkan::draw_menu_frame(VkCommandBuffer commandBuffer,
                               uint32_t frameIndex,
                               renpy::interpreter const& state,
                               int & outputIndex,
                               int mx, int my) const
  {
    for (uint32_t i = 0; i < state.menu.count; i++) {
      int y = menu::yStride * i + menu::y;

      bool overlap = renpy::overlap(menu::width, menu::height, menu::x, y, mx, my);
      instanceMappedData[maximumImageCount * frameIndex + outputIndex++] = {
        .size = {menu::width, menu::height},
        .topLeft = {menu::x, (int16_t)(y)},
        .color = overlap ? 0xf0494493u : 0xa0ffffffu,
        .imageIndex = -3, // white gradient 2
      };
    }
  }

  void vulkan::draw_say_frame(VkCommandBuffer commandBuffer,
                              uint32_t frameIndex,
                              renpy::interpreter const& state,
                              int & outputIndex) const
  {
    instanceMappedData[maximumImageCount * frameIndex + outputIndex++] = {
      .size = {708, 200},
      .topLeft = {286, 720 - 200},
      .color = 0x80ffffffu,
      .imageIndex = -2, // white gradient 1
    };
    instanceMappedData[maximumImageCount * frameIndex + outputIndex++] = {
      .size = {216, 184},
      .topLeft = {336, 720 - 184},
      .imageIndex = 0, // flower
    };
    instanceMappedData[maximumImageCount * frameIndex + outputIndex++] = {
      .size = {-216, 184},
      .topLeft = {1280 - (336 + 216), 720 - 184},
      .imageIndex = 0, // flower
    };

    if (state.say.characterIndex != -1u) {
      instanceMappedData[maximumImageCount * frameIndex + outputIndex++] = {
        .size = {180, 30},
        .topLeft = {550, 542},
        .color = 0x80ffffffu,
        .imageIndex = -4, // white gradient 2
      };
    }
  }

  void vulkan::draw(VkCommandBuffer commandBuffer,
                    uint32_t frameIndex,
                    renpy::interpreter const& state,
                    int mx, int my,
                    bool drawText) const
  {
    int outputIndex = 0;
    // update
    instanceMappedData[maximumImageCount * frameIndex + outputIndex++] = {
      .size = {1280, 720},
      .topLeft = {0, 0},
      .color = state.backgroundColor,
      .imageIndex = (int16_t)state.backgroundIndex,
    };

    for (uint32_t i = 0; i < state.shownImagesCount; i++) {
      renpy::top_left const& tl = renpy::transforms[state.shownImages[i].transformIndex];
      instanceMappedData[maximumImageCount * frameIndex + outputIndex++] = {
        .size = {452, 528},
        .topLeft = {(int16_t)tl.left, (int16_t)tl.top},
        .imageIndex = (int16_t)state.shownImages[i].imageIndex,
      };
    }

    if (drawText) {
      if (state.menu.count != 0) {
        draw_menu_frame(commandBuffer, frameIndex, state, outputIndex, mx, my);
      } else if (state.say.stringIndex != ~0u) {
        draw_say_frame(commandBuffer, frameIndex, state, outputIndex);
      }
    }

    // flush
    constexpr int mappedMemoryRangesCount = 1;
    VkMappedMemoryRange mappedMemoryRanges[mappedMemoryRangesCount]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = instanceMemory,
        .offset = 0,
        .size = (sizeof (ImageInstance)) * outputIndex,
      }
    };
    alignMappedMemoryRanges(physicalDeviceProperties.limits.nonCoherentAtomSize,
                            instanceMemorySize,
                            mappedMemoryRangesCount,
                            mappedMemoryRanges);
    vkFlushMappedMemoryRanges(device, mappedMemoryRangesCount, mappedMemoryRanges);

    // draw

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
