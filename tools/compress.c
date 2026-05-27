#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "zlib.h"

/*
ZEXTERN int ZEXPORT compress2(Bytef *dest, uLongf *destLen,
                              const Bytef *source, uLong sourceLen,
                              int level);
*/

void const * read_file(const char * filename, int * out_size)
{
  fprintf(stderr, "filename: %s\n", filename);

  FILE * f = fopen(filename, "rb");
  if (f == NULL) {
    fprintf(stderr, "fopen(%s): %s\n", filename, strerror(errno));
    return NULL;
  }

  int fseek_end_ret = fseek(f, 0, SEEK_END);
  if (fseek_end_ret < 0) {
    fprintf(stderr, "fseek(%s, SEEK_END): %s\n", filename, strerror(errno));
    return NULL;
  }

  size_t size = ftell(f);
  if (size < 0) {
    fprintf(stderr, "ftell(%s): %s\n", filename, strerror(errno));
    return NULL;
  }

  int fseek_set_ret = fseek(f, 0, SEEK_SET);
  if (fseek_set_ret < 0) {
    fprintf(stderr, "lseek(%s, SEEK_SET): %s\n", filename, strerror(errno));
    return NULL;
  }
  rewind(f);

  void * buf = malloc(size);

  size_t read_size = fread(buf, 1, size, f);
  if (read_size != size) {
    fprintf(stderr, "fread(%s): %s\n", filename, strerror(errno));
    return NULL;
  }

  *out_size = size;

  return buf;
}

int main(int argc, char const * const argv[])
{
  assert(argc == 3);
  const char * in_filename = argv[1];
  const char * out_filename = argv[2];

  int out_size;
  void const * buf = read_file(in_filename, &out_size);
  assert(buf != NULL);

  void * dest = malloc(out_size * 0.001 + out_size + 12);

  static_assert((sizeof (long unsigned int)) == (sizeof (uint64_t)));
  uint64_t dest_size = out_size;
  int level = 9;
  int zret = compress2(dest, &dest_size, buf, out_size, level);
  assert(zret == Z_OK);

  FILE * f = fopen(out_filename, "wb");
  if (f == NULL) {
    fprintf(stderr, "fopen(%s): %s\n", out_filename, strerror(errno));
    return EXIT_FAILURE;
  }

  uint32_t header[3];
  header[0] = 0x56c8f1cb; // magic
  header[1] = out_size; // decompressed size
  header[2] = dest_size; // compressed size
  fwrite(header, (sizeof (uint32_t)), 3, f);
  fwrite(dest, dest_size, 1, f);
}
