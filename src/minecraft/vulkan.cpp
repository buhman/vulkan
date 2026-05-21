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
                             VkFormat depthFormat,
                             VkSampler linearSampler,
                             VkImageView shadowDepthImageView)
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
    this->shadowDepthImageView = shadowDepthImageView;
  }

  void vulkan::init()
  {
    load_vertex_index_buffer("data/minecraft/per_vertex.vtx", "data/minecraft/configuration.idx");
    load_shader();
    load_image("data/minecraft/terrain2.dds", terrainImage);
    create_uniform_buffers();
    create_descriptor_sets();
    write_descriptor_sets();
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
      .setLayoutCount = 2,
      .pSetLayouts = descriptorSetLayouts,
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
  // uniform buffers
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_uniform_buffers()
  {
    VkMemoryRequirements memoryRequirements[uniformBufferDescriptorCount];
    VkDeviceSize offsets[uniformBufferDescriptorCount];

    uint32_t memoryRequirementsIndex = 0;
    // per-frame
    for (uint32_t i = 0; i < maxFrames; i++) {
      VkBufferCreateInfo sceneBufferCreateInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = (sizeof (Scene)),
        .usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      };

      VK_CHECK(vkCreateBuffer(device, &sceneBufferCreateInfo, nullptr, &shaderDataDevice.frame[i].sceneBuffer));
      vkGetBufferMemoryRequirements(device, shaderDataDevice.frame[i].sceneBuffer, &memoryRequirements[memoryRequirementsIndex++]);
    }

    assert(memoryRequirementsIndex == uniformBufferDescriptorCount);

    VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
    VkMemoryAllocateFlags memoryAllocateFlags{ };
    shaderDataDevice.memorySize = allocateFromMemoryRequirements2(device,
                                                                  physicalDeviceProperties.limits.nonCoherentAtomSize,
                                                                  physicalDeviceMemoryProperties,
                                                                  memoryPropertyFlags,
                                                                  memoryAllocateFlags,
                                                                  uniformBufferDescriptorCount,
                                                                  memoryRequirements,
                                                                  &shaderDataDevice.memory,
                                                                  offsets);

    VkDeviceSize offset{ 0 };
    VkDeviceSize size{ VK_WHOLE_SIZE };
    VkMemoryMapFlags flags{ 0 };
    VK_CHECK(vkMapMemory(device, shaderDataDevice.memory, offset, size, flags, &shaderDataDevice.mappedData));

    uint32_t offsetsIndex = 0;
    // this must match the same order as memoryRequirements
    for (uint32_t i = 0; i < maxFrames; i++) {
      shaderDataDevice.frame[i].sceneOffset = offsets[offsetsIndex];
      shaderDataDevice.frame[i].sceneSize = memoryRequirements[offsetsIndex++].size;
      shaderDataDevice.frame[i].sceneMapped = (Scene *)(((size_t)shaderDataDevice.mappedData) + shaderDataDevice.frame[i].sceneOffset);
      VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.frame[i].sceneBuffer, shaderDataDevice.memory, shaderDataDevice.frame[i].sceneOffset));
    }
    assert(offsetsIndex == uniformBufferDescriptorCount);
  }

  //////////////////////////////////////////////////////////////////////
  // images
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_image(char const * filename,
                          Image & image)
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

    // load

    createImageFromFilenameDDS(device,
                               queue,
                               commandBuffer,
                               fence,
                               physicalDeviceProperties.limits.nonCoherentAtomSize,
                               physicalDeviceMemoryProperties,
                               filename,
                               &image.image,
                               &image.memory,
                               &image.imageView);

    // cleanup

    vkDestroyFence(device, fence, nullptr);
    vkFreeCommandBuffers(device,
                         commandPool,
                         1,
                         &commandBuffer);
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor sets
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_descriptor_sets()
  {
    //
    // pool
    //
    constexpr int descriptorPoolSizesCount = 3;
    VkDescriptorPoolSize descriptorPoolSizes[descriptorPoolSizesCount]{
      {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = (maxFrames * 1),
      },
      { // linear sampler
        .type = VK_DESCRIPTOR_TYPE_SAMPLER,
        .descriptorCount = 1,
      },
      {
        .type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
        .descriptorCount = 1 + 1, // +1 for shadow sampler
      }
    };
    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .maxSets = maxFrames + 1,
      .poolSizeCount = descriptorPoolSizesCount,
      .pPoolSizes = descriptorPoolSizes
    };
    VK_CHECK(vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

    //
    // uniform buffer descriptor set layout/allocation (set 0, per-frame)
    //
    {
      constexpr int bindingCount = 1;
      VkDescriptorSetLayoutBinding descriptorSetLayoutBindings[bindingCount]{
        {
          .binding = 0,
          .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
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

      VkDescriptorSetLayout setLayouts[maxFrames];
      for (uint32_t i = 0; i < maxFrames; i++) {
        setLayouts[i] = descriptorSetLayouts[0];
      };

      VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = maxFrames,
        .pSetLayouts = setLayouts
      };
      VK_CHECK(vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, descriptorSets0));
    }

    //
    // uniform buffer descriptor set layout/allocation (set 1, constant)
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
        { // shadow sampled image
          .binding = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
        { // terrain sampled image
          .binding = 2,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        }
      };

      VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = bindingCount,
        .pBindings = descriptorSetLayoutBindings
      };
      VK_CHECK(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayouts[1]));

      VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &descriptorSetLayouts[1]
      };
      VK_CHECK(vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &descriptorSet1));
    }
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor set writes
  //////////////////////////////////////////////////////////////////////

  void vulkan::write_descriptor_sets()
  {
    VkWriteDescriptorSet writeDescriptorSets[bindingCount];
    uint32_t writeIndex = 0;

    VkDescriptorBufferInfo sceneDescriptorBufferInfos[maxFrames];

    // set0 bindings
    for (uint32_t i = 0; i < maxFrames; i++) {
      sceneDescriptorBufferInfos[i] = {
        .buffer = shaderDataDevice.frame[i].sceneBuffer,
        .offset = 0,
        .range = shaderDataDevice.frame[i].sceneSize,
      };
      writeDescriptorSets[writeIndex++] = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptorSets0[i],
        .dstBinding = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .pBufferInfo = &sceneDescriptorBufferInfos[i]
      };
    }

    // set1 bindings
    VkDescriptorImageInfo samplerDescriptorImageInfo = {
      .sampler = linearSampler,
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER,
      .pImageInfo = &samplerDescriptorImageInfo
    };
    VkDescriptorImageInfo shadowDepthDescriptorImageInfo = {
      .imageView = shadowDepthImageView,
      .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 1,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
      .pImageInfo = &shadowDepthDescriptorImageInfo
    };
    VkDescriptorImageInfo terrainDescriptorImageInfo = {
      .imageView = terrainImage.imageView,
      .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 2,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
      .pImageInfo = &terrainDescriptorImageInfo
    };

    assert(writeIndex == bindingCount);
    vkUpdateDescriptorSets(device, writeIndex, writeDescriptorSets, 0, nullptr);
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
  // scene data
  //////////////////////////////////////////////////////////////////////

  void vulkan::transfer_transforms(XMMATRIX const & projection,
                                   XMMATRIX const & view,
                                   XMVECTOR const & lightPosition,
                                   uint32_t frameIndex)
  {
    Scene * scene = shaderDataDevice.frame[frameIndex].sceneMapped;
    XMStoreFloat4x4(&scene->projection, projection);
    XMStoreFloat4x4(&scene->view, view);
    XMStoreFloat4(&scene->lightPosition, lightPosition);

    // flush
    constexpr int mappedMemoryRangesCount = 1;
    VkMappedMemoryRange mappedMemoryRanges[mappedMemoryRangesCount]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = shaderDataDevice.memory,
        .offset = shaderDataDevice.frame[frameIndex].sceneOffset,
        .size = shaderDataDevice.frame[frameIndex].sceneSize,
      }
    };
    alignMappedMemoryRanges(physicalDeviceProperties.limits.nonCoherentAtomSize,
                            shaderDataDevice.memorySize,
                            mappedMemoryRangesCount,
                            mappedMemoryRanges);
    vkFlushMappedMemoryRanges(device, mappedMemoryRangesCount, mappedMemoryRanges);
  }

  //////////////////////////////////////////////////////////////////////
  // draw
  //////////////////////////////////////////////////////////////////////

  void vulkan::draw(VkCommandBuffer commandBuffer,
                    uint32_t frameIndex)
  {
    VkDescriptorSet descriptorSets[2] = {
      descriptorSets0[frameIndex],
      descriptorSet1,
    };
    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipelineLayout,
                            0, 2, descriptorSets,
                            0, nullptr);

    vkCmdBindIndexBuffer(commandBuffer, vertexIndex.buffer, vertexIndex.indexOffset, VK_INDEX_TYPE_UINT16);
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

    VkDeviceSize vertexOffset{ 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexIndex.buffer, &vertexOffset);

    minecraft::vulkan::per_world const & world = worlds[0];

    for (int region = 0; region < world.descriptor->region_count; region++) {
      vkCmdBindVertexBuffers(commandBuffer, 1, 1, &world.regions[region].vertexBuffer, &vertexOffset);
      for (int configuration = 1; configuration < 64; configuration++) {
        int index_count = 6 * popcount(configuration);
        int first_index = index_buffer_configuration_offsets[configuration];
        int instance_count = world.regions[region].instanceCFG[configuration].count;
        int first_instance = world.regions[region].instanceCFG[configuration].offset / perInstanceSize;

        if (instance_count == 0)
          continue;

        vkCmdDrawIndexed(commandBuffer, index_count, instance_count, first_index, 0, first_instance);
      };
    }
  }
}
