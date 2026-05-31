#pragma once

#include "renpy/interpreter.h"

namespace renpy {

  namespace menu {
    constexpr int width = 480;
    constexpr int height = 40;
    constexpr int x = 400;
    constexpr int y = 100;
    constexpr int yStride = 100;
  };

  extern int lastGamepadItem;
  extern bool lastUseGamepad;

  void jumpToMenuItem(interpreter & state, int i);
  bool overlap(int menuWidth, int menuHeight,
               int x, int y,
               int mx, int my,
               int windowWidth, int windowHeight);
  void update(interpreter & state,
              int mx, int my, bool mLeft,
              bool gUp, bool gDown, bool gAccept,
              bool useGamepad,
              int windowWidth, int windowHeight);
}
