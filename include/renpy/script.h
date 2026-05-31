#include "renpy/language.h"

namespace renpy::script {
  extern char const * const strings[];
  extern const int strings_length;
  extern const int strings_say_poem_index;

  extern const language::character characters[];
  extern const int characters_length;

  extern const language::audio audio[];
  extern const int audio_length;

  extern const language::image images[];
  extern const int images_length;

  extern const language::option options[];
  extern const int options_length;

  extern const language::dissolve dissolves[];
  extern const int dissolves_length;

  extern const language::statement statements[];
  extern const int statements_length;

}
