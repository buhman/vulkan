#pragma once

#include "volk/volk.h"

#include "collada/types.h"
#include "collada/instance_types.h"
#include "collada/scene/vulkan.h"

namespace collada::scene {
  // these structures are not vulkan-specific
  struct Scene {
    XMFLOAT4X4 projection;
    XMFLOAT4X4 view;
    XMFLOAT4X4 shadowProjection;
    XMFLOAT4X4 shadowView;
    XMFLOAT4 lightPosition;
  };
  struct Node {
    XMFLOAT4X4 world;
  };
  struct MaterialColor {
    XMFLOAT4 emission;
    XMFLOAT4 ambient;
    XMFLOAT4 diffuse;
    XMFLOAT4 specular;
  };
  struct MaterialImage {
    int emission;
    int ambient;
    int diffuse;
    int specular;
  };
  struct MaterialColorImage {
    MaterialColor color;
    MaterialImage image;
  };
  struct PushConstant {
    int nodeIndex;
    int materialIndex;
  };

  struct vulkan {
    static constexpr uint32_t maxFrames = 2;
    static constexpr uint32_t perFrameDescriptorCount = 2;
    static constexpr uint32_t constantDescriptorCount = 1;
    static constexpr uint32_t uniformBufferDescriptorCount = maxFrames * perFrameDescriptorCount + constantDescriptorCount;
    // +3: linear sampler, shadow sampled image, scene sampled image (array)
    static constexpr uint32_t bindingCount = uniformBufferDescriptorCount + 3;
    static constexpr int shaderVariantCount = 3;

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
    // externally initialized
    VkSampler linearSampler;
    VkImageView shadowDepthImageView;

    //
    // method initialized
    //
    VkPipelineLayout pipelineLayout;
    VkShaderModule shaderModule;
    VkPipeline * pipelines; // per-scene, one per descriptor->inputs_list_count
    struct {
      VkDeviceSize indexOffset;
      VkBuffer buffer;
      VkDeviceMemory memory;
    } vertexIndex;

    VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };

    VkDescriptorSetLayout descriptorSetLayouts[2]; // unrelated to maxFrames, unrelated to descriptorCount
    VkDescriptorSet descriptorSets0[maxFrames];
    VkDescriptorSet descriptorSet1;

    struct Image {
      VkImage image;
      VkDeviceMemory memory;
      VkImageView imageView;
    };
    Image * images;

    struct {
      Scene scene; // global(?)
      Node * nodes; // per-scene
      MaterialColorImage * materialColorImages; // per-scene
    } shaderData;
    struct {
      VkDeviceMemory memory;
      VkDeviceSize memorySize;
      void * mappedData;
      struct {  // must match perFrameDescriptorCount
        VkBuffer sceneBuffer;
        VkDeviceAddress sceneOffset;
        VkDeviceAddress sceneSize;
        void * sceneMapped;

        VkBuffer nodesBuffer;
        VkDeviceAddress nodesOffset;
        VkDeviceAddress nodesSize;
        void * nodesMapped;
      } frame[maxFrames];
      struct { // must match constantDescriptorCount
        VkBuffer materialColorImagesBuffer;
        VkDeviceAddress materialColorImagesOffset;
        VkDeviceAddress materialColorImagesSize;
        void * materialColorImagesMapped;
      } constant;
    } shaderDataDevice;

    // per-frame
    VkCommandBuffer commandBuffer;
    uint32_t frameIndex;
    uint32_t pipelineIndex;
    int excludeMaterialIndex;

    //////////////////////////////////////////////////////////////////////
    // called directly
    //////////////////////////////////////////////////////////////////////

    void initial_state(VkInstance instance,
                       VkDevice device,
                       VkQueue queue,
                       VkCommandPool commandPool,
                       VkPhysicalDeviceProperties const & physicalDeviceProperties,
                       VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                       VkFormat colorFormat,
                       VkFormat depthFormat,
                       VkSampler linearSampler,
                       VkImageView shadowDepthImageView);

    void change_frame(VkCommandBuffer commandBuffer, uint32_t frameIndex);
    void destroy_all(collada::types::descriptor const * const descriptor);

    //////////////////////////////////////////////////////////////////////
    // called by initial_state
    //////////////////////////////////////////////////////////////////////

    void load_shader();

    //////////////////////////////////////////////////////////////////////
    // called by state::load_scene
    //////////////////////////////////////////////////////////////////////

    void load_vertex_index_buffer(char const * vertex_filename,
                                  char const * index_filename);
    void create_pipelines(collada::types::descriptor const * const descriptor);

    void create_uniform_buffers(collada::types::descriptor const * const descriptor);
    void create_descriptor_sets(collada::types::descriptor const * const descriptor);
    void write_descriptor_sets(collada::types::descriptor const * const descriptor);
    void load_material_constants(collada::types::descriptor const * const descriptor);
    void load_images(collada::types::descriptor const * const descriptor);

    //////////////////////////////////////////////////////////////////////
    // called by state::draw
    //////////////////////////////////////////////////////////////////////

    void draw_geometry(types::geometry const & geometry,
                       types::instance_material const * const instance_materials,
                       int const instance_materials_count);

    void draw_instance_geometries(types::instance_geometry const * const instance_geometries,
                                  int const instance_geometries_count);

    void draw_node(int32_t node_index,
                   types::node const & node,
                   instance_types::node const & node_instance);

    //////////////////////////////////////////////////////////////////////
    // called by state::update
    //////////////////////////////////////////////////////////////////////

    void transfer_transforms(XMMATRIX const & projection,
                             XMMATRIX const & view,
                             XMMATRIX const & shadowProjection,
                             XMMATRIX const & shadowView,
                             XMVECTOR const & light_position_world,
                             int nodes_count,
                             instance_types::node const * const node_instances);
  };
}
