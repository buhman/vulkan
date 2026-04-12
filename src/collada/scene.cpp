#include "collada/scene.h"

#include <stdio.h>

namespace collada::scene {

  void state::load_scene(types::descriptor const * const descriptor)
  {
    this->descriptor = descriptor;

    vulkan.create_pipelines(descriptor);
    vulkan.load_vertex_index_buffer(descriptor->position_normal_texture_buffer,
                                    descriptor->index_buffer);

    node_state.allocate_node_instances(descriptor->nodes, descriptor->nodes_count);
  }

  void state::draw()
  {
    for (int i = 0; i < descriptor->nodes_count; i++) {
      types::node const & node = *descriptor->nodes[i];
      instance_types::node const & node_instance = node_state.node_instances[i];

      if (node.instance_geometries_count <= 0)
        continue;

      vulkan.draw_node(i,
                       node,
                       node_instance);

    }
  }

  void state::update(XMMATRIX const & projection,
                     XMMATRIX const & view,
                     float t)
  {
    //t = animate::loop(t / 1.0f, 1.0f);

    for (int i = 0; i < descriptor->nodes_count; i++) {
      //animate::animate_node(node_state.node_instances[i], t);
      node_state.update_node_world_transform(node_state.node_instances[i]);
    }

    vulkan.transfer_transforms(projection,
                               view,
                               descriptor->nodes_count,
                               node_state.node_instances);
  }
}
