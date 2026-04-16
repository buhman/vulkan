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
