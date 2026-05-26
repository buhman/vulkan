#pragma once

#include "renpy/interpreter.h"

namespace renpy {
  struct Image {
    VkImage image;
    VkDeviceMemory memory;
    VkImageView imageView;
  };

  struct ImageInstance {
    struct {
      int16_t width;
      int16_t height;
    } size;
    struct {
      int16_t x;
      int16_t y;
    } topLeft;
    uint32_t color;
    int16_t imageIndex;
    int16_t _padding;
  };

  static_assert((sizeof (ImageInstance)) == 16);

  struct vulkan {
    static constexpr int perVertexSize = (4) * 2;
    static constexpr int perInstanceSize = (sizeof (ImageInstance));
    static constexpr int maximumImageCount = 16;

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
    VkSampler linearSampler;

    // internal vulkan state
    VkPipelineLayout pipelineLayout;
    VkShaderModule shaderModule;
    VkPipeline pipeline;
    VertexIndex vertexIndex;

    VkDeviceSize instanceBufferOffset[2];
    VkBuffer instanceBuffer;
    VkDeviceMemory instanceMemory;
    VkDeviceSize instanceMemorySize;
    ImageInstance * instanceMappedData;

    VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };
    static constexpr int descriptorSetLayoutCount = 1;
    VkDescriptorSetLayout descriptorSetLayouts[descriptorSetLayoutCount]; // unrelated to maxFrames, unrelated to descriptorCount
    VkDescriptorSet descriptorSet0;

    Image * images;

    void initial_state(VkInstance instance,
                       VkDevice device,
                       VkQueue queue,
                       VkCommandPool commandPool,
                       VkPhysicalDeviceProperties physicalDeviceProperties,
                       VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties,
                       VkFormat colorFormat,
                       VkFormat depthFormat,
                       VkSampler linearSampler);
    void init();
    void load_vertex_index_buffer();
    void load_shader();
    void create_descriptor_sets();
    void write_descriptor_sets();
    void load_image_inner(VkCommandBuffer commandBuffer, VkFence fence, int i, char const * filename);
    void load_images();
    void create_pipeline();
    void create_instance_buffers();
    void draw(VkCommandBuffer commandBuffer,
              uint32_t frameIndex,
              renpy::interpreter const& state);

  };
}
