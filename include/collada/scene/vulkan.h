#pragma once

#include "volk/volk.h"

#include "collada/types.h"
#include "collada/instance_types.h"
#include "collada/scene/vulkan.h"

namespace collada::scene {
  // these structures are not vulkan-specific
  struct Scene {
    XMFLOAT4X4 projection;
    XMFLOAT4 lightPosition;
  };
  struct Node {
    XMFLOAT4X4 modelView;
    //int materialIndex;
    //int _padding0[3];
    //int _padding1[4 * 3];
  };
  static_assert((sizeof (Node)) % 64 == 0);
  struct MaterialColor {
    XMFLOAT4 emission;
    XMFLOAT4 ambient;
    XMFLOAT4 diffuse;
    XMFLOAT4 specular;
  };
  static_assert((sizeof (MaterialColor)) % 64 == 0);

  struct vulkan {
    // externally initialized, opaque handle
    VkInstance instance;
    VkDevice device;
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
    VkPipeline * pipelines; // per-scene, one per descriptor->inputs_list_count
    struct {
      VkDeviceSize indexOffset;
      VkBuffer buffer;
      VkDeviceMemory memory;
    } vertexIndex;

    VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };
    static constexpr uint32_t maxFrames = 2;
    static constexpr uint32_t perFrameDescriptorCount = 2;
    static constexpr uint32_t constantDescriptorCount = 1;
    static constexpr uint32_t uniformBufferDescriptorCount = maxFrames * perFrameDescriptorCount + constantDescriptorCount;

    VkDescriptorSetLayout descriptorSetLayouts[2]; // unrelated to maxFrames, unrelated to descriptorCount
    VkDescriptorSet descriptorSets0[maxFrames];
    VkDescriptorSet descriptorSet1;

    struct {
      Scene scene; // global(?)
      Node * nodes; // per-scene
      MaterialColor * materialColors; // per-scene
    } shaderData;
    struct {
      VkDeviceMemory memory;
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
        VkBuffer materialColorsBuffer;
        VkDeviceAddress materialColorsOffset;
        VkDeviceAddress materialColorsSize;
        void * materialColorsMapped;
      } constant;
    } shaderDataDevice;

    // per-frame
    VkCommandBuffer commandBuffer;
    uint32_t frameIndex;

    //////////////////////////////////////////////////////////////////////
    // called directly
    //////////////////////////////////////////////////////////////////////

    void initial_state(VkInstance instance,
                       VkDevice device,
                       VkPhysicalDeviceProperties const & physicalDeviceProperties,
                       VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                       VkFormat colorFormat,
                       VkFormat depthFormat);

    void per_frame_state(uint32_t frameIndex);

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
    void create_descriptor_sets();
    void write_descriptor_sets(collada::types::descriptor const * const descriptor);

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
                             int nodes_count,
                             instance_types::node const * const node_instances);

    //////////////////////////////////////////////////////////////////////
    // called by main
    //////////////////////////////////////////////////////////////////////

    void change_frame(VkCommandBuffer commandBuffer, uint32_t frameIndex);
    void destroy_all(collada::types::descriptor const * const descriptor);
  };
}
