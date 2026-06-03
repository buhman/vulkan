#pragma once

template <typename T>
inline static constexpr T min(T a, T b)
{
  return (a < b) ? a : b;
}

template <typename T>
inline static constexpr T max(T a, T b)
{
  return (a > b) ? a : b;
}

template <typename T>
inline static constexpr T clamp(T n, T minVal, T maxVal)
{
  return min(max(n, minVal), maxVal);
}

template <typename T>
static inline T clamp01(T a)
{
  if (a < 0.0) return 0.0;
  if (a > 1.0) return 1.0;
  return a;
}
