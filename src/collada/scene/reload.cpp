#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "new.h"
#include "collada/scene/reload.h"

namespace collada::scene {
  void reload::load_images(types::descriptor const * const descriptor)
  {
    imageStats = NewM<reload_stat>(descriptor->images_count);

    for (int i = 0; i < descriptor->images_count; i++) {
      char const * filename = descriptor->images[i]->uri;
      size_t length = strlen(filename);

      imageStats[i].filenameTGA = strndup(filename, length);
      imageStats[i].filenameTGA[length - 3] = 't';
      imageStats[i].filenameTGA[length - 2] = 'g';
      imageStats[i].filenameTGA[length - 1] = 'a';

      imageStats[i].mtime.tv_sec = 0;
      imageStats[i].mtime.tv_nsec = 0;
    }
  }

  void reload::stat_images(collada::types::descriptor const * const descriptor,
                           collada::scene::vulkan & vulkan)
  {
    bool reload = false;
    for (int i = 0; i < descriptor->images_count; i++) {
      off_t size = 0;
      while (true) {
        struct stat statbuf;
        int ret = stat(imageStats[i].filenameTGA, &statbuf);
        if (ret != 0)
          break;

        if (statbuf.st_mtim.tv_sec != imageStats[i].mtime.tv_sec || statbuf.st_mtim.tv_nsec != imageStats[i].mtime.tv_nsec) {
          if (statbuf.st_size != size) {
            size = statbuf.st_size;
            usleep(500);
            continue;
          }

          fprintf(stderr, "reload %s\n", imageStats[i].filenameTGA);
          reload = true;
          vulkan.destroy_image(i);
          vulkan.load_image(i, imageStats[i].filenameTGA);
          imageStats[i].mtime.tv_sec = statbuf.st_mtim.tv_sec;
          imageStats[i].mtime.tv_nsec = statbuf.st_mtim.tv_nsec;
        }
        break;
      }
    }
    if (reload) {
      vulkan.write_descriptor_sets(descriptor);
    }
  }

  void reload::destroy_images(types::descriptor const * const descriptor)
  {
    for (int i = 0; i < descriptor->images_count; i++) {
      free(imageStats[i].filenameTGA);
    }
    free(imageStats);
  }
}
