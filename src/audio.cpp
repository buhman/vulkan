#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <opus/opus.h>
#include <SDL3/SDL.h>

#include "file.h"
#include "audio.h"
#include "new.h"
#include "minmax.h"
#include "renpy/language.h"
#include "poem.h"

namespace audio {
  static int const frame_samples = 960; // 20 milliseconds @ 48kHz
  static int const sample_size = (sizeof (int16_t));

  static int const max_frame_size = 960 * 3; // 20ms at 48kHz
  static int const max_packet_size = 1275;

  static int const half_period_samples = sample_rate / 30;
  static int const half_period_size = half_period_samples * sample_size * channels;

  struct AudioBuffer {
    renpy::language::audio const * audio;
    int16_t * buf;
    uint32_t sample_count;
  };

  template <int maxDelay>
  FeedbackCombFilter<maxDelay>::FeedbackCombFilter(int delay, float gain0, float gainM)
    : delay(delay), gain0(gain0), gainM(gainM)
  {
    //buffer = (float *)malloc((sizeof (float)) * maxDelay);
    reset();
  }

  template <int maxDelay>
  void FeedbackCombFilter<maxDelay>::reset()
  {
    index = 0;
    memset(buffer, 0, (sizeof (float)) * maxDelay);
  }

  template <int maxDelay>
  float FeedbackCombFilter<maxDelay>::feed(float value)
  {
    float y = gain0 * value + gainM * buffer[index];
    buffer[index] = y;
    index = (index + 1) % delay;
    return y;
  }

  template <int maxDelay>
  FeedforwardCombFilter<maxDelay>::FeedforwardCombFilter(int delay, float gain0, float gainM)
    : delay(delay), gain0(gain0), gainM(gainM)
  {
    //buffer = (float *)malloc((sizeof (float)) * maxDelay);
    reset();
  }

  template <int maxDelay>
  void FeedforwardCombFilter<maxDelay>::reset()
  {
    index = 0;
    memset(buffer, 0, (sizeof (float)) * maxDelay);
  }

  template <int maxDelay>
  float FeedforwardCombFilter<maxDelay>::feed(float value)
  {
    float y = gain0 * value + gainM * buffer[index];
    buffer[index] = value;
    index = (index + 1) % delay;
    return y;
  }

  template <int maxDelay>
  AllpassFilter<maxDelay>::AllpassFilter(int delay, float gain0, float gainM)
    : delay(delay), gain0(gain0), gainM(gainM)
  {
    //buffer = (float *)malloc((sizeof (float)) * maxDelay);
    reset();
  }

  template <int maxDelay>
  void AllpassFilter<maxDelay>::reset()
  {
    index = 0;
    memset(buffer, 0, (sizeof (float)) * maxDelay);
  }

  template <int maxDelay>
  float AllpassFilter<maxDelay>::feed(float x)
  {
    float v = x + -gainM * buffer[index];
    float y = buffer[index] + gain0 * v;
    buffer[index] = v;
    index = (index + 1) % delay;
    return y;
  }

  struct AudioInstance {
    int audio_index;
    AudioBuffer * audio_buffer;
    uint32_t sample_index;
    uint32_t tail_index;
    uint32_t fadeout_end;
    uint32_t fadeout_index;
    poem::poem const * poem;
  };

  FBReverb::FBReverb()
    : cf{FBCF(3229, 1.0f, 0.733f), // 1687
         FBCF(3079, 1.0f, 0.802f), // 1601
         FBCF(3943, 1.0f, 0.753f), // 2053
         FBCF(4327, 1.0f, 0.733f), // 2251
      }
    , ap{AP(661, 0.7f, 0.7f), // 347
         AP(257, 0.7f, 0.7f), // 113
         AP(71, 0.7f, 0.7f), // 37
      }
  { }

  void FBReverb::reset()
  {
    for (int i = 0; i < cfCount; i++)
      cf[i].reset();

    for (int i = 0; i < apCount; i++)
      ap[i].reset();
  }

  lr FBReverb::feed(float x)
  {
    for (int i = 0; i < apCount; i++) {
      x = ap[i].feed(x);
    }

    float x0 = cf[0].feed(x);
    float x1 = cf[1].feed(x);
    float x2 = cf[2].feed(x);
    float x3 = cf[3].feed(x);

    float s0 = x0 + x2;
    float s1 = x1 + x3;

    float a = s0 + s1;
    float b = s0 - s1;
    return {a, b};
  }


  FFReverb::FFReverb()
    : cf{FFCF{9209, 1.0f, 0.742f},
         FFCF{9601, 1.0f, 0.733f},
         FFCF{10369, 1.0f, 0.715f},
         FFCF{11131, 1.0f, 0.697f},
      }
    , ap{AP{2017, 0.7f, 0.7f},
         AP{647, 0.7f, 0.7f},
         AP{137, 0.7f, 0.7f},
      }
  { }

  void FFReverb::reset()
  {
    for (int i = 0; i < __cfCount; i++) {
      printf("reset cf %d\n", i);
      cf[i].reset();
    }

    for (int i = 0; i < apCount; i++)
      ap[i].reset();
  }

  lr FFReverb::feed(float x)
  {
    for (int i = 0; i < apCount; i++) {
      x = ap[i].feed(x);
    }

    float x0 = cf[0].feed(x);
    float x1 = cf[1].feed(x);
    float x2 = cf[2].feed(x);
    float x3 = cf[3].feed(x);

    float s0 = x0 + x1 + x2 + x3;
    //float s0 = x0 + x1 + x2;
    return {s0, s0};
  }

  int reverbIndex = 0;
  FBReverb fbreverb;
  FFReverb ffreverb;

  float dryGain = 1.0;
  float wetGain = 0.25;
  float mixChannelGain[mixChannelCount];

  //

  static SDL_AudioStream * audio_stream;
  static SDL_AudioSpec audio_spec;

  static AudioBuffer * audio_buffers;
  static int audio_buffers_count;

  constexpr int max_audio_instances = 128;
  static AudioInstance audio_instances[max_audio_instances];
  static int audio_instances_count;

  void init()
  {
    audio_spec.channels = channels;
    audio_spec.format = SDL_AUDIO_F32LE;
    audio_spec.freq = sample_rate;
    audio_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audio_spec, NULL, NULL);
    assert(audio_stream);
    SDL_ResumeAudioStreamDevice(audio_stream);

    audio_instances_count = 0;
    fbreverb.reset();
    ffreverb.reset();

    for (int i = 0; i < mixChannelCount; i++) {
      mixChannelGain[i] = 1.0f;
    }
  }

  void decode(OpusDecoder * opus_decoder, char const * const filename, AudioBuffer * audio_buffer)
  {
    uint32_t size;
    uint8_t const * buf = (uint8_t const *)file::open(filename, &size);
    assert(buf != nullptr);

    uint32_t samples_count = (buf[3] << 24)
                           | (buf[2] << 16)
                           | (buf[1] << 8)
                           | (buf[0] << 0);
    uint32_t offset = 4;
    uint32_t samples_decoded = 0;
    uint32_t samples_copied = 0;

    int err = opus_decoder_ctl(opus_decoder, OPUS_RESET_STATE);
    if (err < 0) {
      fprintf(stderr, "opus_encoder_ctl(OPUS_RESET_STATE): %s\n", opus_strerror(err));
      assert(!"opus_encoder_ctl");
    }

    int16_t * output_buf = NewM<int16_t>(channels * samples_count);

    // decode packets
    while (offset < size) {
      uint16_t packet_size = (buf[offset + 1] << 8) | (buf[offset + 0] << 0);
      offset += 2;

      assert(offset + packet_size <= size);
      int16_t decode_buf[max_frame_size * channels];
      int frame_size = opus_decode(opus_decoder, &buf[offset], packet_size, decode_buf, max_frame_size, 0);
      if (frame_size < 0) {
        fprintf(stderr, "opus_decode: %s\n", opus_strerror(frame_size));
        assert(!"opus_decode\n");
      }
      samples_decoded += frame_size;

      uint32_t copy_samples = min(samples_decoded, samples_count) - samples_copied;
      memcpy(&output_buf[samples_copied * channels], decode_buf, copy_samples * channels * sample_size);

      samples_copied += copy_samples;
      offset += packet_size;
    }

    printf("copied %d decoded %d count %d\n", samples_copied, samples_decoded, samples_count);
    assert(samples_decoded >= samples_count);
    assert(samples_copied == samples_count);

    audio_buffer->buf = output_buf;
    audio_buffer->sample_count = samples_count;

    assert(audio_buffer->sample_count / 2);
  }

  struct LoadState {
    OpusDecoder * opus_decoder;
    renpy::language::audio const * audio;
    int start;
    int count;
  };

  static int loadAudio(void * data)
  {
    LoadState * loadState = (LoadState *)data;
    for (int i = loadState->start; i < loadState->start + loadState->count; i++) {
      audio_buffers[i].audio = &loadState->audio[i];
      decode(loadState->opus_decoder, loadState->audio[i].path, &audio_buffers[i]);
    }
    return 0;
  }

  void load(renpy::language::audio const * const audio, int count)
  {
    audio_buffers = NewM<AudioBuffer>(count);
    audio_buffers_count = count;

    int core_count = SDL_GetNumLogicalCPUCores();
    assert(core_count >= 1);
    SDL_Thread ** threads = NewM<SDL_Thread *>(core_count);
    LoadState * loadStates = NewM<LoadState>(core_count);

    int per_core_count = count / core_count;
    int remainder = count % core_count;
    int start = 0;
    for (int i = 0; i < core_count; i++) {
      int this_core_count = per_core_count;
      if (remainder) {
        this_core_count += 1;
        remainder -= 1;
      }

      int err;
      loadStates[i].opus_decoder = opus_decoder_create(sample_rate, channels, &err);
      if (err < 0) {
        fprintf(stderr, "opus_decoder_create: %s\n", opus_strerror(err));
        assert(!"opus_decoder_create");
      }

      loadStates[i].audio = audio;
      loadStates[i].start = start;
      loadStates[i].count = this_core_count;
      start += this_core_count;
      threads[i] = SDL_CreateThread(loadAudio, "loadAudio", &loadStates[i]);
    }

    for (int i = 0; i < core_count; i++) {
      SDL_WaitThread(threads[i], nullptr);
      opus_decoder_destroy(loadStates[i].opus_decoder);
    }
    free(threads);
    free(loadStates);
  }

  void play(int audio_index)
  {
    fprintf(stderr, "%d %d\n", audio_index, audio_buffers_count);
    assert(audio_index >= 0 && audio_index < audio_buffers_count);
    assert(audio_instances_count < max_audio_instances);

    AudioInstance & instance = audio_instances[audio_instances_count++];

    instance.audio_index = (int)audio_index;
    instance.audio_buffer = &audio_buffers[audio_index];
    instance.sample_index = 0;
    instance.tail_index = audio_buffers[audio_index].sample_count;
    instance.fadeout_end = 0;
    instance.fadeout_index = 0;
    if (strcmp(instance.audio_buffer->audio->path, "audio/poem/BirdSong.opus.bin") == 0) {
      instance.poem = &poem::birdsong;
    } else if (strcmp(instance.audio_buffer->audio->path, "audio/poem/EleanorTheHero.opus.bin") == 0) {
      instance.poem = &poem::eleanorthehero;
    } else if (strcmp(instance.audio_buffer->audio->path, "audio/poem/KiriStella.opus.bin") == 0) {
      instance.poem = &poem::kiristella;
    } else {
      instance.poem = nullptr;
    }
    if (instance.poem != nullptr) {
      poem_timestamp_index = 0;
      poem_line_index = 0;
    }
  }

  bool exists(int audio_index)
  {
    assert(audio_index >= 0 && audio_index < audio_buffers_count);
    for (int i = 0; i < audio_instances_count; i++) {
      if (audio_instances[i].audio_index == audio_index) {
        return true;
      }
    }
    return false;
  }

  void stop(int audio_index, double fadeout)
  {
    assert(audio_index >= 0 && audio_index < audio_buffers_count);

    for (int i = 0; i < audio_instances_count; i++) {
      if (audio_instances[i].audio_index == audio_index) {
        if (audio_instances[i].fadeout_end == 0) {
          fprintf(stderr, "audio: stop instance %d index %d\n", i, audio_index);
          audio_instances[i].fadeout_end = fadeout * (double)sample_rate;
          audio_instances[i].fadeout_index = 0;
        } else {
          fprintf(stderr, "audio: duplicate stop on instance %d index %d\n", i, audio_index);
        }
      }
    }
  }

  void stop_all()
  {
    audio_instances_count = 0;
  }

  static inline float clampf(float v)
  {
    if (v > 1.0f)
      return 1.0f;
    if (v < -1.0f)
      return -1.0f;
    return v;
  }

  static inline void remove_instance(int instance_index)
  {
    fprintf(stderr, "removed instance %d index %d\n", instance_index, audio_instances[instance_index].audio_index);

    for (int i = instance_index; i < (audio_instances_count - 1); i++) {
      audio_instances[i] = audio_instances[i + 1];
    }
    audio_instances_count -= 1;
  }

  static inline void update_instance(float * mix_buffer, AudioInstance & instance)
  {
    int16_t const * const buf = instance.audio_buffer->buf;
    uint32_t const sample_count = instance.audio_buffer->sample_count;
    uint32_t const loop_end = instance.audio_buffer->audio->loop_end * (double)sample_rate;
    uint32_t mix_index = 0;

    float bufferGain = instance.audio_buffer->audio->gain;

    for (int i = 0; i < half_period_samples; i++) {
      if (loop_end != 0.0) {
        if (instance.sample_index >= loop_end) {
          instance.sample_index = 0;
          instance.tail_index = loop_end;
        }
      } else if (instance.sample_index >= sample_count) {
        // non-looping at the end of the loop, do not play
        return;
      }

      if (instance.fadeout_end != 0 && instance.fadeout_index >= instance.fadeout_end) {
        return;
      }

      assert(instance.sample_index < sample_count);
      assert(instance.tail_index <= sample_count);

      float fadeout = 1.0;
      if (instance.fadeout_end != 0) {
        fadeout = 1.0 - ((float)instance.fadeout_index / (float)instance.fadeout_end);
      }

      for (int ch = 0; ch < channels; ch++) {
        float value = buf[instance.sample_index * channels + ch];
        if (instance.tail_index != sample_count) {
          value += buf[instance.tail_index * channels + ch];
        }
        constexpr float scale = 1.0f / 32768.0f;
        float output = value * fadeout * bufferGain * scale;
        mix_buffer[mix_index * channels + ch] += output;
      }
      instance.sample_index += 1;
      instance.fadeout_index += 1;
      if (instance.tail_index != sample_count) {
        instance.tail_index += 1;
      }

      mix_index += 1;
    }
  }

  static inline bool should_cull_instance(AudioInstance & instance)
  {
    if (instance.audio_buffer->audio->loop_end == 0.0 && instance.sample_index >= instance.audio_buffer->sample_count) {
      return true;
    }
    if (instance.fadeout_end != 0 && instance.fadeout_index >= instance.fadeout_end) {
      return true;
    }
    return false;
  }

  int poem_timestamp_index = 0;
  int poem_line_index = 0;
  poem::poem const * poem_playing = nullptr;

  void update_poem(AudioInstance & instance)
  {
    if (instance.poem == nullptr) {
      return;
    }

    poem::poem const * const poem = instance.poem;
    assert(poem_playing == nullptr);
    poem_playing = poem;

    if (poem_timestamp_index < (poem->timestamps_length - 1)) {
      double time = (double)instance.sample_index / (double)sample_rate;
      while (poem->timestamps[poem_timestamp_index + 1].time <= time) {
        poem_timestamp_index += 1;
      }
    }

    if (poem_line_index < (poem->lines_length - 1)) {
      while (poem->timestamps[poem_timestamp_index].wordIndex >= poem->lines[poem_line_index].start + poem->lines[poem_line_index].length) {
        poem_line_index += 1;
      }
    }
  }

  static inline int getMixChannel(AudioInstance & instance)
  {
    if (instance.audio_buffer->audio->audio_flags & renpy::language::audio::music) {
      return mix_channel::music;
    } else if (instance.audio_buffer->audio->audio_flags & renpy::language::audio::poem) {
      return mix_channel::poem;
    } else {
      return mix_channel::voice;
    }
  }

  void update()
  {
    float mix_buffer[half_period_samples * channels];
    float channel_buffer[mixChannelCount][half_period_samples * channels];
    static_assert((sizeof (channel_buffer)) == half_period_samples * channels * mixChannelCount * (sizeof (float)));

    if (SDL_GetAudioStreamQueued(audio_stream) >= (int)(sizeof (mix_buffer)))
      return;

    memset(&mix_buffer[0], 0, (sizeof (mix_buffer)));
    memset(&channel_buffer[0][0], 0, (sizeof (channel_buffer)));

    poem_playing = nullptr;
    for (int i = 0; i < audio_instances_count; i++) {
      update_instance(channel_buffer[getMixChannel(audio_instances[i])], audio_instances[i]);

      update_poem(audio_instances[i]);
    }

    bool culled = true;
    while (culled) {
      culled = false;
      for (int i = 0; i < audio_instances_count; i++) {
        if (should_cull_instance(audio_instances[i])) {
          culled = true;
          remove_instance(i);
          break;
        }
      }
    }

    // audio configuration "B"
    // mono reverberation
    for (int i = 0; i < half_period_samples; i++) {
      float value = channel_buffer[mix_channel::voice][i * channels + 0];

      lr wet;
      if (reverbIndex == 0) {
        wet = fbreverb.feed(value);
      }
      else {
        wet = ffreverb.feed(value);
      }
      float left = value * dryGain + wet.l * wetGain;
      float right = value * dryGain + wet.r * wetGain;
      channel_buffer[mix_channel::voice][i * channels + 0] = left;
      channel_buffer[mix_channel::voice][i * channels + 1] = right;
    }

    for (int i = 0; i < half_period_samples; i++) {
      for (int ch = 0; ch < channels; ch++) {
        float value = 0;
        for (int mixChannel = 0; mixChannel < mixChannelCount; mixChannel++) {
          float gain = mixChannelGain[mixChannel];
          value += channel_buffer[mixChannel][i * channels + ch] * gain;
        }
        mix_buffer[i * channels + ch] = clampf(value);
      }
    }

    SDL_PutAudioStreamData(audio_stream, (void *)mix_buffer, (int)(sizeof (mix_buffer)));
  }
}
