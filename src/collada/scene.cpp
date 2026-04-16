#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "collada/scene.h"
#include "collada/animate.h"

namespace collada::scene {

  void state::load_scene(types::descriptor const * const descriptor)
  {
    this->descriptor = descriptor;

    vulkan.load_vertex_index_buffer(descriptor->position_normal_texture_buffer,
                                    descriptor->index_buffer);
    vulkan.create_uniform_buffers(descriptor);
    vulkan.create_descriptor_sets(descriptor);
    vulkan.load_material_constants(descriptor);
    vulkan.load_images(descriptor);
    vulkan.write_descriptor_sets(descriptor);
    vulkan.create_pipelines(descriptor);

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

  int state::find_node_index_by_name(const char * name)
  {
    for (int i = 0; i < descriptor->nodes_count; i++) {
      if (strcmp(descriptor->nodes[i]->name, name) == 0) {
        return i;
      }
    }
    fprintf(stderr, "node `%s` not found in scene\n", name);
    exit(EXIT_FAILURE);
  }

  int state::find_material_index_by_name(const char * name)
  {
    for (int i = 0; i < descriptor->materials_count; i++) {
      if (strcmp(descriptor->materials[i]->name, name) == 0) {
        return i;
      }
    }
    fprintf(stderr, "node `%s` not found in scene\n", name);
    exit(EXIT_FAILURE);
  }

  void state::update(float t)
  {
    t = animate::loop(t, 3.3f);

    for (int i = 0; i < descriptor->nodes_count; i++) {
      animate::animate_node(node_state.node_instances[i], t);
      node_state.update_node_world_transform(node_state.node_instances[i]);
    }
  }

  void state::unload_scene()
  {
    node_state.deallocate_node_instances(descriptor->nodes_count);
  }
}
