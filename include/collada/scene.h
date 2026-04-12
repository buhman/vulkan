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

    void update(XMMATRIX const & projection,
                XMMATRIX const & view,
                float t);
  };
}
