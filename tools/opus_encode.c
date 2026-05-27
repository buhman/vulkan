#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <opus/opus.h>

const int frame_size = 960; // 20ms at 48kHz
const int sample_rate = 48000;
const int channels = 2;
const int bitrate = 128000;

const int max_packet_size = 3 * 1275;

int main(int argc, char *argv[])
{
  assert(argc == 3);
  int err;

  OpusEncoder * encoder = opus_encoder_create(sample_rate, channels, OPUS_APPLICATION_AUDIO, &err);
  if (err < 0) {
    fprintf(stderr, "opus_encoder_create: %s\n", opus_strerror(err));
    return 1;
  }

  err = opus_encoder_ctl(encoder, OPUS_SET_BITRATE(bitrate));
  if (err < 0) {
    fprintf(stderr, "opus_encoder_ctl(OPUS_SET_BITRATE): %s\n", opus_strerror(err));
    return 1;
  }

  char const * input_filename = argv[1];
  FILE * input_file = fopen(input_filename, "rb");
  if (input_file == NULL) {
    fprintf(stderr, "fopen(%s): %s\n", input_filename, strerror(errno));
    return 1;
  }

  char const * output_filename = argv[2];
  FILE * output_file = fopen(output_filename, "wb");
  if (input_file == NULL) {
    fprintf(stderr, "fopen(%s): %s\n", output_filename, strerror(errno));
    return 1;
  }

  int16_t input[frame_size * channels];
  uint8_t input_buf[frame_size * channels * (sizeof (int16_t))];
  uint8_t encode_buf[max_packet_size];

  int total_samples = 0;
  size_t header_write_1 = fwrite(&total_samples, 1, (sizeof (int)), output_file);
  if (header_write_1 != (sizeof (int))) {
    fprintf(stderr, "fwrite: %s\n", strerror(errno));
    return 1;
  }

  bool more_data = true;
  while (more_data) {
    size_t samples = fread(input_buf, (sizeof (int16_t)) * channels, frame_size, input_file);
    if (samples == 0)
      break;

    total_samples += samples;

    if (samples != frame_size) {
      printf("padding short frame %ld\n", samples);
      more_data = false;
      for (int i = samples * channels; i < frame_size * channels; i++) {
        input_buf[i * 2 + 0] = 0;
        input_buf[i * 2 + 1] = 0;
      }
    }
    samples = frame_size;

    for (int i = 0; i < channels * frame_size; i++) {
      // load little endian
      input[i] = (input_buf[2 * i + 1] << 8) | (input_buf[2 * i + 0] << 0);
    }

    int bytes = opus_encode(encoder, input, frame_size, encode_buf, max_packet_size);
    if (bytes < 0) {
      fprintf(stderr, "opus_encode: %s\n", opus_strerror(bytes));
      return 1;
    }
    assert(bytes <= 1275);

    int16_t encode_bytes = bytes;
    size_t bytes_write = fwrite(&encode_bytes, 1, (sizeof (encode_bytes)), output_file);
    if (bytes_write != (sizeof (encode_bytes))) {
      fprintf(stderr, "fwrite: %s\n", strerror(errno));
      return 1;
    }
    size_t buf_write = fwrite(encode_buf, 1, bytes, output_file);
    if (buf_write != bytes) {
      fprintf(stderr, "fwrite: %s\n", strerror(errno));
      return 1;
    }
  }

  fflush(output_file);

  int ret = fseek(output_file, SEEK_SET, 0);
  if (ret != 0) {
    fprintf(stderr, "fseek: %s\n", strerror(errno));
    return 1;
  }

  size_t header_write_2 = fwrite(&total_samples, 1, (sizeof (int)), output_file);
  if (header_write_2 != (sizeof (int))) {
    fprintf(stderr, "fwrite: %s\n", strerror(errno));
    return 1;
  }
  printf("total_samples: %d\n", total_samples);

  fclose(output_file);
  fclose(input_file);

  return 0;
}
