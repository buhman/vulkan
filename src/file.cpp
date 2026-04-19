#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include "pack.h"
#include "file.h"

extern "C" {
#ifdef __APPLE__
  extern uint8_t const files_pack_start[];
  extern uint8_t const files_pack_end[];
  #define files_pack_start files_pack_start
  #define files_pack_end files_pack_end
#else
  extern uint8_t const _files_pack_start[];
  extern uint8_t const _files_pack_end[];
  #define files_pack_start _files_pack_start
  #define files_pack_end _files_pack_end
#endif
};

namespace file {

  void const * open(const char * filename, uint32_t * out_size)
  {
    fprintf(stderr, "(pack) filename: %s\n", filename);

    pack::header const * header = (pack::header const *)&files_pack_start[0];
    if (header->magic != pack::magic_value) {
      fprintf(stderr, "invalid header magic: %08x expected magic value: %08x\n", header->magic, pack::magic_value);
      exit(EXIT_FAILURE);
    }
    ptrdiff_t data = (ptrdiff_t)&files_pack_start[header->header_size];

    for (unsigned int i = 0; i < header->entry_count; i++) {
      if (strcmp(header->entry[i].filename, filename) == 0) {
        *out_size = header->entry[i].size;
        return (void const *)(data + header->entry[i].offset);
      }
    }

    fprintf(stderr, "filename not found in pack file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  void * openRelative(char const * filename, uint32_t * out_size)
  {
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
}
