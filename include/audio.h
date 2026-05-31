#pragma once

#include "renpy/language.h"
#include "poem.h"

namespace audio {

  extern int poem_timestamp_index;
  extern int poem_line_index;
  extern poem::poem const * poem_playing;

  void init();
  void load(renpy::language::audio const * const audio, int count);
  void update();
  void play(int audio_index);
  void stop(int audio_index, double fadeout);
  void stop_all();
  bool exists(int audio_index);
}
