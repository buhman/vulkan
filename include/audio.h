#pragma once

#include "renpy/language.h"

namespace audio {
  void init();
  void load(renpy::language::audio const * const audio, int count);
  void update();
}
