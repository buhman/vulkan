#include "minecraft/world.h"
#include "minecraft/inthash.h"

namespace minecraft::world {
  static vtx_cfg const grandlecturn_vertex_paths[] = {
    { "data/minecraft/grandlecturn/region.0.0.instance.vtx", "data/minecraft/grandlecturn/region.0.0.instance.cfg" },
    { "data/minecraft/grandlecturn/region.-1.0.instance.vtx", "data/minecraft/grandlecturn/region.-1.0.instance.cfg" },
    { "data/minecraft/grandlecturn/region.0.-1.instance.vtx", "data/minecraft/grandlecturn/region.0.-1.instance.cfg" },
    { "data/minecraft/grandlecturn/region.-1.-1.instance.vtx", "data/minecraft/grandlecturn/region.-1.-1.instance.cfg" },
  };

  static vtx_cfg const midnightmeadow_vertex_paths[] = {
    { "data/minecraft/midnightmeadow/region.0.0.instance.vtx", "data/minecraft/midnightmeadow/region.0.0.instance.cfg" },
    { "data/minecraft/midnightmeadow/region.-1.0.instance.vtx", "data/minecraft/midnightmeadow/region.-1.0.instance.cfg" },
    { "data/minecraft/midnightmeadow/region.0.-1.instance.vtx", "data/minecraft/midnightmeadow/region.0.-1.instance.cfg" },
    { "data/minecraft/midnightmeadow/region.-1.-1.instance.vtx", "data/minecraft/midnightmeadow/region.-1.-1.instance.cfg" },
  };

  descriptor const descriptors[] = {
    //[world_id::GRANDLECTURN] =
    {
      .region_count = 4,
      .vertex_paths = grandlecturn_vertex_paths,
      .entry_table_path = "data/minecraft/grandlecturn/global.dump",
      .lights_path = "data/minecraft/grandlecturn/global.lights.vtx",
      .hash_func = grandlecturn_hash,
    },
    //[world_id::MIDNIGHTMEADOW] =
    {
      .region_count = 4,
      .vertex_paths = midnightmeadow_vertex_paths,
      .entry_table_path = "data/minecraft/midnightmeadow/global.dump",
      .lights_path = "data/minecraft/midnightmeadow/global.lights.vtx",
      .hash_func = midnightmeadow_hash,
    },
  };
  int const descriptors_length = (sizeof (descriptors)) / (sizeof (descriptors[0]));
}
