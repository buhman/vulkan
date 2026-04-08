#pragma once

#ifdef __aligned_alloc
#undef __aligned_alloc
#endif

#ifdef _WIN32
#include <stdlib.h>
#include <malloc.h>
#define __aligned_alloc(size, alignment) _aligned_malloc(size, alignment)
#else
#include <stdlib.h>
#define __aligned_alloc(size, alignment) aligned_alloc(alignment, size)
#endif

template <typename T>
inline T * NewA(int elements, size_t alignment)
{
  return (T *)__aligned_alloc((sizeof (T)) * elements, alignment);
}

template <typename T>
inline T * NewM(int elements)
{
  return (T *)malloc((sizeof (T)) * elements);
}
#undef __aligned_alloc
