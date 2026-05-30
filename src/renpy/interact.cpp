#include <assert.h>
#include <stdio.h>

#include "renpy/script.h"
#include "renpy/interact.h"

namespace renpy {
  bool overlap(int menuWidth, int menuHeight,
               int x, int y,
               int mx, int my,
               int windowWidth, int windowHeight)
  {
    float minX = x;
    float minY = y;
    float maxX = x + menuWidth;
    float maxY = y + menuHeight;

    int canonicalSizeX = 1280;
    int canonicalSizeY = 720;
    int scaleFactor = 1;
    while (canonicalSizeX * (scaleFactor + 1) <= windowWidth && canonicalSizeY * (scaleFactor + 1) <= windowHeight) {
      scaleFactor += 1;
    }
    float scaleFactorInverse = 1.0f / ((float)scaleFactor);
    int offsetX = (windowWidth - (canonicalSizeX * scaleFactor)) / 2;
    int offsetY = (windowHeight - (canonicalSizeY * scaleFactor)) / 2;
    float mxf = ((float)(mx - offsetX)) * scaleFactorInverse;
    float myf = ((float)(my - offsetY)) * scaleFactorInverse;

    return mxf >= minX && mxf <= maxX && myf >= minY && myf <= maxY;
  }

  static bool lastMenuPause = false;
  static bool lastmLeft = false;
  int lastGamepadItem = 0;
  bool lastUseGamepad = false;

  static bool lastgUp = false;
  static bool lastgDown = false;
  static bool lastgAccept = false;

  static void jumpToMenuItem(interpreter & state, int i)
  {
    // jump to menu item
    uint32_t optionIndex = state.menu.optionIndex + i;
    assert(optionIndex < (uint32_t)script::options_length);
    uint32_t next_pc = script::options[optionIndex].statementIndex;
    fprintf(stderr, "interact[%d]: menu jump %d\n", state.pc, next_pc);
    state.pc = next_pc;
    state.pause.menu = false;
  }

  void update(interpreter & state,
              int mx, int my, bool mLeft,
              bool _gUp, bool _gDown, bool _gAccept,
              bool useGamepad,
              int windowWidth, int windowHeight)
  {
    lastUseGamepad = useGamepad;

    bool mDown = mLeft && (!lastmLeft);
    lastmLeft = mLeft;

    bool pauseTransition = state.pause.menu && (!lastMenuPause);
    lastMenuPause = state.pause.menu;

    bool gUp = _gUp && (!lastgUp);
    bool gDown = _gDown && (!lastgDown);
    bool gAccept = _gAccept && (!lastgAccept);
    lastgUp = _gUp;
    lastgDown = _gDown;
    lastgAccept = _gAccept;

    if (!state.pause.menu) {
      return;
    }

    if (pauseTransition) {
      fprintf(stderr, "interact::update: menu pause transition\n");
      lastGamepadItem = 0;
    }

    if (useGamepad) {
      //printf("useGamepad %d %d\n", gUp, _gAccept);
      if (gUp) {
        lastGamepadItem -= 1;
        if (lastGamepadItem < 0)
          lastGamepadItem = state.menu.count - 1;
      }
      if (gDown) {
        lastGamepadItem += 1;
        if (lastGamepadItem >= (int)state.menu.count)
          lastGamepadItem = 0;
      }
      if (gAccept) {
        jumpToMenuItem(state, lastGamepadItem);
      }
    } else {
      // use mouse
      for (uint32_t i = 0; i < state.menu.count; i++) {
        int y = menu::yStride * i + menu::y;

        bool overlap = renpy::overlap(menu::width, menu::height, menu::x, y, mx, my, windowWidth, windowHeight);
        if (overlap) {
          lastGamepadItem = i;
          if (mDown) {
            jumpToMenuItem(state, i);
            return;
          }
        }
      }
    }
  }
}
