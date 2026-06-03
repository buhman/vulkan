#pragma once

#include "ui/widget.h"

namespace ui
{
  void init();
  void draw(MappedInstanceData<SolidInstance> & data,
            MappedInstanceData<font::BitmapInstance> & fontData);
  void update(float mx, float my, bool mLeft, bool mEdge);
}
