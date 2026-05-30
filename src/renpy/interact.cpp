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

  static bool lastmLeft = false;

  void update(interpreter & state,
              int mx, int my, bool mLeft,
              int windowWidth, int windowHeight)
  {
    bool mDown = mLeft && (!lastmLeft);
    lastmLeft = mLeft;
    //if (mDown) {
    //state.pause.voice = false;
    //}

    if (!state.pause.menu || !mDown)
      return;

    for (uint32_t i = 0; i < state.menu.count; i++) {
      int y = menu::yStride * i + menu::y;

      bool overlap = renpy::overlap(menu::width, menu::height, menu::x, y, mx, my, windowWidth, windowHeight);
      if (overlap) {
        // jump to menu item
        uint32_t optionIndex = state.menu.optionIndex + i;
        assert(optionIndex < (uint32_t)script::options_length);
        uint32_t next_pc = script::options[optionIndex].statementIndex;
        fprintf(stderr, "interact[%d]: menu jump %d\n", state.pc, next_pc);
        state.pc = next_pc;
        state.pause.menu = false;
        break;
      }
    }
  }
}
