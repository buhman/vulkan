#pragma once

#define SDL_CHECK(f) \
  { \
    bool result = (f); \
    if (result != true) { \
      fprintf(stderr, "SDL: %s %s L%d error: `%s`\n", __FILE__, __func__, __LINE__, SDL_GetError()); \
      exit(EXIT_FAILURE); \
    } \
  }

#define SDL_CHECK_NONNULL(f) \
  { \
    void * ptr = (void *)(f); \
    if (ptr == nullptr) { \
      fprintf(stderr, "SDL: %s %s L%d error: `%s`\n", __FILE__, __func__, __LINE__, SDL_GetError()); \
      exit(EXIT_FAILURE); \
    } \
  }

#define VK_CHECK(f) \
  { \
    VkResult result = (f); \
    if (result != VK_SUCCESS) { \
      fprintf(stderr, "VK: %s %s L%d error: `%s`\n", __FILE__, __func__, __LINE__, string_VkResult(result)); \
      exit(EXIT_FAILURE); \
    } \
  }

#define VK_CHECK_SWAPCHAIN(f) \
  { \
    VkResult result = (f); \
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) { \
      updateSwapchain = true; \
    } else if (result != VK_SUCCESS) { \
      fprintf(stderr, "VK: %s %s L%d error: `%s`\n", __FILE__, __func__, __LINE__, string_VkResult(result)); \
      exit(EXIT_FAILURE); \
    } \
  }

#define ASSERT(expr, msg) \
  { \
    bool result = (expr); \
    if (result != true) { \
      fprintf(stderr, "%s %s L%d error: `%s`\n", __FILE__, __func__, __LINE__, msg); \
      exit(EXIT_FAILURE); \
    } \
  }

#if defined(_MSC_VER) && !defined(__clang__) // MSVC
#define UNREACHABLE() __assume(false);
#else // GCC, Clang
#define UNREACHABLE() __builtin_unreachable();
#endif
