#pragma once

#ifdef __APPLE__
#include "vulkan/vulkan.h"
#else
#include "volk/volk.h"
#endif

#include "directxmath/directxmath.h"

#include "vulkan_helper.h"
#include "minecraft/vulkan/per_world.h"

namespace minecraft::vulkan {

  struct Scene {
    XMFLOAT4X4 projection;
    XMFLOAT4X4 view;
    XMFLOAT4X4 shadowProjection;
    XMFLOAT4X4 shadowView;
    XMFLOAT4 lightPosition;
  };

  struct vulkan {
    static constexpr uint32_t maxFrames = 2;
    static constexpr uint32_t perFrameDescriptorCount = 1;
    static constexpr uint32_t uniformBufferDescriptorCount = maxFrames * perFrameDescriptorCount;
    static constexpr uint32_t bindingCount = uniformBufferDescriptorCount + 3;

    static constexpr int perVertexSize = (3 + 3 + 2) * 2;
    static constexpr int perInstanceSize = (3 + 1 + 3 + 1) * 2;

    VertexIndex vertexIndex;

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
    VkImageView shadowDepthImageView;

    //
    // method initialized
    //
    VkPipelineLayout pipelineLayout;
    VkShaderModule shaderModule;
    VkPipeline pipeline;

    per_world * worlds;

    VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };

    VkDescriptorSetLayout descriptorSetLayouts[2]; // unrelated to maxFrames, unrelated to descriptorCount
    VkDescriptorSet descriptorSets0[maxFrames];
    VkDescriptorSet descriptorSet1;

    struct Image {
      VkImage image;
      VkDeviceMemory memory;
      VkImageView imageView;
    };
    Image terrainImage;

    struct {
      VkDeviceMemory memory;
      VkDeviceSize memorySize;
      void * mappedData;
      struct {  // must match perFrameDescriptorCount
        VkBuffer sceneBuffer;
        VkDeviceAddress sceneOffset;
        VkDeviceAddress sceneSize;
        Scene * sceneMapped;
      } frame[maxFrames];
    } shaderDataDevice;

    void initial_state(VkInstance instance,
                       VkDevice device,
                       VkQueue queue,
                       VkCommandPool commandPool,
                       VkPhysicalDeviceProperties physicalDeviceProperties,
                       VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties,
                       VkFormat colorFormat,
                       VkFormat depthFormat,
                       VkSampler linearSampler,
                       VkImageView shadowDepthImageView);
    void init();
    void load_vertex_index_buffer(char const * vertex_filename,
                                  char const * index_filename);
    void load_shader();
    void create_pipeline();
    void load_worlds();
    void create_uniform_buffers();
    void create_descriptor_sets();
    void write_descriptor_sets();
    void transfer_transforms(XMMATRIX const & projection,
                             XMMATRIX const & view,
                             XMVECTOR const & lightPosition,
                             uint32_t frameIndex);
    void load_image(char const * filename,
                    Image & image);

    void draw(VkCommandBuffer commandBuffer,
              uint32_t frameIndex);
  };
}
