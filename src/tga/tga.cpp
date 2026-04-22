#include <assert.h>
#include <stddef.h>

#include "tga/tga.h"

namespace tga {
  header const * validate(void const * data, uint32_t size, void ** outData, uint32_t * outSize)
  {
    header const * const tga = (tga::header const *)data;

    assert(tga->colorMapType == 0);
    assert(tga->imageTypeCode == 2);
    assert(tga->image.xOrigin == 0);
    assert(tga->image.yOrigin == 0);
    assert(tga->image.bitsPerPixel == 32);


    uint32_t bytesPerPixel = tga->image.bitsPerPixel / 8;
    size_t imageOffset = (sizeof (header)) + tga->idLength;
    *outData = (void *)(((size_t)data) + imageOffset);
    *outSize = tga->image.width * tga->image.width * bytesPerPixel;

    return tga;
  }
}
