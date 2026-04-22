#include <stdint.h>

#define PACKED __attribute__((packed))

namespace tga {
  struct PACKED header {
    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageTypeCode;
    struct PACKED {
      uint16_t origin;
      uint16_t length;
      uint8_t depth;
    } colorMap;
    struct PACKED {
      uint16_t xOrigin;
      uint16_t yOrigin;
      uint16_t width;
      uint16_t height;
      uint8_t bitsPerPixel;
    } image;
    uint8_t descriptor;
  };
  static_assert((sizeof (header)) == 18);

  header const * validate(void const * data, uint32_t size, void ** outData, uint32_t * outSize);

  static inline bool isTGAExtension(const char * filename, size_t length)
  {
    char a = filename[length - 4];
    char b = filename[length - 3];
    char c = filename[length - 2];
    char d = filename[length - 1];

    return
      (a == '.') &&
      (b == 't' || b == 'T') &&
      (c == 'g' || c == 'G') &&
      (d == 'a' || d == 'A');
  }
}

#undef PACKED
