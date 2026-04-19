#pragma once

#include "collada/types.h"
#include "collada/instance_types.h"
#include "collada/node_state.h"

#include "collada/scene/vulkan.h"

namespace collada::scene {
  struct state {
    types::descriptor const * descriptor;
    node_state::state node_state;

    collada::scene::vulkan vulkan;

    void load_scene(types::descriptor const * const descriptor);
    void draw();

    int find_node_index_by_name(const char * name);
    int find_material_index_by_name(const char * name);

    void update(float t);

    void unload_scene();

    void mouse_motion(int eyeIndex, int targetIndex, float xrel, float yrel, int mode);
  };
}
