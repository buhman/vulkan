#pragma once

#include "volk/volk.h"

#include "collada/types.h"
#include "collada/instance_types.h"
#include "collada/scene/vulkan.h"

#include "shader_data.h"

namespace collada::scene {
  struct vulkan {
    // externally initialized, opaque handle
    VkInstance instance;
    VkDevice device;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    // externally initialized, structures
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
    // externally initialized, enum
    VkFormat colorFormat;
    VkFormat depthFormat;
    // externally initialized, pointers
    ShaderData * shaderData;
    ShaderDataDevice const * shaderDataDevice;

    // method initialized
    VkShaderModule shaderModule;
    VkPipeline * pipelines;
    struct {
      VkDeviceSize indexOffset;
      VkBuffer buffer;
      VkDeviceMemory memory;
    } vertexIndex;

    // per-frame
    VkCommandBuffer commandBuffer;
    uint32_t frameIndex;

    //////////////////////////////////////////////////////////////////////
    // called directly
    //////////////////////////////////////////////////////////////////////

    void initial_state(VkInstance instance,
                       VkDevice device,
                       VkPipelineLayout pipelineLayout,
                       VkDescriptorSetLayout descriptorSetLayout,
                       VkPhysicalDeviceProperties const & physicalDeviceProperties,
                       VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                       VkFormat colorFormat,
                       VkFormat depthFormat,
                       ShaderData * shaderData,
                       ShaderDataDevice const * shaderDataDevice);

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
  };
}
