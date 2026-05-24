#include <stdint.h>

namespace language {
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

  struct statement {
    enum type type;
    union {
      jump jump;
      menu menu;
      play play;
      say say;
      scene scene;
      show show;
      voice voice;
    };
  };
}
