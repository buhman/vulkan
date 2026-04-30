#pragma once

#include "volk/volk.h"

#include "minecraft/vulkan/per_world.h"

namespace minecraft::vulkan {

  struct vulkan {
    struct {
      VkDeviceSize jointWeightOffset;
      VkDeviceSize indexOffset;
      VkBuffer buffer;
      VkDeviceMemory memory;
    } vertexIndex;

    // externally initialized, opaque handle
    VkInstance instance;
    VkDevice device;
    VkQueue queue;
    VkCommandPool commandPool;
    // externally initialized, structures
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
    // externally initialized, enum
    VkFormat colorFormat;
    VkFormat depthFormat;

    //
    // method initialized
    //
    VkPipelineLayout pipelineLayout;
    VkShaderModule shaderModule;
    VkPipeline pipeline;

    per_world * worlds;

    void init();
    void load_vertex_index_buffer(char const * vertex_filename,
                                  char const * index_filename);
    void load_shader();
    void create_pipeline();
    void load_worlds();
    void draw(VkCommandBuffer commandBuffer);
  };
}
