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

    static constexpr int perVertexSize = (3 + 3 + 2) * 2;
    static constexpr int perInstanceSize = (3 + 1 + 3 + 1) * 2;

    void initial_state(VkInstance instance,
                       VkDevice device,
                       VkQueue queue,
                       VkCommandPool commandPool,
                       VkPhysicalDeviceProperties physicalDeviceProperties,
                       VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties,
                       VkFormat colorFormat,
                       VkFormat depthFormat);
    void init();
    void load_vertex_index_buffer(char const * vertex_filename,
                                  char const * index_filename);
    void load_shader();
    void create_pipeline();
    void load_worlds();
    void draw(VkCommandBuffer commandBuffer);
  };
}
