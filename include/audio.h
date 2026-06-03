#pragma once

#include "renpy/language.h"
#include "poem.h"

namespace audio {
  constexpr int sample_rate = 48000;
  constexpr int channels = 2;

  struct DelayFilter {
    float * buffer;
    int index;

    const int maxDelay;
    int delay;
    float gain;

    DelayFilter(int maxDelay, int delay, float gain);

    void reset();
    virtual float feed(float value) = 0;
  };

  struct FeedbackCombFilter : DelayFilter {
    FeedbackCombFilter(int maxDelay, int delay, float gain);
    float feed(float value) override;
  };

  struct FeedforwardCombFilter : DelayFilter {
  public:
    FeedforwardCombFilter(int maxDelay, int delay, float gain);
    float feed(float value) override;
  };

  struct AllpassFilter : DelayFilter {
    AllpassFilter(int maxDelay, int delay, float gain);
    float feed(float x) override;
  };

  using FBCF = FeedbackCombFilter;
  using FFCF = FeedforwardCombFilter;
  using AP = AllpassFilter;

  struct lr { float l; float r; };

  struct Reverb {
    static constexpr int apCount = 3;
    static constexpr int cfCount = 4;

    DelayFilter * cf;
    DelayFilter * ap;

    Reverb(DelayFilter * cf, DelayFilter * ap);
    void reset();
    lr feed(float x);
  };

  extern int reverbIndex;
  extern Reverb * reverbs[];
  extern int const reverbsCount;

  extern float wetGain;
  extern float dryGain;

  struct mix_channel {
    enum {
      music = 0,
      poem = 1,
      voice = 2,
    };
  };

  constexpr int mixChannelCount = 3;
  extern float mixChannelGain[mixChannelCount];

  extern int poem_timestamp_index;
  extern int poem_line_index;
  extern poem::poem const * poem_playing;

  void init();
  void load(renpy::language::audio const * const audio, int count);
  void update();
  void play(int audio_index);
  void stop(int audio_index, double fadeout);
  void stop_all();
  bool exists(int audio_index);
}
