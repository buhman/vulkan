#include <assert.h>
#include <stdio.h>

#include "renpy/script.h"
#include "renpy/interact.h"

namespace renpy {
  bool overlap(int width, int height, int x, int y, int mx, int my)
  {
    int minX = x;
    int minY = y;
    int maxX = x + width;
    int maxY = y + height;

    return mx >= minX && mx <= maxX && my >= minY && my <= maxY;
  }

  static bool lastmLeft = false;

  void update(interpreter & state, int mx, int my, bool mLeft)
  {
    bool mDown = mLeft && (!lastmLeft);
    lastmLeft = mLeft;
    if (mDown) {
      state.pause.voice = false;
    }

    if (state.menu.count == 0 || !mDown)
      return;

    for (uint32_t i = 0; i < state.menu.count; i++) {
      int y = menu::yStride * i + menu::y;

      bool overlap = renpy::overlap(menu::width, menu::height, menu::x, y, mx, my);
      if (overlap) {
        // jump to menu item
        uint32_t optionIndex = state.menu.optionIndex + i;
        assert(optionIndex < (uint32_t)script::options_length);
        uint32_t next_pc = script::options[optionIndex].statementIndex;
        fprintf(stderr, "interact[%d]: menu jump %d\n", state.pc, next_pc);
        state.pc = next_pc;
        state.menu.count = 0;
        break;
      }
    }
  }
}
