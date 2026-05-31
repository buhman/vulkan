namespace poem1 {
  struct line {
    int start;
    int length;
  };

  struct timestamp {
    double time;
    int wordIndex;
  };

  extern char const * const words[];
  extern int const words_length;
  extern line const lines[];
  extern int const lines_length;
  extern timestamp const timestamps[];
  extern int const timestamps_length;
}
