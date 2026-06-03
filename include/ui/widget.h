#pragma once

#include "ui/instance_data.h"
#include "font/bitmap.h"

namespace ui::widget
{
  struct BoundingBox
  {
    int left;
    int top;
    int width;
    int height;

    bool inside(float x, float y)
    {
      return (x >= left) && (x <= (left + width))
        && (y >= top) && (y <= (top + height));
    }
  };

  struct Widget {
    //virtual void mouseDown(float x, float y) {};
    virtual void draw(MappedInstanceData<SolidInstance> & data,
                      MappedInstanceData<font::BitmapInstance> & fontData) = 0;

    virtual void update(float mx, float my, bool mLeft, bool mEdge) = 0;
  };

  template <int optionCount>
  struct Radio : public Widget
  {
    char const * label;
    char const ** boxLabels;
    int width;
    int height;
    int * selected;
    BoundingBox box[optionCount];

    Radio(char const * label,
          char const ** boxLabels,
          int left, int top, int width, int height,
          int hSpace, int vSpace,
          int * selected)
      : label(label)
      , boxLabels(boxLabels)
      , width((optionCount - 1) * hSpace + width)
      , height((optionCount - 1) * vSpace + height)
      , selected(selected)
    {
      int x = left;
      int y = top;
      for (int i = 0; i < optionCount; i++) {
        box[i].left = x;
        box[i].top = y;
        box[i].width = width;
        box[i].height = height;
        x += hSpace;
        y += vSpace;
      }
    }

    void draw(MappedInstanceData<SolidInstance> & data,
              MappedInstanceData<font::BitmapInstance> & fontData) override;

    void update(float mx, float my, bool mLeft, bool mEdge) override;
  };

  template <typename T, bool under>
  struct Slider : public Widget
  {
    bool drag;

    char const * label;

    BoundingBox sliderBorder;
    BoundingBox slider;
    BoundingBox lminus;
    BoundingBox lplus;
    BoundingBox rminus;
    BoundingBox rplus;

    T minValue;
    T maxValue;
    T minExtent;
    T maxExtent;
    T * value;

    Slider()
    {}

    Slider(char const * label,
           int left, int top, int width, int height,
           T minValue, T maxValue,
           T minExtent, T maxExtent,
           T * value)
      : drag{ false }
      , label{ label }
      , sliderBorder{ left, top, width, height }
      , slider{ left, top + 2, width, height - 4 }
      , lminus{ left - 21, top + 3, 8, 8 }
      , lplus{ left - 11, top + 3, 8, 8 }
      , rminus{ left + width + 3, top + 3, 8, 8 }
      , rplus{ left + width + 13, top + 3, 8, 8 }
      , minValue{ minValue }
      , maxValue{ maxValue }
      , minExtent{ minExtent }
      , maxExtent{ maxExtent }
      , value{ value }
    {}

    void draw(MappedInstanceData<SolidInstance> & data,
              MappedInstanceData<font::BitmapInstance> & fontData) override;

    void update(float mx, float my, bool mLeft, bool mEdge) override;
  };

  struct DelayGainSlider : public Widget
  {
    char const * label;

    Slider<int, true> delay;
    Slider<float, true> gain;

    DelayGainSlider()
    {}

    DelayGainSlider(char const * label,
                    int left, int top,
                    int delayMin, int delayMax, int * delayValue,
                    float gainMin, float gainMax,
                    float * gainValue)
      : label(label)
      , delay("delay",
              left, top, 150, 14,
              delayMin, delayMax,
              delayMin, delayMax,
              delayValue)
      , gain("gain",
             left, top + 30, 150, 14,
             gainMin, gainMax,
             gainMin, gainMax,
             gainValue)
    {}

    void draw(MappedInstanceData<SolidInstance> & data,
              MappedInstanceData<font::BitmapInstance> & fontData) override;

    void update(float mx, float my, bool mLeft, bool mEdge) override;
  };
}
