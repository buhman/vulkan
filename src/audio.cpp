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

namespace audio {

  static int const frame_samples = 960; // 20 milliseconds @ 48kHz
  static int const sample_rate = 48000;
  static int const channels = 2;
  static int const sample_size = (sizeof (int16_t));

  static int const max_frame_size = 960 * 3; // 20ms at 48kHz
  static int const max_packet_size = 1275;

  static int const half_period_samples = sample_rate / 30;
  static int const half_period_size = half_period_samples * sample_size * channels;

  //

  static SDL_AudioStream * audio_stream;
  static SDL_AudioSpec audio_spec;

  static OpusDecoder * opus_decoder;

  struct AudioBuffer {
    renpy::language::audio const * audio;
    int16_t * buf;
    uint32_t sample_count;
  };

  struct AudioInstance {
    int audio_index;
    AudioBuffer * audio_buffer;
    uint32_t sample_index;
    uint32_t tail_index;
    uint32_t fadeout_end;
    uint32_t fadeout_index;
  };

  static AudioBuffer * audio_buffers;
  static int audio_buffers_count;

  constexpr int max_audio_instances = 128;
  static AudioInstance audio_instances[max_audio_instances];
  static int audio_instances_count;

  void init()
  {
    audio_spec.channels = channels;
    audio_spec.format = SDL_AUDIO_S16LE;
    audio_spec.freq = sample_rate;
    audio_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audio_spec, NULL, NULL);
    assert(audio_stream);
    SDL_ResumeAudioStreamDevice(audio_stream);

    int err;
    opus_decoder = opus_decoder_create(sample_rate, channels, &err);
    if (err < 0) {
      fprintf(stderr, "opus_decoder_create: %s\n", opus_strerror(err));
      assert(!"opus_decoder_create");
    }

    audio_instances_count = 0;
  }

  void decode(char const * const filename, AudioBuffer * audio_buffer)
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

  void load(renpy::language::audio const * const audio, int count)
  {
    audio_buffers = NewM<AudioBuffer>(count);
    audio_buffers_count = count;
    for (int i = 0; i < count; i++) {
      audio_buffers[i].audio = &audio[i];
      decode(audio[i].path, &audio_buffers[i]);
    }
  }

  void play(int audio_index)
  {
    assert(audio_index >= 0 && audio_index < audio_buffers_count);
    assert(audio_instances_count < max_audio_instances);

    AudioInstance & instance = audio_instances[audio_instances_count++];

    instance.audio_index = (int)audio_index;
    instance.audio_buffer = &audio_buffers[audio_index];
    instance.sample_index = 0;
    instance.tail_index = audio_buffers[audio_index].sample_count;
    instance.fadeout_end = 0;
    instance.fadeout_index = 0;
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

  static inline void saturation_add(int16_t * mix_buffer, int32_t value)
  {
    int32_t mix_value = *mix_buffer;
    mix_value += value;
    if (mix_value > 32767)
      mix_value = 32767;
    if (mix_value < -32768)
      mix_value = -32768;
    *mix_buffer = mix_value;
  }

  static inline void remove_instance(int instance_index)
  {
    fprintf(stderr, "removed instance %d index %d\n", instance_index, audio_instances[instance_index].audio_index);

    for (int i = instance_index; i < (audio_instances_count - 1); i++) {
      audio_instances[i] = audio_instances[i + 1];
    }
    audio_instances_count -= 1;
  }

  static inline void update_instance(int16_t * mix_buffer, AudioInstance & instance)
  {
    int16_t const * const buf = instance.audio_buffer->buf;
    uint32_t const sample_count = instance.audio_buffer->sample_count;
    uint32_t const loop_end = instance.audio_buffer->audio->loop_end * (double)sample_rate;

    uint32_t mix_index = 0;
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


      double fadeout = 1.0;
      if (instance.fadeout_end != 0) {
        fadeout = 1.0 - ((double)instance.fadeout_index / (double)instance.fadeout_end);
      }

      for (int ch = 0; ch < channels; ch++) {
        int32_t value = buf[instance.sample_index * channels + ch];
        if (instance.tail_index != sample_count) {
          value += buf[instance.tail_index * channels + ch];
        }
        saturation_add(&mix_buffer[mix_index * channels + ch], (double)value * fadeout);
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

  void update()
  {
    if (SDL_GetAudioStreamQueued(audio_stream) >= half_period_size)
      return;

    int16_t mix_buffer[half_period_samples * channels];
    memset(mix_buffer, 0, (sizeof (mix_buffer)));

    for (int i = 0; i < audio_instances_count; i++) {
      update_instance(mix_buffer, audio_instances[i]);
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

    SDL_PutAudioStreamData(audio_stream, (void *)mix_buffer, half_period_size);
  }
}
