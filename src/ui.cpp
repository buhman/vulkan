#include "ui.h"
#include "audio.h"

namespace ui
{
  constexpr int top = 75;
  constexpr int ySpace = 120;
  constexpr int yMixSpace = 60;

  constexpr int inputMixLeft = 100;
  constexpr int allpassLeft = 400;
  constexpr int combLeft = 700;
  constexpr int outputMixLeft = 1000;


  struct ap_comb {
    widget::DelayGainSlider ap[3];
    widget::DelayGainSlider comb[4];
  };

  ap_comb reverberatorSliders[2];

  widget::Slider<float, false> dryGain("dry gain",
                                       outputMixLeft, top + yMixSpace * 0, 150, 14,
                                       0.0, 1.0, 0.0, 1.0,
                                       &audio::dryGain);

  widget::Slider<float, false> wetGain("wet gain",
                                       outputMixLeft, top + yMixSpace * 1, 150, 14,
                                       0.0, 1.0, 0.0, 1.0,
                                       &audio::wetGain);

  widget::Slider<float, false> voiceGain("voice gain",
                                       inputMixLeft, top + yMixSpace * 0, 150, 14,
                                       0.0, 1.0, 0.0, 1.0,
                                         &audio::mixChannelGain[audio::mix_channel::voice]);

  widget::Slider<float, false> poemGain("poem gain",
                                       inputMixLeft, top + yMixSpace * 1, 150, 14,
                                       0.0, 1.0, 0.0, 1.0,
                                       &audio::mixChannelGain[audio::mix_channel::poem]);

  widget::Slider<float, false> musicGain("music gain",
                                         inputMixLeft, top + yMixSpace * 2, 150, 14,
                                         0.0, 1.0, 0.0, 1.0,
                                         &audio::mixChannelGain[audio::mix_channel::music]);

  const char * reverberatorNames[] = {
    "feed-back",
    "feed-forward",
  };
  widget::Radio<2> reverberators("reverberator",
                                 reverberatorNames,
                                 950, 200, 100, 40,
                                 120, 0,
                                 &audio::reverbIndex);

  void init()
  {
    static const char * allpassLabels[3] = {
      "allpass 0",
      "allpass 1",
      "allpass 2",
    };
    static const char * combLabels[4] = {
      "comb 0",
      "comb 1",
      "comb 2",
      "comb 3",
    };

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        reverberatorSliders[i].ap[j] =
          widget::DelayGainSlider(allpassLabels[j],
                                  allpassLeft, top + ySpace * j,
                                  1, audio::reverbs[i].ap[j].maxDelay, &audio::reverbs[i].ap[j].delay,
                                  0.0, 1.0, &audio::reverbs[i].ap[j].gain);
      }
      for (int j = 0; j < 4; j++) {
        reverberatorSliders[i].comb[j] =
          widget::DelayGainSlider(combLabels[j],
                                  combLeft, top + ySpace * j,
                                  100, audio::reverbs[i].cf[j].maxDelay, &audio::reverbs[i].cf[j].delay,
                                  0.0, 1.0, &audio::reverbs[i].cf[j].gain);
      }
    }
  }

  void draw(MappedInstanceData<SolidInstance> & data,
            MappedInstanceData<font::BitmapInstance> & fontData)
  {
    data.append({
        { (uint16_t)0, (uint16_t)0 },
        { (uint16_t)1280, (uint16_t)720 },
        0x80000000,
      });

    widget::DelayGainSlider * ap = reverberatorSliders[audio::reverbIndex].ap;
    widget::DelayGainSlider * comb = reverberatorSliders[audio::reverbIndex].comb;

    for (int i = 0; i < 3; i++)
      ap[i].draw(data, fontData);

    for (int i = 0; i < 4; i++)
      comb[i].draw(data, fontData);

    dryGain.draw(data, fontData);
    wetGain.draw(data, fontData);

    voiceGain.draw(data, fontData);
    poemGain.draw(data, fontData);
    musicGain.draw(data, fontData);

    reverberators.draw(data, fontData);
  }

  void update(float mx, float my, bool mLeft, bool mEdge)
  {
    widget::DelayGainSlider * ap = reverberatorSliders[audio::reverbIndex].ap;
    widget::DelayGainSlider * comb = reverberatorSliders[audio::reverbIndex].comb;

    for (int i = 0; i < 3; i++)
      ap[i].update(mx, my, mLeft, mEdge);

    for (int i = 0; i < 4; i++)
      comb[i].update(mx, my, mLeft, mEdge);

    dryGain.update(mx, my, mLeft, mEdge);
    wetGain.update(mx, my, mLeft, mEdge);

    voiceGain.update(mx, my, mLeft, mEdge);
    poemGain.update(mx, my, mLeft, mEdge);
    musicGain.update(mx, my, mLeft, mEdge);

    reverberators.update(mx, my, mLeft, mEdge);
  }
}
