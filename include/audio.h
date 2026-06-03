#pragma once

#include "renpy/language.h"
#include "poem.h"

namespace audio {
  constexpr int sample_rate = 48000;
  constexpr int channels = 2;

  template <int maxDelay>
  struct FeedbackCombFilter {
  private:
    //float * buffer;
    float buffer[maxDelay];
    int index;
  public:
    int delay;
    float gain0;
    float gainM;

    FeedbackCombFilter(int delay, float gain0, float gainM);
    void reset();
    float feed(float value);
  };

  template <int maxDelay>
  struct FeedforwardCombFilter {
  private:
    //float * buffer;
    float buffer[maxDelay];
    int index;
  public:
    int delay;
    float gain0;
    float gainM;

    FeedforwardCombFilter(int delay, float gain0, float gainM);
    void reset();
    float feed(float value);
  };

  template <int maxDelay>
  struct AllpassFilter {
  private:
    //float * buffer;
    float buffer[maxDelay];
    int index;

  public:
    int delay;
    float gain0;
    float gainM;

    AllpassFilter(int delay, float gain0, float gainM);
    void reset();
    float feed(float x);
  };

  using FBCF = FeedbackCombFilter<15000>;
  using FFCF = FeedforwardCombFilter<15000>;
  using AP = AllpassFilter<2500>;

  struct lr { float l; float r; };

  struct FBReverb {
    static constexpr int cfCount = 4;
    static constexpr int apCount = 3;

    FBCF cf[cfCount];
    AP ap[apCount];

    FBReverb();
    void reset();
    lr feed(float x);
  };

  struct FFReverb {
    static constexpr int __cfCount = 4;
    static constexpr int apCount = 3;

    FFCF cf[__cfCount];
    AP ap[apCount];

    FFReverb();
    void reset();
    lr feed(float x);
  };

  extern int reverbIndex;
  extern FBReverb fbreverb;
  extern FFReverb ffreverb;

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
