#include <stdint.h>

namespace language::statement {
  enum type {
    show,
    voice,
    music,
    text,
    menu,
    jump,
  };

  struct show {
    uint32_t imageIndex;
    uint32_t transformIndex;
  };

  struct voice {
    uint32_t audioIndex;
  };

  struct music {
    uint32_t channelIndex;
    uint32_t audioIndex;
  };

  struct say {
    uint32_t characterIndex;
    uint32_t stringIndex;
  };

  struct option {
    uint32_t stringIndex;
    uint32_t statementIndex;
  };

  struct menu {
    uint32_t count;
    uint32_t optionIndex;
  };

  struct jump {
    uint32_t statementIndex;
  };

  struct statement {
    enum statement_type type;
    union {
      show show;
      voice voice;
      music music;
      say say;
      menu menu;
      jump jump;
    };
  };
}
