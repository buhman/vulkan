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

  int const frame_samples = 960; // 20 milliseconds @ 48kHz
  int const sample_rate = 48000;
  int const channels = 2;
  int const sample_size = (sizeof (int16_t));

  int const max_frame_size = 960 * 3; // 20ms at 48kHz
  int const max_packet_size = 1275;

  //

  SDL_AudioStream * audio_stream;
  SDL_AudioSpec audio_spec;

  OpusDecoder * opus_decoder;

  struct AudioBuffer {
    renpy::language::audio const * audio;
    int16_t * buf;
    uint32_t sample_count;
  };

  struct AudioInstance {
    AudioBuffer * audio_buffer;
    uint32_t sample_index;
    uint32_t tail_index;
  };

  AudioBuffer * audio_buffers;

  constexpr int max_audio_instances = 16;
  AudioInstance audio_instances[max_audio_instances];
  int instance_count;

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

    instance_count = 0;
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
    for (int i = 0; i < count; i++) {
      audio_buffers[i].audio = &audio[i];
      decode(audio[i].path, &audio_buffers[i]);
      //audio_instances[i].audio_buffer = &audio_buffers[i];
      //audio_instances[i].sample_index = 0;
      //audio_instances[i].tail_index = audio_buffers[i].sample_count;
    }
  }

  inline static int min(int a, int b)
  {
    return (a < b) ? a : b;
  }

  void update()
  {
    int half_period_samples = audio_spec.freq / 2;
    int half_period_size = half_period_samples * sample_size * audio_spec.channels;
    if (SDL_GetAudioStreamQueued(audio_stream) >= half_period_size)
      return;

    int16_t mix_buffer[half_period_samples * channels];
    memset(mix_buffer, 0, (sizeof (mix_buffer)));

    /*
    AudioInstance & instance = audio_instances[0];
    int16_t const * const buf = instance.audio_buffer->buf;
    uint32_t const sample_count = instance.audio_buffer->sample_count;
    uint32_t const loop_end = instance.audio_buffer->audio_file->loop_end;

    uint32_t mix_index = 0;
    for (int i = 0; i < half_period_samples; i++) {
      if (instance.sample_index >= loop_end) {
        instance.sample_index = 0;
        instance.tail_index = loop_end;
        fprintf(stderr, "loop\n");
      }

      assert(instance.sample_index < sample_count);
      assert(instance.tail_index <= sample_count);

      for (int ch = 0; ch < channels; ch++) {
        mix_buffer[mix_index * channels + ch] += buf[instance.sample_index * channels + ch];
        if (instance.tail_index != sample_count) {
          mix_buffer[mix_index * channels + ch] += buf[instance.tail_index * channels + ch];
        }
      }
      instance.sample_index += 1;
      if (instance.tail_index != sample_count) {
        instance.tail_index += 1;
      }

      mix_index += 1;
    }

    SDL_PutAudioStreamData(audio_stream, (void *)mix_buffer, half_period_size);
    */
  }
}
