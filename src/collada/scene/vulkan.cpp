#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "volk/volk.h"
#include "vulkan/vk_enum_string_helper.h"

#include "collada/inputs.h"
#include "collada/scene/vulkan.h"

#include "vulkan_helper.h"

#include "check.h"
#include "new.h"
#include "file.h"

inline static uint32_t vulkan_semantic_location(char const * const semantic, int semantic_index)
{
  if (strcmp(semantic, "POSITION") == 0 && semantic_index == 0) {
    return 0;
  }
  if (strcmp(semantic, "NORMAL") == 0 && semantic_index == 0) {
    return 1;
  }
  if (strcmp(semantic, "TEXCOORD") == 0 && semantic_index == 0) {
    return 2;
  }
  if (strcmp(semantic, "BLENDINDICES") == 0 && semantic_index == 0) {
    return 3;
  }
  if (strcmp(semantic, "BLENDWEIGHT") == 0 && semantic_index == 0) {
    return 4;
  }
  fprintf(stderr, "unknown semantic %s index %d\n", semantic, semantic_index);
  assert(false);
}

inline static VkFormat vulkan_format(collada::types::input_format format)
{
  switch (format) {
  case collada::types::input_format::FLOAT1: return VK_FORMAT_R32_SFLOAT;
  case collada::types::input_format::FLOAT2: return VK_FORMAT_R32G32_SFLOAT;
  case collada::types::input_format::FLOAT3: return VK_FORMAT_R32G32B32_SFLOAT;
  case collada::types::input_format::FLOAT4: return VK_FORMAT_R32G32B32A32_SFLOAT;
  case collada::types::input_format::INT1: return VK_FORMAT_R32_SINT;
  case collada::types::input_format::INT2: return VK_FORMAT_R32G32_SINT;
  case collada::types::input_format::INT3: return VK_FORMAT_R32G32B32_SINT;
  case collada::types::input_format::INT4: return VK_FORMAT_R32G32B32A32_SINT;
  default: assert(false);
  }
}


inline static uint32_t vulkan_load_layout(collada::types::inputs const & inputs,
                                          uint32_t binding,
                                          uint32_t start_offset,
                                          VkVertexInputAttributeDescription * vertexAttributeDescriptions)
{
  uint32_t offset = start_offset;
  for (int i = 0; i < inputs.elements_count; i++) {
    uint32_t location = vulkan_semantic_location(inputs.elements[i].semantic, inputs.elements[i].semantic_index);
    VkFormat format = vulkan_format(inputs.elements[i].format);
    vertexAttributeDescriptions[i].location = location;
    vertexAttributeDescriptions[i].binding = binding;
    vertexAttributeDescriptions[i].format = format;
    vertexAttributeDescriptions[i].offset = offset;
    offset += collada::inputs::format_size(inputs.elements[i].format);
  }
  return offset;
}

inline static void vulkan_vertex_input_states(collada::types::descriptor const * const descriptor,
                                              VkPipelineVertexInputStateCreateInfo * vertexInputStates,
                                              VkVertexInputBindingDescription * vertexBindingDescriptions)
{
  for (int i = 0; i < descriptor->inputs_list_count; i++) {
    collada::types::inputs const & inputs = descriptor->inputs_list[i];
    VkVertexInputAttributeDescription * vertexAttributeDescriptions = NewM<VkVertexInputAttributeDescription>(inputs.elements_count);
    uint32_t stride = vulkan_load_layout(inputs,
                                         0, // binding
                                         0, // start_offset
                                         vertexAttributeDescriptions);

    vertexBindingDescriptions[i] = {
      .binding = 0,
      .stride = stride,
      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    };

    vertexInputStates[i] = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
      .vertexBindingDescriptionCount = 1,
      .pVertexBindingDescriptions = &vertexBindingDescriptions[i],
      .vertexAttributeDescriptionCount = (uint32_t)inputs.elements_count,
      .pVertexAttributeDescriptions = vertexAttributeDescriptions,
    };
  }
}

namespace collada::scene {

  void vulkan::initial_state(VkInstance instance,
                             VkDevice device,
                             VkPhysicalDeviceProperties const & physicalDeviceProperties,
                             VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                             VkFormat colorFormat,
                             VkFormat depthFormat)
  {
    this->instance = instance;
    this->device = device;

    this->physicalDeviceProperties = physicalDeviceProperties;
    this->physicalDeviceMemoryProperties = physicalDeviceMemoryProperties;

    this->colorFormat = colorFormat;
    this->depthFormat = depthFormat;

    load_shader();
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

    vertexIndex.indexOffset = vertexSize; // + vertexJWStart;

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

    allocateFromMemoryRequirements(device,
                                   physicalDeviceMemoryProperties,
                                   memoryRequirements,
                                   memoryPropertyFlags,
                                   memoryAllocateFlags,
                                   1,
                                   &vertexIndex.memory);

    VK_CHECK(vkBindBufferMemory(device, vertexIndex.buffer, vertexIndex.memory, 0));

    // copy data

    void * vertexIndexMappedData;
    VK_CHECK(vkMapMemory(device, vertexIndex.memory, 0, vertexIndexBufferCreateInfo.size, 0, &vertexIndexMappedData));
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
  // uniform and storage buffers
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_uniform_buffers(collada::types::descriptor const * const descriptor)
  {
    VkMemoryRequirements memoryRequirements[uniformBufferDescriptorCount];
    VkDeviceSize offsets[uniformBufferDescriptorCount];

    shaderData.nodes = NewM<Node>(descriptor->nodes_count);
    shaderData.materialColors = NewM<MaterialColor>(descriptor->materials_count);

    uint32_t memoryRequirementsIndex = 0;
    // per-frame
    for (uint32_t i = 0; i < maxFrames; i++) {
      // scene buffer
      VkBufferCreateInfo sceneBufferCreateInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = (sizeof (Scene)),
        .usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      };

      VK_CHECK(vkCreateBuffer(device, &sceneBufferCreateInfo, nullptr, &shaderDataDevice.frame[i].sceneBuffer));
      vkGetBufferMemoryRequirements(device, shaderDataDevice.frame[i].sceneBuffer, &memoryRequirements[memoryRequirementsIndex++]);

      // nodes buffer
      VkBufferCreateInfo nodesBufferCreateInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = (sizeof (Node)) * descriptor->nodes_count,
        .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      };
      VK_CHECK(vkCreateBuffer(device, &nodesBufferCreateInfo, nullptr, &shaderDataDevice.frame[i].nodesBuffer));
      vkGetBufferMemoryRequirements(device, shaderDataDevice.frame[i].nodesBuffer, &memoryRequirements[memoryRequirementsIndex++]);
    };

    // material color buffer
    VkBufferCreateInfo materialColorsBufferCreateInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = (sizeof (MaterialColor)) * descriptor->materials_count,
      .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };
    VK_CHECK(vkCreateBuffer(device, &materialColorsBufferCreateInfo, nullptr, &shaderDataDevice.constant.materialColorsBuffer));
    vkGetBufferMemoryRequirements(device, shaderDataDevice.constant.materialColorsBuffer, &memoryRequirements[memoryRequirementsIndex++]);

    assert(memoryRequirementsIndex == uniformBufferDescriptorCount);

    VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
    VkMemoryAllocateFlags memoryAllocateFlags{ };
    allocateFromMemoryRequirements2(device,
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
      shaderDataDevice.frame[i].sceneMapped = (void *)(((size_t)shaderDataDevice.mappedData) + shaderDataDevice.frame[i].sceneOffset);
      VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.frame[i].sceneBuffer, shaderDataDevice.memory, shaderDataDevice.frame[i].sceneOffset));

      shaderDataDevice.frame[i].nodesOffset = offsets[offsetsIndex];
      shaderDataDevice.frame[i].nodesSize = memoryRequirements[offsetsIndex++].size;
      shaderDataDevice.frame[i].nodesMapped = (void *)(((size_t)shaderDataDevice.mappedData) + shaderDataDevice.frame[i].nodesOffset);
      VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.frame[i].nodesBuffer, shaderDataDevice.memory, shaderDataDevice.frame[i].nodesOffset));
    }
    shaderDataDevice.constant.materialColorsOffset = offsets[offsetsIndex];
    shaderDataDevice.constant.materialColorsSize = memoryRequirements[offsetsIndex++].size;
    shaderDataDevice.constant.materialColorsMapped = (void *)(((size_t)shaderDataDevice.mappedData) + shaderDataDevice.constant.materialColorsOffset);
    VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.constant.materialColorsBuffer, shaderDataDevice.memory, shaderDataDevice.constant.materialColorsOffset));

    assert(offsetsIndex == uniformBufferDescriptorCount);
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor sets
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_descriptor_sets()
  {
    //
    // pool
    //
    VkDescriptorPoolSize descriptorPoolSizes[2]{
      {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = maxFrames + 1, // why +1?
      },
      {
        .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .descriptorCount = maxFrames + 1, // +1 for materialColors
      }
    };
    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .maxSets = 2,
      .poolSizeCount = 2,
      .pPoolSizes = descriptorPoolSizes
    };
    VK_CHECK(vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

    //
    // uniform buffer descriptor set layout/allocation (set 0, per-frame)
    //
    {
      constexpr int bindingCount = 2;
      VkDescriptorSetLayoutBinding descriptorSetLayoutBindings[bindingCount]{
        {
          .binding = 0,
          .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_VERTEX_BIT
        },
        {
          .binding = 1,
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
      constexpr int bindingCount = 1;
      VkDescriptorSetLayoutBinding descriptorSetLayoutBindings[bindingCount]{
        {
          .binding = 0,
          .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
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

  void vulkan::write_descriptor_sets(collada::types::descriptor const * const descriptor)
  {
    VkWriteDescriptorSet writeDescriptorSets[uniformBufferDescriptorCount];
    uint32_t writeIndex = 0;

    VkDescriptorBufferInfo sceneDescriptorBufferInfos[maxFrames];
    VkDescriptorBufferInfo nodesDescriptorBufferInfos[maxFrames];

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
      nodesDescriptorBufferInfos[i] = {
        .buffer = shaderDataDevice.frame[i].nodesBuffer,
        .offset = 0,
        .range = shaderDataDevice.frame[i].nodesSize,
      };
      writeDescriptorSets[writeIndex++] = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptorSets0[i],
        .dstBinding = 1,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .pBufferInfo = &nodesDescriptorBufferInfos[i]
      };
    }

    VkDescriptorBufferInfo materialColorsDescriptorBufferInfo{
      .buffer = shaderDataDevice.constant.materialColorsBuffer,
      .offset = 0,
      .range = shaderDataDevice.constant.materialColorsSize,
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
      .pBufferInfo = &materialColorsDescriptorBufferInfo
    };

    assert(writeIndex == uniformBufferDescriptorCount);

    vkUpdateDescriptorSets(device, writeIndex, writeDescriptorSets, 0, nullptr);
  }

  //////////////////////////////////////////////////////////////////////
  // material constants
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_material_constants(collada::types::descriptor const * const descriptor)
  {
    // store
    for (int i = 0; i < descriptor->materials_count; i++) {
      collada::types::effect const * const effect = descriptor->materials[i]->effect;
      switch (effect->type) {
      case collada::types::effect_type::BLINN:
        shaderData.materialColors[i].emission = *(XMFLOAT4 *)(&effect->blinn.emission.color);
        shaderData.materialColors[i].ambient = *(XMFLOAT4 *)(&effect->blinn.ambient.color);
        shaderData.materialColors[i].diffuse = *(XMFLOAT4 *)(&effect->blinn.diffuse.color);
        shaderData.materialColors[i].specular = *(XMFLOAT4 *)(&effect->blinn.specular.color);
        break;
      case collada::types::effect_type::LAMBERT:
        shaderData.materialColors[i].emission = *(XMFLOAT4 *)(&effect->lambert.emission.color);
        shaderData.materialColors[i].ambient = *(XMFLOAT4 *)(&effect->lambert.ambient.color);
        shaderData.materialColors[i].diffuse = *(XMFLOAT4 *)(&effect->lambert.diffuse.color);
        shaderData.materialColors[i].specular = XMFLOAT4{0, 0, 0, 0};
        break;
      case collada::types::effect_type::PHONG:
        shaderData.materialColors[i].emission = *(XMFLOAT4 *)(&effect->phong.emission.color);
        shaderData.materialColors[i].ambient = *(XMFLOAT4 *)(&effect->phong.ambient.color);
        shaderData.materialColors[i].diffuse = *(XMFLOAT4 *)(&effect->phong.diffuse.color);
        shaderData.materialColors[i].specular = *(XMFLOAT4 *)(&effect->phong.specular.color);
        break;
      case collada::types::effect_type::CONSTANT:
        shaderData.materialColors[i].emission = *(XMFLOAT4 *)(&effect->constant.color);
        shaderData.materialColors[i].ambient = XMFLOAT4{0, 0, 0, 0};
        shaderData.materialColors[i].diffuse = XMFLOAT4{0, 0, 0, 0};
        shaderData.materialColors[i].specular = XMFLOAT4{0, 0, 0, 0};
        break;
      default:
        assert(false);
        break;
      }
    }

    // copy
    memcpy(shaderDataDevice.constant.materialColorsMapped, &shaderData.materialColors[0], (sizeof (MaterialColor)) * descriptor->materials_count);

    // flush

    VkDeviceSize materialColorsFlushSize{ shaderDataDevice.constant.materialColorsSize };
    VkMappedMemoryRange shaderDataMemoryRanges[1]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = shaderDataDevice.memory,
        .offset = shaderDataDevice.constant.materialColorsOffset,
        .size = roundAlignment(materialColorsFlushSize, physicalDeviceProperties.limits.nonCoherentAtomSize),
      },
    };
    vkFlushMappedMemoryRanges(device, 1, shaderDataMemoryRanges);
  }

  //////////////////////////////////////////////////////////////////////
  // shader
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_shader()
  {
    uint32_t shaderSize;
    void const * shaderStart = file::open("shader/collada.spv", &shaderSize);

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

  void vulkan::create_pipelines(collada::types::descriptor const * const descriptor)
  {
    VkPushConstantRange pushConstantRanges[1]{
      {
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
        .offset = 0,
        .size = (sizeof (PushConstant))
      }
    };

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      .setLayoutCount = 2,
      .pSetLayouts = descriptorSetLayouts,
      .pushConstantRangeCount = 1,
      .pPushConstantRanges = pushConstantRanges
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
      .cullMode = VK_CULL_MODE_BACK_BIT,
      //.cullMode = VK_CULL_MODE_NONE,
      .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
      .lineWidth = 1.0f
    };
    VkPipelineMultisampleStateCreateInfo multisampleState{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
      .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
    };

    VkPipelineVertexInputStateCreateInfo * vertexInputStates = NewM<VkPipelineVertexInputStateCreateInfo>(descriptor->inputs_list_count);
    VkVertexInputBindingDescription * vertexBindingDescriptions = NewM<VkVertexInputBindingDescription>(descriptor->inputs_list_count);
    vulkan_vertex_input_states(descriptor,
                               vertexInputStates,
                               vertexBindingDescriptions);

    VkGraphicsPipelineCreateInfo * pipelineCreateInfos = NewM<VkGraphicsPipelineCreateInfo>(descriptor->inputs_list_count);

    for (int i = 0; i < descriptor->inputs_list_count; i++) {
      pipelineCreateInfos[i] = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = &renderingCreateInfo,
        .stageCount = 2,
        .pStages = shaderStages,
        .pVertexInputState = &vertexInputStates[i],
        .pInputAssemblyState = &inputAssemblyState,
        .pViewportState = &viewportState,
        .pRasterizationState = &rasterizationState,
        .pMultisampleState = &multisampleState,
        .pDepthStencilState = &depthStencilState,
        .pColorBlendState = &colorBlendState,
        .pDynamicState = &dynamicState,
        .layout = pipelineLayout
      };
    };

    pipelines = NewM<VkPipeline>(descriptor->inputs_list_count);
    VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, descriptor->inputs_list_count, pipelineCreateInfos, nullptr, pipelines));

    free(pipelineCreateInfos);

    free(vertexBindingDescriptions);
    for (int i = 0; i < descriptor->inputs_list_count; i++) {
      free((void *)vertexInputStates[i].pVertexAttributeDescriptions);
    }
    free(vertexInputStates);
  }

  //////////////////////////////////////////////////////////////////////
  // draw
  //////////////////////////////////////////////////////////////////////

  void vulkan::draw_geometry(types::geometry const & geometry,
                             types::instance_material const * const instance_materials,
                             int const instance_materials_count)
  {
    types::mesh const& mesh = geometry.mesh;

    vkCmdBindIndexBuffer(commandBuffer, vertexIndex.buffer, vertexIndex.indexOffset + mesh.index_buffer_offset, VK_INDEX_TYPE_UINT32);

    for (int j = 0; j < instance_materials_count; j++) {
      types::instance_material const& instance_material = instance_materials[j];
      types::triangles const& triangles = mesh.triangles[instance_material.element_index];

      VkShaderStageFlags stageFlags{ VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT };
      uint32_t materialIndex = instance_material.material_index;
      uint32_t offset{ (offsetof (PushConstant, materialIndex)) };
      vkCmdPushConstants(commandBuffer, pipelineLayout, stageFlags, offset, (sizeof (uint32_t)), &materialIndex);

      VkDeviceSize vertexOffset{ (VkDeviceSize)mesh.vertex_buffer_offset };
      vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexIndex.buffer, &vertexOffset);
      vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[triangles.inputs_index]);

      uint32_t indexCount = triangles.count * 3;
      vkCmdDrawIndexed(commandBuffer, indexCount, 1, triangles.index_offset, 0, 0);
    }
  }

  void vulkan::draw_instance_geometries(types::instance_geometry const * const instance_geometries,
                                        int const instance_geometries_count)
  {
    for (int i = 0; i < instance_geometries_count; i++) {
      types::instance_geometry const &instance_geometry = instance_geometries[i];
      draw_geometry(*instance_geometry.geometry,
                    instance_geometry.instance_materials,
                    instance_geometry.instance_materials_count);
    }
  }

  void vulkan::transfer_transforms(XMMATRIX const & projection,
                                   XMMATRIX const & view,
                                   XMVECTOR const & light_position_world,
                                   int nodes_count,
                                   instance_types::node const * const node_instances)
  {
    // store
    XMStoreFloat4x4(&shaderData.scene.projection, projection);
    XMVECTOR lightPositionView = XMVector3Transform(light_position_world, view);
    XMStoreFloat4(&shaderData.scene.lightPosition, lightPositionView);

    for (int i = 0; i < nodes_count; i++) {
      XMMATRIX model_view = node_instances[i].world * view;
      XMStoreFloat4x4(&shaderData.nodes[i].modelView, model_view);
    }

    // copy
    memcpy(shaderDataDevice.frame[frameIndex].sceneMapped, &shaderData.scene, (sizeof (Scene)));
    memcpy(shaderDataDevice.frame[frameIndex].nodesMapped, &shaderData.nodes[0], (sizeof (Node)) * nodes_count);

    // flush

    VkDeviceSize sceneFlushSize{ shaderDataDevice.frame[frameIndex].sceneSize };
    VkDeviceSize nodesFlushSize{ shaderDataDevice.frame[frameIndex].nodesSize };
    //fprintf(stderr, "sceneFlushSize %ld\n", sceneFlushSize);
    //fprintf(stderr, "nodesFlushSize %ld\n", nodesFlushSize);
    VkMappedMemoryRange shaderDataMemoryRanges[2]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = shaderDataDevice.memory,
        .offset = shaderDataDevice.frame[frameIndex].sceneOffset,
        .size = roundAlignment(sceneFlushSize, physicalDeviceProperties.limits.nonCoherentAtomSize),
      },
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = shaderDataDevice.memory,
        .offset = shaderDataDevice.frame[frameIndex].nodesOffset,
        .size = roundAlignment(nodesFlushSize, physicalDeviceProperties.limits.nonCoherentAtomSize),
      }
    };
    vkFlushMappedMemoryRanges(device, 2, shaderDataMemoryRanges);
  }

  void vulkan::draw_node(int32_t node_index,
                         types::node const & node,
                         instance_types::node const & node_instance)
  {
    VkShaderStageFlags stageFlags{ VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT };
    uint32_t offset{ (offsetof (PushConstant, nodeIndex)) };
    vkCmdPushConstants(commandBuffer, pipelineLayout, stageFlags, offset, (sizeof (uint32_t)), &node_index);

    draw_instance_geometries(node.instance_geometries, node.instance_geometries_count);
  }

  void vulkan::change_frame(VkCommandBuffer commandBuffer, uint32_t frameIndex)
  {
    this->commandBuffer = commandBuffer;
    this->frameIndex = frameIndex;
    VkDescriptorSet descriptorSets[2] = {
      descriptorSets0[frameIndex],
      descriptorSet1,
    };
    vkCmdBindDescriptorSets(commandBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipelineLayout,
                            0, 2, descriptorSets,
                            0, nullptr);
  }

  void vulkan::destroy_all(collada::types::descriptor const * const descriptor)
  {
    free(shaderData.nodes);
    free(shaderData.materialColors);

    vkDestroyBuffer(device, vertexIndex.buffer, nullptr);
    vkFreeMemory(device, vertexIndex.memory, nullptr);

    for (uint32_t i = 0; i < maxFrames; i++) {
      vkDestroyBuffer(device, shaderDataDevice.frame[i].sceneBuffer, nullptr);
      vkDestroyBuffer(device, shaderDataDevice.frame[i].nodesBuffer, nullptr);
    }
    vkDestroyBuffer(device, shaderDataDevice.constant.materialColorsBuffer, nullptr);
    vkFreeMemory(device, shaderDataDevice.memory, nullptr);

    vkDestroyDescriptorSetLayout(device, descriptorSetLayouts[0], nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayouts[1], nullptr);
    vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    for (int i = 0; i < descriptor->inputs_list_count; i++) {
      vkDestroyPipeline(device, pipelines[i], nullptr);
    }
    free(pipelines);
    vkDestroyShaderModule(device, shaderModule, nullptr);
  }
}
