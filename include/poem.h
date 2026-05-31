#pragma once

namespace poem {
  struct line {
    int start;
    int length;
  };

  struct timestamp {
    double time;
    int wordIndex;
  };

  struct poem {
    char const * const * const words;
    int const words_length;
    line const * const lines;
    int const lines_length;
    timestamp const * const timestamps;
    int const timestamps_length;
  };

  extern poem const eleanorthehero;
  extern poem const kiristella;
  extern poem const birdsong;
}
