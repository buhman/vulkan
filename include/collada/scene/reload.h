#pragma once

#include <time.h>

#include "collada/types.h"
#include "collada/scene/vulkan.h"

namespace collada::scene {
  struct reload_stat {
    char * filenameTGA;
    struct timespec mtime;
  };

  struct reload {
    reload_stat * imageStats;

    void load_images(types::descriptor const * const descriptor);
    void stat_images(collada::types::descriptor const * const descriptor,
                     collada::scene::vulkan & vulkan);
    void destroy_images(types::descriptor const * const descriptor);
  };
}
