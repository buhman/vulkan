#pragma once

#include <stdint.h>

#include "renpy/language.h"
#include "renpy/script.h"

namespace renpy {
  struct top_left {
    uint32_t top;
    uint32_t left;
  };

  static constexpr top_left transforms[] = {
    [language::transform::left] = { .top = 192, .left = 0 },
    [language::transform::centerleft] = { .top = 192, .left = 240 },
    [language::transform::center] = { .top = 192, .left = 416 },
    [language::transform::centerright] = { .top = 192, .left = 588 },
    [language::transform::right] = { .top = 192, .left = 828 },
  };
  static constexpr int transformsCount = (sizeof (transforms)) / (sizeof (transforms[0]));

  struct shownImage {
    uint32_t imageIndex;
    uint32_t transformIndex;
  };

  static constexpr int maximumShownImagesCount = 16;

  struct interpreter {
    uint32_t pc;
    uint32_t backgroundIndex;
    uint32_t backgroundColor;
    shownImage shownImages[maximumShownImagesCount];
    uint32_t shownImagesCount;
    struct {
      uint32_t stringIndex;
      uint32_t characterIndex;
    } say;
    struct {
      uint32_t count;
      uint32_t optionIndex;
    } menu;
    uint32_t dissolveIndex;
    struct {
      bool voice;
      bool menu;
      bool dissolve;
      bool pause;
    } pause;
    double dissolveDuration;
    double pauseDuration;

    uint32_t findImage(uint32_t imageIndex);
    void showImage(uint32_t imageIndex, uint32_t transformIndex);
    void hideImage(uint32_t imageIndex);
    void reset();
    void interpret_one();
    void interpret();

    inline bool interactionWait()
    {
      return pause.voice || pause.menu || pause.dissolve || pause.pause;
    }

    inline bool dissolvePC()
    {
      return dissolveIndex < (uint32_t)script::dissolves_length && script::dissolves[dissolveIndex].first_statement == pc;
    }
  };
}
