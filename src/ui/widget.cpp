#include <string.h>
#include <stdio.h>

#include "ui/widget.h"
#include "intstring.h"
#include "minmax.h"

namespace ui::widget
{
  static void drawBoundingBox(MappedInstanceData<SolidInstance> & data,
                              BoundingBox const & bb, uint32_t color)
  {
    if ((color & 0xff000000) == 0)
      color |= 0xff000000;
    data.append({
        { (uint16_t)bb.left, (uint16_t)bb.top },
        { (uint16_t)bb.width, (uint16_t)bb.height },
        color,
      });
  }

  static inline void drawGlyph(MappedInstanceData<font::BitmapInstance> & fontData,
                               int x, int y,
                               int c)
  {
    fontData.append({ {(uint16_t)(x), (uint16_t)(y)}, font::bitmap::glyphIndex(c) });
  }

  template<typename T>
  inline void drawNumberCentered(MappedInstanceData<font::BitmapInstance> & fontData,
                                 int x, int y,
                                 T number);

  template<>
  inline void drawNumberCentered<int>(MappedInstanceData<font::BitmapInstance> & fontData,
                                      int x, int y,
                                      int number)
  {
    char buf[16];
    int numLength = string::dec(buf, 16, number);
    int width = numLength * 6;
    int left = x - (width / 2);
    for (int i = 0; i < numLength; i++) {
      fontData.append({ {(uint16_t)(left + 6 * i), (uint16_t)(y)}, font::bitmap::glyphIndex(buf[i]) });
    }
  }

  template<>
  inline void drawNumberCentered<float>(MappedInstanceData<font::BitmapInstance> & fontData,
                                        int x, int y,
                                        float number)
  {

    char buf[64];
    int numLength = string::flt(buf, 64, number);
    int width = numLength * 6;
    int left = x - (width / 2);
    for (int i = 0; i < numLength; i++) {
      fontData.append({ {(uint16_t)(left + 6 * i), (uint16_t)(y)}, font::bitmap::glyphIndex(buf[i]) });
    }
  }

  static inline void drawStringCentered(MappedInstanceData<font::BitmapInstance> & fontData,
                                        int x, int y,
                                        const char * string)
  {
    int length = strlen(string);
    int width = length * 6;
    int left = x - (width / 2);
    for (int i = 0; i < length; i++) {
      fontData.append({ {(uint16_t)(left + 6 * i), (uint16_t)(y)}, font::bitmap::glyphIndex(string[i]) });
    }
  }

  static inline void drawStringLeft(MappedInstanceData<font::BitmapInstance> & fontData,
                                    int x, int y,
                                    const char * string)
  {
    int length = strlen(string);
    int left = x;
    for (int i = 0; i < length; i++) {
      fontData.append({ {(uint16_t)(left + 6 * i), (uint16_t)(y)}, font::bitmap::glyphIndex(string[i]) });
    }
  }

  static inline void drawStringRight(MappedInstanceData<font::BitmapInstance> & fontData,
                                     int x, int y,
                                     const char * string)
  {
    int length = strlen(string);

    int width = length * 6;
    int left = x - width;
    for (int i = 0; i < length; i++) {
      fontData.append({ {(uint16_t)(left + 6 * i), (uint16_t)(y)}, font::bitmap::glyphIndex(string[i]) });
    }
  }

  template <typename T, bool under>
  void Slider<T, under>::draw(MappedInstanceData<SolidInstance> & data,
                              MappedInstanceData<font::BitmapInstance> & fontData)
  {
    drawBoundingBox(data, sliderBorder, 0x545454);

    float sliderInterp = (float)(*value - minExtent) / (float)(maxExtent - minExtent);
    int sliderWidth = (float)slider.width * clamp01(sliderInterp);

    drawBoundingBox(data, {
        slider.left,
        slider.top,
        sliderWidth,
        slider.height,
      }, 0x800000);

    drawBoundingBox(data, lminus, 0x008080);
    drawGlyph(fontData, lminus.left + 2, lminus.top - 3, '-');
    drawBoundingBox(data, lplus, 0x008080);
    drawGlyph(fontData, lplus.left + 2, lplus.top - 3, '+');

    drawBoundingBox(data, rminus, 0x008000);
    drawGlyph(fontData, rminus.left + 2, lminus.top - 3, '-');
    drawBoundingBox(data, rplus, 0x008000);
    drawGlyph(fontData, rplus.left + 2, lplus.top - 3, '+');

    constexpr int yOffset = under ? 14 : -16;

    drawNumberCentered<T>(fontData, slider.left, slider.top + yOffset, minExtent);
    drawNumberCentered<T>(fontData, slider.left + slider.width, slider.top + yOffset, maxExtent);

    drawNumberCentered<T>(fontData, slider.left + slider.width / 2, slider.top + yOffset, *value);

    drawStringRight(fontData, slider.left - 25, slider.top - 1, label);
    //drawStringRight(fontData, slider.left - 25, slider.top + 5, label);
    //drawStringLeft(fontData, slider.left + slider.width + 26, slider.top - 1, label);
  }

  template <typename T, bool under>
  void Slider<T, under>::update(float mx, float my, bool mLeft, bool mEdge)
  {
    if (!mLeft) {
      drag = false;
      return;
    }

    if (mEdge) {
      double eWidth2 = (double)(maxExtent - minExtent) / 2.0f;
      double vWidth2 = (double)(maxValue - minValue) / 2.0f;
      double width2 = min(eWidth2, vWidth2);

      if (lminus.inside(mx, my)) {
        minExtent = clamp<double>(minExtent + width2, minValue, maxValue);
      } else if (lplus.inside(mx, my)) {
        minExtent = clamp<double>(minExtent - width2, minValue, maxValue);
      } else if (rminus.inside(mx, my)) {
        maxExtent = clamp<double>(maxExtent - width2, minValue, maxValue);
      } else if (rplus.inside(mx, my)) {
        maxExtent = clamp<double>(maxExtent + width2, minValue, maxValue);
      } else if (slider.inside(mx, my)) {
        drag = true;
      }
    }

    if (drag) {
      float lerp = clamp01((mx - (float)slider.left) / (float)(slider.width));

      float valueScale = maxExtent - minExtent;
      *value = (T)(lerp * valueScale + minExtent);
    }
  }

  template struct Slider<int, true>;
  template struct Slider<int, false>;
  template struct Slider<float, true>;
  template struct Slider<float, false>;

  void DelayGainSlider::draw(MappedInstanceData<SolidInstance> & data,
                             MappedInstanceData<font::BitmapInstance> & fontData)
  {
    drawStringCentered(fontData, delay.slider.left + delay.slider.width / 2, delay.slider.top - 16, label);

    delay.draw(data, fontData);
    gain.draw(data, fontData);
  }

  void DelayGainSlider::update(float mx, float my, bool mLeft, bool mEdge)
  {
    delay.update(mx, my, mLeft, mEdge);
    gain.update(mx, my, mLeft, mEdge);
  }

  template <int optionCount>
  void Radio<optionCount>::draw(MappedInstanceData<SolidInstance> & data,
                                MappedInstanceData<font::BitmapInstance> & fontData)
  {
    drawStringCentered(fontData, box[0].left + width / 2, box[0].top - 16, label);

    for (int i = 0; i < optionCount; i++) {
      uint32_t color = (i == *selected) ? 0xa0800080 : 0x80300030;
      drawBoundingBox(data, box[i], color);
      drawStringCentered(fontData, box[i].left + box[i].width / 2, box[0].top + box[i].height / 2 - 6, boxLabels[i]);
    }
  }

  template <int optionCount>
  void Radio<optionCount>::update(float mx, float my, bool mLeft, bool mEdge)
  {
    if (!mEdge)
      return;

    for (int i = 0; i < optionCount; i++) {
      if (box[i].inside(mx, my)) {
        *selected = i;
        break;
      }
    }
  }

  template struct widget::Radio<2>;
}
