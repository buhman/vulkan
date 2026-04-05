#pragma once

#ifdef __aligned_alloc
#undef __aligned_alloc
#endif
#ifdef __alloca
#undef __alloca
#endif

#ifdef _WIN32
#include <stdlib.h>
#include <malloc.h>
#define __aligned_alloc(alignment, size) _aligned_malloc(size, alignment)
#define __alloca(size) _malloca(size)
#else
#include <stdlib.h>
#define __aligned_alloc(alignment, size) aligned_alloc(alignment, size)
#define __alloca(size) alloca(size)
#endif

template <typename T>
T * New(int elements)
{
  return (T *)__aligned_alloc(16, (sizeof (T)) * elements);
}

template <typename T>
T * NewM(int elements)
{
  return (T *)malloc((sizeof (T)) * elements);
}

/*
template <typename T>
T * NewA(int elements)
{
  return (T *)__alloca((sizeof (T)) * elements);
}
*/

#undef __alloca
#undef __aligned_alloc
