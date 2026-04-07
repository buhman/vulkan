#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "pack.h"
#include "file.h"

extern "C" {
  extern uint8_t const _files_pack_start[];
  extern uint8_t const _files_pack_end[];
};

namespace file {

  void const * open(const char * r_filename, uint32_t * out_size)
  {
    fprintf(stderr, "(pack) filename: %s\n", r_filename);

    pack::header const * header = (pack::header const *)&_files_pack_start[0];
    if (header->magic != pack::magic_value) {
      fprintf(stderr, "invalid header magic: %08x expected magic value: %08x\n", header->magic, pack::magic_value);
      exit(EXIT_FAILURE);
    }
    ptrdiff_t data = (ptrdiff_t)&_files_pack_start[header->header_size];

    for (unsigned int i = 0; i < header->entry_count; i++) {
      if (strcmp(header->entry[i].filename, r_filename) == 0) {
        *out_size = header->entry[i].size;
        return (void const *)(data + header->entry[i].offset);
      }
    }

    fprintf(stderr, "filename not found in pack file %s\n", r_filename);
    exit(EXIT_FAILURE);
  }

}
