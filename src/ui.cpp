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

#define BREVERB audio::fbreverb
#define FREVERB audio::ffreverb

  widget::DelayGainSlider fap[3] {
    widget::DelayGainSlider("allpass 0",
                            allpassLeft, top + ySpace * 0,
                            1, 2500, &FREVERB.ap[0].delay,
                            0.0, 1.0, &FREVERB.ap[0].gain0, &FREVERB.ap[0].gainM),
    widget::DelayGainSlider("allpass 1",
                            allpassLeft, top + ySpace * 1,
                            1, 2500, &FREVERB.ap[1].delay,
                            0.0, 1.0, &FREVERB.ap[1].gain0, &FREVERB.ap[1].gainM),
    widget::DelayGainSlider("allpass 2",
                            allpassLeft, top + ySpace * 2,
                            1, 2500, &FREVERB.ap[2].delay,
                            0.0, 1.0, &FREVERB.ap[2].gain0, &FREVERB.ap[2].gainM),
  };

  widget::DelayGainSlider fcomb[4] {
    widget::DelayGainSlider("comb 0",
                            combLeft, top + ySpace * 0,
                            100, 15000, &FREVERB.cf[0].delay,
                            0.0, 1.0, &FREVERB.cf[0].gain0, &FREVERB.cf[0].gainM),
    widget::DelayGainSlider("comb 1",
                            combLeft, top + ySpace * 1,
                            100, 15000, &FREVERB.cf[1].delay,
                            0.0, 1.0, &FREVERB.cf[1].gain0, &FREVERB.cf[1].gainM),
    widget::DelayGainSlider("comb 2",
                            combLeft, top + ySpace * 2,
                            100, 15000, &FREVERB.cf[2].delay,
                            0.0, 1.0, &FREVERB.cf[2].gain0, &FREVERB.cf[2].gainM),
    widget::DelayGainSlider("comb 3",
                            combLeft, top + ySpace * 3,
                            100, 15000, &FREVERB.cf[3].delay,
                            0.0, 1.0, &FREVERB.cf[3].gain0, &FREVERB.cf[3].gainM),
  };

  widget::DelayGainSlider bap[3] {
    widget::DelayGainSlider("allpass 0",
                            allpassLeft, top + ySpace * 0,
                            1, 2500, &BREVERB.ap[0].delay,
                            0.0, 1.0, &BREVERB.ap[0].gain0, &BREVERB.ap[0].gainM),
    widget::DelayGainSlider("allpass 1",
                            allpassLeft, top + ySpace * 1,
                            1, 2500, &BREVERB.ap[1].delay,
                            0.0, 1.0, &BREVERB.ap[1].gain0, &BREVERB.ap[1].gainM),
    widget::DelayGainSlider("allpass 2",
                            allpassLeft, top + ySpace * 2,
                            1, 2500, &BREVERB.ap[2].delay,
                            0.0, 1.0, &BREVERB.ap[2].gain0, &BREVERB.ap[2].gainM),
  };

  widget::DelayGainSlider bcomb[4] {
    widget::DelayGainSlider("comb 0",
                            combLeft, top + ySpace * 0,
                            100, 15000, &BREVERB.cf[0].delay,
                            0.0, 1.0, &BREVERB.cf[0].gain0, &BREVERB.cf[0].gainM),
    widget::DelayGainSlider("comb 1",
                            combLeft, top + ySpace * 1,
                            100, 15000, &BREVERB.cf[1].delay,
                            0.0, 1.0, &BREVERB.cf[1].gain0, &BREVERB.cf[1].gainM),
    widget::DelayGainSlider("comb 2",
                            combLeft, top + ySpace * 2,
                            100, 15000, &BREVERB.cf[2].delay,
                            0.0, 1.0, &BREVERB.cf[2].gain0, &BREVERB.cf[2].gainM),
    widget::DelayGainSlider("comb 3",
                            combLeft, top + ySpace * 3,
                            100, 15000, &BREVERB.cf[3].delay,
                            0.0, 1.0, &BREVERB.cf[3].gain0, &BREVERB.cf[3].gainM),
  };

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

  void draw(MappedInstanceData<SolidInstance> & data,
            MappedInstanceData<font::BitmapInstance> & fontData)
  {
    data.append({
        { (uint16_t)0, (uint16_t)0 },
        { (uint16_t)1280, (uint16_t)720 },
        0x80000000,
      });

    widget::DelayGainSlider * ap = (audio::reverbIndex == 0) ? bap : fap;
    widget::DelayGainSlider * comb = (audio::reverbIndex == 0) ? bcomb : fcomb;

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
    widget::DelayGainSlider * ap = (audio::reverbIndex == 0) ? bap : fap;
    widget::DelayGainSlider * comb = (audio::reverbIndex == 0) ? bcomb : fcomb;

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
