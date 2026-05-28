#pragma once

#include "renpy/language.h"

namespace audio {
  void init();
  void load(renpy::language::audio const * const audio, int count);
  void update();
  void play(int audio_index);
  void stop(int audio_index, double fadeout);
}
