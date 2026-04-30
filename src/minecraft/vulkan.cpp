#include <stdio.h>
#include <string.h>

#include "volk/volk.h"
#include "vulkan/vk_enum_string_helper.h"

#include "file.h"
#include "check.h"
#include "vulkan_helper.h"
#include "new.h"
#include "popcount.h"

#include "minecraft/data.inc"
#include "minecraft/world.h"
#include "minecraft/vulkan.h"
#include "minecraft/vulkan/per_world.h"

namespace minecraft::vulkan {

  static inline int popcount(int x)
  {
    return __builtin_popcount(x);
  }

  void vulkan::initial_state(VkInstance instance,
                             VkDevice device,
                             VkQueue queue,
                             VkCommandPool commandPool,
                             VkPhysicalDeviceProperties physicalDeviceProperties,
                             VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties,
                             VkFormat colorFormat,
                             VkFormat depthFormat)
  {
    this->instance = instance;
    this->device = device;
    this->queue = queue;
    this->commandPool = commandPool;

    this->physicalDeviceProperties = physicalDeviceProperties;
    this->physicalDeviceMemoryProperties = physicalDeviceMemoryProperties;

    this->colorFormat = colorFormat;
    this->depthFormat = depthFormat;
  }

  void vulkan::init()
  {
    load_vertex_index_buffer("data/minecraft/per_vertex.vtx", "data/minecraft/configuration.idx");
    load_shader();
    create_pipeline();
    load_worlds();
  }

  //////////////////////////////////////////////////////////////////////
  // vertex index buffer
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_vertex_index_buffer(char const * vertex_filename,
                                        char const * index_filename)
  {
    uint32_t vertexSize;
    void const * vertexStart = file::open(vertex_filename, &vertexSize);
    uint32_t indexSize;
    void const * indexStart = file::open(index_filename, &indexSize);

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
  }

  //////////////////////////////////////////////////////////////////////
  // shader
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_shader()
  {
    uint32_t shaderSize;
    void const * shaderStart = file::open("shader/minecraft.spv", &shaderSize);

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

  void vulkan::create_pipeline()
  {
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      //.setLayoutCount = 2,
      //.pSetLayouts = descriptorSetLayouts,
      //.pushConstantRangeCount = 0,
      //.pPushConstantRanges = nullptr
    };
    VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
      .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST
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
      .depthTestEnable = VK_TRUE,
      .depthWriteEnable = VK_TRUE,
      .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
      .stencilTestEnable = VK_TRUE,
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

    VkVertexInputBindingDescription vertexBindingDescriptions[2]{
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

    VkVertexInputAttributeDescription vertexAttributeDescriptions[8]{
      // per-vertex
      { // position
        .location = 0,
        .binding = 0,
        .format = VK_FORMAT_R16G16B16_SFLOAT,
        .offset = 0,
      },
      { // normal
        .location = 1,
        .binding = 0,
        .format = VK_FORMAT_R16G16B16_SFLOAT,
        .offset = 6,
      },
      { // texture
        .location = 2,
        .binding = 0,
        .format = VK_FORMAT_R16G16_SFLOAT,
        .offset = 12,
      },
      // per-instance
      { // block position
        .location = 3,
        .binding = 1,
        .format = VK_FORMAT_R16G16B16_SINT,
        .offset = 0,
      },
      { // block id
        .location = 4,
        .binding = 1,
        .format = VK_FORMAT_R16_SINT,
        .offset = 8,
      },
      { // data
        .location = 5,
        .binding = 1,
        .format = VK_FORMAT_R16_SINT,
        .offset = 10,
      },
      { // texture id
        .location = 6,
        .binding = 1,
        .format = VK_FORMAT_R16_SINT,
        .offset = 12,
      },
      { // special
        .location = 7,
        .binding = 1,
        .format = VK_FORMAT_R16_SINT,
        .offset = 14,
      },
    };

    VkPipelineVertexInputStateCreateInfo vertexInputState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
      .vertexBindingDescriptionCount = 2,
      .pVertexBindingDescriptions = vertexBindingDescriptions,
      .vertexAttributeDescriptionCount = 8,
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
  // load worlds
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_worlds()
  {
    worlds = NewM<per_world>(minecraft::world::descriptors_length);

    for (int i = 0; i < minecraft::world::descriptors_length; i++) {
      worlds[i].load(device, physicalDeviceProperties, physicalDeviceMemoryProperties, &minecraft::world::descriptors[i]);
    }
  }

  //////////////////////////////////////////////////////////////////////
  // draw
  //////////////////////////////////////////////////////////////////////

  void vulkan::draw(VkCommandBuffer commandBuffer)
  {
    vkCmdBindIndexBuffer(commandBuffer, vertexIndex.buffer, vertexIndex.indexOffset, VK_INDEX_TYPE_UINT16);
    VkBuffer vertexBuffers[2]{
      vertexIndex.buffer,
      worlds[0].regions[0].vertexBuffer,
    };
    VkDeviceSize vertexOffsets[2]{ 0, 0 };

    vkCmdBindVertexBuffers(commandBuffer, 0, 2, vertexBuffers, vertexOffsets);
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

    for (int configuration = 1; configuration < 64; configuration++) {
      int index_count = 6 * popcount(configuration);
      int first_index = index_buffer_configuration_offsets[configuration];
      int instance_count = worlds[0].regions[0].instanceCFG[configuration].count;
      int first_instance = worlds[0].regions[0].instanceCFG[configuration].offset / perInstanceSize;

      if (instance_count == 0)
        continue;

      vkCmdDrawIndexed(commandBuffer, index_count, instance_count, first_index, 0, first_instance);
    };
  }
}
