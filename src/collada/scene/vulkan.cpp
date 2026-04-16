#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "volk/volk.h"
#include "vulkan/vk_enum_string_helper.h"

#include "collada/inputs.h"
#include "collada/scene/vulkan.h"

#include "minmax.h"
#include "vulkan_helper.h"
#include "dds/validate.h"
#include "dds/vulkan.h"

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
                             VkQueue queue,
                             VkCommandPool commandPool,
                             VkPhysicalDeviceProperties const & physicalDeviceProperties,
                             VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
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
  // uniform and storage buffers
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_uniform_buffers(collada::types::descriptor const * const descriptor)
  {
    VkMemoryRequirements memoryRequirements[uniformBufferDescriptorCount];
    VkDeviceSize offsets[uniformBufferDescriptorCount];

    shaderData.nodes = NewM<Node>(descriptor->nodes_count);
    shaderData.materialColorImages = NewM<MaterialColorImage>(descriptor->materials_count);

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
    VkBufferCreateInfo materialColorImagesBufferCreateInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = (sizeof (MaterialColorImage)) * descriptor->materials_count,
      .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };
    VK_CHECK(vkCreateBuffer(device, &materialColorImagesBufferCreateInfo, nullptr, &shaderDataDevice.constant.materialColorImagesBuffer));
    vkGetBufferMemoryRequirements(device, shaderDataDevice.constant.materialColorImagesBuffer, &memoryRequirements[memoryRequirementsIndex++]);

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
      shaderDataDevice.frame[i].sceneMapped = (void *)(((size_t)shaderDataDevice.mappedData) + shaderDataDevice.frame[i].sceneOffset);
      VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.frame[i].sceneBuffer, shaderDataDevice.memory, shaderDataDevice.frame[i].sceneOffset));

      shaderDataDevice.frame[i].nodesOffset = offsets[offsetsIndex];
      shaderDataDevice.frame[i].nodesSize = memoryRequirements[offsetsIndex++].size;
      shaderDataDevice.frame[i].nodesMapped = (void *)(((size_t)shaderDataDevice.mappedData) + shaderDataDevice.frame[i].nodesOffset);
      VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.frame[i].nodesBuffer, shaderDataDevice.memory, shaderDataDevice.frame[i].nodesOffset));
    }
    shaderDataDevice.constant.materialColorImagesOffset = offsets[offsetsIndex];
    shaderDataDevice.constant.materialColorImagesSize = memoryRequirements[offsetsIndex++].size;
    shaderDataDevice.constant.materialColorImagesMapped = (void *)(((size_t)shaderDataDevice.mappedData) + shaderDataDevice.constant.materialColorImagesOffset);
    VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.constant.materialColorImagesBuffer, shaderDataDevice.memory, shaderDataDevice.constant.materialColorImagesOffset));

    assert(offsetsIndex == uniformBufferDescriptorCount);
  }

  //////////////////////////////////////////////////////////////////////
  // descriptor sets
  //////////////////////////////////////////////////////////////////////

  void vulkan::create_descriptor_sets(collada::types::descriptor const * const descriptor)
  {
    //
    // pool
    //
    constexpr int descriptorPoolSizesCount = 4;
    VkDescriptorPoolSize descriptorPoolSizes[descriptorPoolSizesCount]{
      {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = maxFrames,
      },
      {
        .type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .descriptorCount = maxFrames + 1, // +1 for materialColorImages
      },
      {
        .type = VK_DESCRIPTOR_TYPE_SAMPLER,
        .descriptorCount = 1,
      },
      {
        .type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
        .descriptorCount = (uint32_t)descriptor->images_count + 1, // +1 for shadow sampler
      },
    };
    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .maxSets = maxFrames + 1, // +1 for descriptorSet1
      .poolSizeCount = descriptorPoolSizesCount,
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
          .stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_GEOMETRY_BIT
        },
        {
          .binding = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_GEOMETRY_BIT
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
      constexpr int bindingCount = 4;
      VkDescriptorSetLayoutBinding descriptorSetLayoutBindings[bindingCount]{
        {
          .binding = 0,
          .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
        {
          .binding = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
        { // shadow sampled image
          .binding = 2,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
        },
        { // scene images
          .binding = 3,
          .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
          .descriptorCount = (uint32_t)descriptor->images_count,
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

  void vulkan::write_descriptor_sets(collada::types::descriptor const * const descriptor)
  {
    VkWriteDescriptorSet writeDescriptorSets[bindingCount];
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

    VkDescriptorBufferInfo materialColorImagesDescriptorBufferInfo{
      .buffer = shaderDataDevice.constant.materialColorImagesBuffer,
      .offset = 0,
      .range = shaderDataDevice.constant.materialColorImagesSize,
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
      .pBufferInfo = &materialColorImagesDescriptorBufferInfo
    };
    VkDescriptorImageInfo samplerDescriptorImageInfo = {
      .sampler = linearSampler,
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 1,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER,
      .pImageInfo = &samplerDescriptorImageInfo
    };
    VkDescriptorImageInfo sampledImageDescriptorImageInfo = {
      .imageView = shadowDepthImageView,
      .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
    };
    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 2,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
      .pImageInfo = &sampledImageDescriptorImageInfo
    };

    // scene images
    VkDescriptorImageInfo * sceneDescriptorImageInfos = NewM<VkDescriptorImageInfo>(descriptor->images_count);
    for (int i = 0; i < descriptor->images_count; i++) {
      sceneDescriptorImageInfos[i] = {
        .imageView = images[i].imageView,
        .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
      };
    }

    writeDescriptorSets[writeIndex++] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = descriptorSet1,
      .dstBinding = 3,
      .descriptorCount = (uint32_t)descriptor->images_count,
      .descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
      .pImageInfo = sceneDescriptorImageInfos
    };

    assert(writeIndex == bindingCount);
    vkUpdateDescriptorSets(device, writeIndex, writeDescriptorSets, 0, nullptr);
    free(sceneDescriptorImageInfos);
  }

  //////////////////////////////////////////////////////////////////////
  // material constants
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_material_constants(collada::types::descriptor const * const descriptor)
  {
    constexpr collada::types::color_or_texture_type TEXTURE = collada::types::color_or_texture_type::TEXTURE;
    // store
    for (int i = 0; i < descriptor->materials_count; i++) {
      collada::types::effect const * const effect = descriptor->materials[i]->effect;
      MaterialColorImage & mci = shaderData.materialColorImages[i];
      switch (effect->type) {
      case collada::types::effect_type::BLINN:
        mci.color.emission = *(XMFLOAT4 *)(&effect->blinn.emission.color);
        mci.color.ambient = *(XMFLOAT4 *)(&effect->blinn.ambient.color);
        mci.color.diffuse = *(XMFLOAT4 *)(&effect->blinn.diffuse.color);
        mci.color.specular = *(XMFLOAT4 *)(&effect->blinn.specular.color);
        mci.image.emission = (effect->blinn.emission.type == TEXTURE) ? effect->blinn.emission.texture.image_index : -1;
        mci.image.ambient = (effect->blinn.ambient.type == TEXTURE) ? effect->blinn.ambient.texture.image_index : -1;
        mci.image.diffuse = (effect->blinn.diffuse.type == TEXTURE) ? effect->blinn.diffuse.texture.image_index : -1;
        mci.image.specular = (effect->blinn.specular.type == TEXTURE) ? effect->blinn.specular.texture.image_index : -1;
        break;
      case collada::types::effect_type::LAMBERT:
        mci.color.emission = *(XMFLOAT4 *)(&effect->lambert.emission.color);
        mci.color.ambient = *(XMFLOAT4 *)(&effect->lambert.ambient.color);
        mci.color.diffuse = *(XMFLOAT4 *)(&effect->lambert.diffuse.color);
        mci.color.specular = XMFLOAT4{0, 0, 0, 0};
        mci.image.emission = (effect->lambert.emission.type == TEXTURE) ? effect->lambert.emission.texture.image_index : -1;
        mci.image.ambient = (effect->lambert.ambient.type == TEXTURE) ? effect->lambert.ambient.texture.image_index : -1;
        mci.image.diffuse = (effect->lambert.diffuse.type == TEXTURE) ? effect->lambert.diffuse.texture.image_index : -1;
        mci.image.specular = -1;
        break;
      case collada::types::effect_type::PHONG:
        mci.color.emission = *(XMFLOAT4 *)(&effect->phong.emission.color);
        mci.color.ambient = *(XMFLOAT4 *)(&effect->phong.ambient.color);
        mci.color.diffuse = *(XMFLOAT4 *)(&effect->phong.diffuse.color);
        mci.color.specular = *(XMFLOAT4 *)(&effect->phong.specular.color);
        mci.image.emission = (effect->phong.emission.type == TEXTURE) ? effect->phong.emission.texture.image_index : -1;
        mci.image.ambient = (effect->phong.ambient.type == TEXTURE) ? effect->phong.ambient.texture.image_index : -1;
        mci.image.diffuse = (effect->phong.diffuse.type == TEXTURE) ? effect->phong.diffuse.texture.image_index : -1;
        mci.image.specular = (effect->phong.specular.type == TEXTURE) ? effect->phong.specular.texture.image_index : -1;
        break;
      case collada::types::effect_type::CONSTANT:
        mci.color.emission = *(XMFLOAT4 *)(&effect->constant.color);
        mci.color.ambient = XMFLOAT4{0, 0, 0, 0};
        mci.color.diffuse = XMFLOAT4{0, 0, 0, 0};
        mci.color.specular = XMFLOAT4{0, 0, 0, 0};
        mci.image.emission = -1;
        mci.image.ambient = -1;
        mci.image.diffuse = -1;
        mci.image.specular = -1;
        break;
      default:
        assert(false);
        break;
      }
    }

    // copy
    memcpy(shaderDataDevice.constant.materialColorImagesMapped, &shaderData.materialColorImages[0], (sizeof (MaterialColorImage)) * descriptor->materials_count);

    // flush

    VkMappedMemoryRange mappedMemoryRanges[1]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = shaderDataDevice.memory,
        .offset = shaderDataDevice.constant.materialColorImagesOffset,
        .size = shaderDataDevice.constant.materialColorImagesSize,
      },
    };
    alignMappedMemoryRanges(physicalDeviceProperties.limits.nonCoherentAtomSize,
                            shaderDataDevice.memorySize,
                            1, mappedMemoryRanges);
    vkFlushMappedMemoryRanges(device, 1, mappedMemoryRanges);
  }

  //////////////////////////////////////////////////////////////////////
  // material textures
  //////////////////////////////////////////////////////////////////////

  void vulkan::load_images(collada::types::descriptor const * const descriptor)
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
    images = NewM<Image>(descriptor->images_count);

    for (int i = 0; i < descriptor->images_count; i++) {
      createImageFromFilenameDDS(device,
                                 queue,
                                 commandBuffer,
                                 fence,
                                 physicalDeviceProperties.limits.nonCoherentAtomSize,
                                 physicalDeviceMemoryProperties,
                                 descriptor->images[i]->uri,
                                 &images[i].image,
                                 &images[i].memory,
                                 &images[i].imageView);
    }

    // cleanup

    vkDestroyFence(device, fence, nullptr);
    vkFreeCommandBuffers(device,
                         commandPool,
                         1,
                         &commandBuffer);
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
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_GEOMETRY_BIT,
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

    VkPipelineShaderStageCreateInfo geometryShaderStages[3]{
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = shaderModule,
        .pName = "VSGeometryMain"
      },
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_GEOMETRY_BIT,
        .module = shaderModule,
        .pName = "GSGeometryMain"
      },
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = shaderModule,
        .pName = "PSGeometryMain"
      }
    };

    VkPipelineShaderStageCreateInfo shadowShaderStages[2]{
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = shaderModule,
        .pName = "VSShadowMain"
      },
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = shaderModule,
        .pName = "PSShadowMain"
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

    VkPipelineRenderingCreateInfo shadowRenderingCreateInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
      //.colorAttachmentCount = 1,
      //.pColorAttachmentFormats = &colorFormat,
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
    VkPipelineRasterizationStateCreateInfo shadowRasterizationState{
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

    VkPipelineVertexInputStateCreateInfo * vertexInputStates = NewM<VkPipelineVertexInputStateCreateInfo>(descriptor->inputs_list_count);
    VkVertexInputBindingDescription * vertexBindingDescriptions = NewM<VkVertexInputBindingDescription>(descriptor->inputs_list_count);
    vulkan_vertex_input_states(descriptor,
                               vertexInputStates,
                               vertexBindingDescriptions);

    int pipelineCount = descriptor->inputs_list_count * shaderVariantCount;
    VkGraphicsPipelineCreateInfo * pipelineCreateInfos = NewM<VkGraphicsPipelineCreateInfo>(pipelineCount);

    for (int i = 0; i < descriptor->inputs_list_count; i++) {
      // shadow
      pipelineCreateInfos[i * shaderVariantCount + 0] = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = &shadowRenderingCreateInfo,
        .stageCount = 2,
        .pStages = shadowShaderStages,
        .pVertexInputState = &vertexInputStates[i],
        .pInputAssemblyState = &inputAssemblyState,
        .pViewportState = &viewportState,
        .pRasterizationState = &shadowRasterizationState,
        .pMultisampleState = &multisampleState,
        .pDepthStencilState = &depthStencilState,
        .pColorBlendState = &colorBlendState,
        .pDynamicState = &dynamicState,
        .layout = pipelineLayout
      };

      // non-shadow
      pipelineCreateInfos[i * shaderVariantCount + 1] = {
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

      // geometry
      pipelineCreateInfos[i * shaderVariantCount + 2] = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = &renderingCreateInfo,
        .stageCount = 3,
        .pStages = geometryShaderStages,
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

    pipelines = NewM<VkPipeline>(pipelineCount);
    VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, pipelineCount, pipelineCreateInfos, nullptr, pipelines));

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
      int materialIndex = instance_material.material_index;
      if (materialIndex == excludeMaterialIndex) {
        continue;
      }
      types::triangles const& triangles = mesh.triangles[instance_material.element_index];

      VkShaderStageFlags stageFlags{ VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_GEOMETRY_BIT };
      constexpr uint32_t offset{ (offsetof (PushConstant, materialIndex)) };
      vkCmdPushConstants(commandBuffer, pipelineLayout, stageFlags, offset, (sizeof (uint32_t)), &materialIndex);

      VkDeviceSize vertexOffset{ (VkDeviceSize)mesh.vertex_buffer_offset };
      vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexIndex.buffer, &vertexOffset);
      vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[triangles.inputs_index * shaderVariantCount + pipelineIndex]);

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
                                   XMMATRIX const & shadowProjection,
                                   XMMATRIX const & shadowView,
                                   XMVECTOR const & light_position_world,
                                   int nodes_count,
                                   instance_types::node const * const node_instances)
  {
    // store
    XMStoreFloat4x4(&shaderData.scene.projection, projection);
    XMStoreFloat4x4(&shaderData.scene.view, view);
    XMStoreFloat4x4(&shaderData.scene.shadowProjection, shadowProjection);
    XMStoreFloat4x4(&shaderData.scene.shadowView, shadowView);
    XMVECTOR lightPositionView = XMVector3Transform(light_position_world, view);
    XMStoreFloat4(&shaderData.scene.lightPosition, lightPositionView);

    for (int i = 0; i < nodes_count; i++) {
      XMStoreFloat4x4(&shaderData.nodes[i].world, node_instances[i].world);
    }

    // copy
    memcpy(shaderDataDevice.frame[frameIndex].sceneMapped, &shaderData.scene, (sizeof (Scene)));
    memcpy(shaderDataDevice.frame[frameIndex].nodesMapped, &shaderData.nodes[0], (sizeof (Node)) * nodes_count);

    // flush

    VkMappedMemoryRange mappedMemoryRanges[2]{
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = shaderDataDevice.memory,
        .offset = shaderDataDevice.frame[frameIndex].sceneOffset,
        .size = shaderDataDevice.frame[frameIndex].sceneSize,
      },
      {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = shaderDataDevice.memory,
        .offset = shaderDataDevice.frame[frameIndex].nodesOffset,
        .size = shaderDataDevice.frame[frameIndex].nodesSize,
      }
    };
    alignMappedMemoryRanges(physicalDeviceProperties.limits.nonCoherentAtomSize,
                            shaderDataDevice.memorySize,
                            2,
                            mappedMemoryRanges);
    vkFlushMappedMemoryRanges(device, 2, mappedMemoryRanges);
  }

  void vulkan::draw_node(int32_t node_index,
                         types::node const & node,
                         instance_types::node const & node_instance)
  {
    VkShaderStageFlags stageFlags{ VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_GEOMETRY_BIT };
    constexpr uint32_t offset{ (offsetof (PushConstant, nodeIndex)) };
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
    for (int i = 0; i < descriptor->images_count; i++) {
      vkDestroyImage(device, images[i].image, nullptr);
      vkDestroyImageView(device, images[i].imageView, nullptr);
      vkFreeMemory(device, images[i].memory, nullptr);
    }
    free(images);

    free(shaderData.nodes);
    free(shaderData.materialColorImages);

    vkDestroyBuffer(device, vertexIndex.buffer, nullptr);
    vkFreeMemory(device, vertexIndex.memory, nullptr);

    for (uint32_t i = 0; i < maxFrames; i++) {
      vkDestroyBuffer(device, shaderDataDevice.frame[i].sceneBuffer, nullptr);
      vkDestroyBuffer(device, shaderDataDevice.frame[i].nodesBuffer, nullptr);
    }
    vkDestroyBuffer(device, shaderDataDevice.constant.materialColorImagesBuffer, nullptr);
    vkFreeMemory(device, shaderDataDevice.memory, nullptr);

    vkDestroyDescriptorSetLayout(device, descriptorSetLayouts[0], nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayouts[1], nullptr);
    vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    int pipelineCount = descriptor->inputs_list_count * shaderVariantCount;
    for (int i = 0; i < pipelineCount; i++) {
      vkDestroyPipeline(device, pipelines[i], nullptr);
    }
    free(pipelines);
    vkDestroyShaderModule(device, shaderModule, nullptr);
  }
}
