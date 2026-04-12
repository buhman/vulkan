#pragma once

#include "directxmath/directxmath.h"

constexpr uint32_t maxFramesInFlight{ 2 };

struct ShaderData {
  XMFLOAT4X4 projection;
  XMFLOAT4X4 modelView[16];
  XMFLOAT4 lightPosition;
};

struct ShaderDataDevice {
  VkDeviceMemory memory;
  VkDeviceAddress stride;
  void * mappedData;
  struct {
    VkBuffer buffer{ VK_NULL_HANDLE };
    VkDeviceAddress deviceAddress{};
  } frame[maxFramesInFlight];
};
