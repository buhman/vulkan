#include <stdint.h>

namespace renpy::language {
  struct transform {
    enum _transform {
      left,
      centerleft,
      center,
      centerright,
      right,
    };
  };

  struct option {
    char const * const string;
    uint32_t statementIndex;
  };

  struct character {
    char const * const characterName;
  };

  struct audio {
    char const * const path;
  };

  struct image {
    char const * const path;
  };

  // statement

  enum struct type {
    jump,
    menu,
    play,
    _return,
    say,
    scene,
    show,
    voice,
    with,
    stop,
    pause,
    hide,
  };

  struct jump {
    uint32_t statementIndex;
  };

  struct menu {
    uint32_t count;
    uint32_t optionIndex;
  };

  struct play {
    uint32_t channelIndex;
    uint32_t audioIndex;
  };

  struct _return {
  };

  struct say {
    uint32_t characterIndex;
    uint32_t stringIndex;
  };

  struct scene {
    uint32_t imageIndex;
  };

  struct show {
    uint32_t imageIndex;
    uint32_t transformIndex;
  };

  struct voice {
    uint32_t audioIndex;
  };

  struct with {
  };

  struct stop {
    uint32_t channelIndex;
  };

  struct pause {
    float duration;
  };

  struct hide {
    uint32_t imageIndex;
  };

  struct statement {
    enum type type;
    union {
      renpy::language::jump jump;
      renpy::language::menu menu;
      renpy::language::play play;
      renpy::language::say say;
      renpy::language::scene scene;
      renpy::language::show show;
      renpy::language::voice voice;
      renpy::language::stop stop;
      renpy::language::pause pause;
      renpy::language::hide hide;
    };
  };
}
