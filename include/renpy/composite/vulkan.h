#pragma once

namespace renpy::composite {

  struct vulkan {
    static constexpr int perVertexSize = (4) * 2;

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

    VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };
    static constexpr int descriptorSetLayoutCount = 1;
    VkDescriptorSetLayout descriptorSetLayouts[descriptorSetLayoutCount]; // unrelated to maxFrames, unrelated to descriptorCount
    VkDescriptorSet descriptorSet0;

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
    void write_descriptor_sets(VkImageView * imageViews, int imageViewCount);
    void create_pipeline();
    void draw(VkCommandBuffer commandBuffer,
              uint32_t frameIndex,
              float dissolveLerp,
              float textLerp,
              float framebufferWidth,
              float framebufferHeight);
  };
}
