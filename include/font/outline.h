#pragma once

#include "outline_types.h"
#include "vulkan_helper.h"
#include "renpy/interpreter.h"

namespace font::outline {

  struct font_desc {
    char const * const path;
  };

  font_desc const medieval_sharp[] = {
    {
      .path = "data/font/outline/medieval_sharp_24.data",
    },
  };
  int const medieval_sharp_length = (sizeof (medieval_sharp)) / (sizeof (font_desc));

  constexpr uint32_t textboxLeft = 410;
  constexpr uint32_t textboxWidth = 450;

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

  struct GlyphInstance {
    uint16_t x;
    uint16_t y;
    uint32_t glyph;
    uint32_t color;
  };
  static_assert((sizeof (GlyphInstance)) == 4 * 3);

  struct Glyph {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
  };

  struct font {
    static constexpr int perVertexSize = (4) * 2;
    static constexpr int perInstanceSize = (sizeof (GlyphInstance));

    static constexpr int maximumGlyphCount = 1024;

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

    VkDeviceSize instanceBufferOffset[2];
    VkBuffer instanceBuffer;
    VkDeviceMemory instanceMemory;
    VkDeviceSize instanceMemorySize;
    GlyphInstance * instanceMappedData;

    VkBuffer glyphsBuffer;
    VkDeviceMemory glyphsMemory;
    VkDeviceSize glyphsBufferSize;

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
    void create_instance_buffers();
    void create_pipeline();
    void create_glyphs_buffer(types::font const * const font, types::glyph const * const glyphs);
    void emit_line(int frameIndex,
                   char const * const string,
                   uint32_t x, uint32_t y,
                   int& outputIndex,
                   int startIndex,
                   int endIndex,
                   uint32_t color);
    void centered(int frameIndex, char const * const string, uint32_t& x, uint32_t& y,
                  uint32_t minX,
                  uint32_t maxWidth,
                  int& outputIndex,
                  uint32_t color);
    void draw(VkCommandBuffer commandBuffer,
              uint32_t frameIndex,
              renpy::interpreter const& state);

    LoadedFont load_font(font_desc const& desc);
  };
}
