

namespace renpy {
  struct top_left {
    uint32_t top;
    uint32_t left;
  };

  static const top_left transforms[] = {
    [language::transform::left] = { .top = 192, .left = 0 },
    [language::transform::centerleft] = { .top = 192, .left = 240 },
    [language::transform::center] = { .top = 192, .left = 416 },
    [language::transform::centerright] = { .top = 192, .left = 588 },
    [language::transform::right] = { .top = 192, .left = 828 },
  };

  struct shownImage {
    uint32_t imageIndex;
    uint32_t transformIndex;
  };

  struct interpreter {
    uint32_t backgroundIndex;
    shownImage shownImages[16];
    uint32_t shownImagesCount;
  };
}
