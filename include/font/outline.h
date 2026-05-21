#pragma once

#include "outline_types.h"
#include "vulkan_helper.h"

namespace font::outline {

  struct font_desc {
    char const * const path;
  };

  font_desc const uncial_antiqua[] = {
    {
      .path = "data/font/outline/uncial_antiqua_36.data",
    },
  };
  int const uncial_antiqua_length = (sizeof (uncial_antiqua)) / (sizeof (font_desc));

  struct AllocatedImage {
    VkImage image;
    VkDeviceMemory memory;
    VkImageView imageView;
  };

  struct LoadedFont {
    types::font * font;
    types::glyph * glyphs;
    AllocatedImage allocatedImage;
  };

  struct font {
    static constexpr int perVertexSize = (4) * 2;
    static constexpr int perInstanceSize = (0) * 2;

    VkInstance instance;
    VkDevice device;
    VkQueue queue;
    VkCommandPool commandPool;
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
    VkFormat colorFormat;
    VkFormat depthFormat;
    VkSampler linearSampler;

    // font-specific state
    VkPipelineLayout pipelineLayout;
    VkShaderModule shaderModule;
    VkPipeline pipeline;
    VertexIndex vertexIndex;
    LoadedFont loadedFont;

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
    void write_descriptor_sets(VkImageView fontImageView);
    void create_pipeline();
    void draw(VkCommandBuffer commandBuffer,
              uint32_t frameIndex);

    LoadedFont load_font(font_desc const& desc);
  };
}
