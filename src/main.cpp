#include <stdio.h>
#include <stdlib.h>

#include "volk.h"
#include "vulkan/vk_enum_string_helper.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
#include "directxmath/directxmath.h"

#include "new.h"

extern "C" {
  extern uint8_t const _binary_position_normal_texture_vtx_start[];
  extern void * const _binary_position_normal_texture_vtx_size;
  extern uint8_t const _binary_index_idx_start[];
  extern void * const _binary_index_idx_size;

  extern uint8_t const _binary_shader_triangle_vs_spv_start[];
  extern void * const _binary_shader_triangle_vs_spv_size;
  extern uint8_t const _binary_shader_triangle_ps_spv_start[];
  extern void * const _binary_shader_triangle_ps_spv_size;

  extern uint8_t const _binary_sprite_data_start[];
  extern void * const _binary_sprite_data_size;
}

#define vtx_start _binary_position_normal_texture_vtx_start
#define vtx_size (size_t)(&_binary_position_normal_texture_vtx_size)
#define idx_start _binary_index_idx_start
#define idx_size (size_t)(&_binary_index_idx_size)

#define vs_start _binary_shader_triangle_vs_spv_start
#define vs_size (size_t)(&_binary_shader_triangle_vs_spv_size)
#define ps_start _binary_shader_triangle_ps_spv_start
#define ps_size (size_t)(&_binary_shader_triangle_ps_spv_size)

#define sprite_start _binary_sprite_data_start
#define sprite_size (size_t)(&_binary_sprite_data_size)

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

constexpr uint32_t maxFramesInFlight{ 2 };

VkInstance instance{ VK_NULL_HANDLE };
VkDevice device{ VK_NULL_HANDLE };
VkQueue queue{ VK_NULL_HANDLE };
VkSurfaceKHR surface{ VK_NULL_HANDLE };
VkSwapchainKHR swapchain{ VK_NULL_HANDLE };

uint32_t swapchainImageCount{ 0 };
VkImage * swapchainImages{ nullptr };
VkImageView * swapchainImageViews{ nullptr };

VkImage depthImage{ VK_NULL_HANDLE };
VkImageView depthImageView{ VK_NULL_HANDLE };
VkDeviceMemory depthImageMemory{ VK_NULL_HANDLE };

VkBuffer vertexIndexBuffer{ VK_NULL_HANDLE };

VkFence fences[maxFramesInFlight];
VkSemaphore presentSemaphores[maxFramesInFlight];
VkSemaphore * renderSemaphores{ nullptr };

VkCommandPool commandPool{ VK_NULL_HANDLE };
VkCommandBuffer commandBuffers[maxFramesInFlight];

VkPipeline pipeline{ VK_NULL_HANDLE };
VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };

VkImage textureImage{ VK_NULL_HANDLE };
VkImageView textureImageView{ VK_NULL_HANDLE };
VkSampler textureSampler{ VK_NULL_HANDLE };

VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };
VkDescriptorSetLayout textureDescriptorSetLayout{ VK_NULL_HANDLE };
VkDescriptorSet textureDescriptorSet{ VK_NULL_HANDLE };

XMINT2 windowSize{};

struct ShaderData {
  XMFLOAT4X4 projection;
  XMFLOAT4X4 view;
  XMFLOAT4X4 model;
  //XMFLOAT4X4 model[3];
  XMFLOAT4 lightPosition{ 0.0f, -10.0f, 10.0f, 0.0f };
  uint32_t selected{ 1 };
} shaderData{};

struct ShaderDataBuffer {
  VkBuffer buffer{ VK_NULL_HANDLE };
  VkDeviceAddress deviceAddress{};
  VkDeviceMemory memory;
  void * mappedData;
};

ShaderDataBuffer shaderDataBuffers[maxFramesInFlight];

void print_memoryPropertyFlags(VkMemoryPropertyFlags propertyFlags)
{
  int index = 0;
  while (propertyFlags) {
    if (propertyFlags & 1) {
      if (index != 0)
        printf("|");
      printf(string_VkMemoryPropertyFlagBits((VkMemoryPropertyFlagBits)(1u << index)));
    }
    propertyFlags >>= 1;
    index += 1;
  };
  printf("\n");
}

uint32_t findMemoryTypeIndex(VkPhysicalDeviceMemoryProperties const * memoryProperties, uint32_t memoryTypeBits, VkMemoryPropertyFlags propertyFlags)
{
  for (uint32_t i = 0; i < memoryProperties->memoryTypeCount; i++) {
    if (!(memoryTypeBits & (1u << i)))
      continue;

    if (memoryProperties->memoryTypes[i].propertyFlags == propertyFlags) {
      return i;
    }
  }
  ASSERT(false, "no memory type index matching memoryTypeBits and propertyFlags");
  UNREACHABLE();
}

XMMATRIX currentProjection()
{
  float fov_angle_y = XMConvertToRadians(45 * 1.0);
  float aspect_ratio = (float)windowSize.x / (float)windowSize.y;
  float near_z = 0.1;
  float far_z = 100.0;
  XMMATRIX projection = XMMatrixPerspectiveFovRH(fov_angle_y, aspect_ratio, near_z, far_z);
  return projection;
}

XMMATRIX currentView()
{
  XMVECTOR eye = XMVectorSet(0, -3, 0, 0);
  XMVECTOR at = XMVectorSet(0, 0, 0, 0);
  XMVECTOR up = XMVectorSet(0, 0, 1, 0);
  XMMATRIX view = XMMatrixLookAtRH(eye, at, up);
  return view;
}

float theta = 0;

XMMATRIX currentModel()
{
  theta += 0.01;
  return XMMatrixTranslation(0, 0, -0.5) * XMMatrixRotationX(theta);
}

void recreateSwapchain(VkSurfaceFormatKHR surfaceFormat, VkFormat depthFormat, VkPhysicalDeviceMemoryProperties2 const & memoryProperties, VkSurfaceCapabilitiesKHR const & surfaceCapabilities)
{
  //////////////////////////////////////////////////////////////////////
  // swapchain and images
  //////////////////////////////////////////////////////////////////////

  VkExtent2D imageExtent {
    .width = surfaceCapabilities.currentExtent.width,
    .height = surfaceCapabilities.currentExtent.height,
  };
  VkFormat imageFormat{ surfaceFormat.format };
  VkColorSpaceKHR imageColorSpace{ surfaceFormat.colorSpace };

  VkSwapchainCreateInfoKHR swapchainCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    .surface = surface,
    .minImageCount = surfaceCapabilities.minImageCount,
    .imageFormat = imageFormat,
    .imageColorSpace = imageColorSpace,
    .imageExtent = imageExtent,
    .imageArrayLayers = 1,
    .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
    .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
    .presentMode = VK_PRESENT_MODE_FIFO_KHR
  };
  if (swapchain != VK_NULL_HANDLE) {
    swapchainCreateInfo.oldSwapchain = swapchain;
  }
  VK_CHECK(vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &swapchain));

  if (swapchainImages != nullptr) {
    free(swapchainImages);
  }
  if (swapchainImageViews != nullptr) {
    for (uint32_t i = 0; i < swapchainImageCount; i++) {
      vkDestroyImageView(device, swapchainImageViews[i], nullptr);
    }
    free(swapchainImageViews);
  }

  VK_CHECK(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, nullptr));
  swapchainImages = NewM<VkImage>(swapchainImageCount);
  VK_CHECK(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages));
  swapchainImageViews = NewM<VkImageView>(swapchainImageCount);
  for (uint32_t i = 0; i < swapchainImageCount; i++) {
    VkImageViewCreateInfo imageViewCreateInfo{
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .image = swapchainImages[i],
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = imageFormat,
      .subresourceRange{
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .levelCount = 1,
        .layerCount = 1
      }
    };
    VK_CHECK(vkCreateImageView(device, &imageViewCreateInfo, nullptr, &swapchainImageViews[i]));
  }

  if (swapchainCreateInfo.oldSwapchain != nullptr) {
    vkDestroySwapchainKHR(device, swapchainCreateInfo.oldSwapchain, nullptr);
  }

  //////////////////////////////////////////////////////////////////////
  // depth
  //////////////////////////////////////////////////////////////////////

  if (depthImage != VK_NULL_HANDLE) {
    vkDestroyImage(device, depthImage, nullptr);
  }
  if (depthImageMemory != VK_NULL_HANDLE) {
    vkFreeMemory(device, depthImageMemory, nullptr);
  }
  if (depthImageView != VK_NULL_HANDLE) {
    vkDestroyImageView(device, depthImageView, nullptr);
  }

  VkImageCreateInfo depthImageCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = depthFormat,
    .extent{
      .width = imageExtent.width,
      .height = imageExtent.height,
      .depth = 1,
    },
    .mipLevels = 1,
    .arrayLayers = 1,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .tiling = VK_IMAGE_TILING_OPTIMAL,
    .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
  };
  VK_CHECK(vkCreateImage(device, &depthImageCreateInfo, nullptr, &depthImage));

  VkMemoryRequirements depthImageMemoryRequirements;
  vkGetImageMemoryRequirements(device, depthImage, &depthImageMemoryRequirements);
  VkMemoryPropertyFlags depthImageMemoryPropertyFlags{
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
  };
  uint32_t depthImageMemoryTypeIndex = findMemoryTypeIndex(&memoryProperties.memoryProperties, depthImageMemoryRequirements.memoryTypeBits, depthImageMemoryPropertyFlags);
  VkMemoryAllocateInfo depthImageAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .allocationSize = depthImageMemoryRequirements.size,
    .memoryTypeIndex = depthImageMemoryTypeIndex,
  };

  VK_CHECK(vkAllocateMemory(device, &depthImageAllocateInfo, nullptr, &depthImageMemory));
  VK_CHECK(vkBindImageMemory(device, depthImage, depthImageMemory, 0));

  VkImageViewCreateInfo depthViewCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = depthImage,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = depthFormat,
    .subresourceRange{
      .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
      .levelCount = 1,
      .layerCount = 1
    }
  };
  VK_CHECK(vkCreateImageView(device, &depthViewCreateInfo, nullptr, &depthImageView));
}

int main()
{
  SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));
  SDL_CHECK(SDL_Vulkan_LoadLibrary(NULL));
  volkInitialize();

  VkApplicationInfo appInfo{
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "Vulkan",
    .apiVersion = VK_API_VERSION_1_3
  };

  uint32_t instanceExtensionsCount{ 0 };
  char const * const * instanceExtensions{ SDL_Vulkan_GetInstanceExtensions(&instanceExtensionsCount) };

  VkInstanceCreateInfo instanceCreateInfo{
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &appInfo,
    .enabledExtensionCount = instanceExtensionsCount,
    .ppEnabledExtensionNames = instanceExtensions,
  };
  VK_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));

  volkLoadInstance(instance);

  //////////////////////////////////////////////////////////////////////
  // physical device and queue family index
  //////////////////////////////////////////////////////////////////////

  uint32_t physicalDeviceCount{ 0 };
  VK_CHECK(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr));
  VkPhysicalDevice * physicalDevices = NewM<VkPhysicalDevice>(physicalDeviceCount);
  VK_CHECK(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices));

  uint32_t physicalDeviceIndex{ 0 };
  printf("physicalDeviceCount %d\n", physicalDeviceCount);
  for (uint32_t i = 0; i < physicalDeviceCount; i++) {
    VkPhysicalDeviceProperties2 properties{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
    vkGetPhysicalDeviceProperties2(physicalDevices[i], &properties);
    printf("devices[%d] name: %s%s\n", i, properties.properties.deviceName, (i == physicalDeviceIndex) ? " [selected]" : "");
    if (i == physicalDeviceIndex) {
      printf("limits:\n");
      printf("  maxImageDimension1D %u\n", properties.properties.limits.maxImageDimension1D);
      printf("  maxImageDimension2D %u\n", properties.properties.limits.maxImageDimension2D);
      printf("  maxMemoryAllocationCount %u\n", properties.properties.limits.maxMemoryAllocationCount);
      printf("  maxSamplerAllocationCount %u\n", properties.properties.limits.maxSamplerAllocationCount);
    }
  }
  VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
  free(physicalDevices);

  uint32_t queueFamilyCount{ 0 };
  vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, &queueFamilyCount, nullptr);
  VkQueueFamilyProperties2 * queueFamilyProperties = NewM<VkQueueFamilyProperties2>(queueFamilyCount);
  for (uint32_t i = 0; i < queueFamilyCount; i++) {
    queueFamilyProperties[i].sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
    queueFamilyProperties[i].pNext = nullptr;
  }
  vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, &queueFamilyCount, queueFamilyProperties);
  uint32_t queueFamilyIndex{ ~0u };
  for (uint32_t i = 0; i < queueFamilyCount; i++) {
    VkQueueFlags queueFlags = queueFamilyProperties[i].queueFamilyProperties.queueFlags;
    if ((queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFlags & VK_QUEUE_COMPUTE_BIT)) {
      queueFamilyIndex = i;
      break;
    }
  }
  ASSERT(queueFamilyIndex != ~0u, "no queue with VK_QUEUE_GRAPHICS_BIT && VK_QUEUE_COMPUTE_BIT");
  free(queueFamilyProperties);

  SDL_CHECK(SDL_Vulkan_GetPresentationSupport(instance, physicalDevice, queueFamilyIndex));

  //////////////////////////////////////////////////////////////////////
  // memory
  //////////////////////////////////////////////////////////////////////

  VkPhysicalDeviceMemoryProperties2 memoryProperties{
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2,
    .pNext = nullptr
  };
  vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &memoryProperties);
  /*
  for (uint32_t i = 0; i < memoryProperties.memoryProperties.memoryTypeCount; i++) {
    printf("memoryTypes[%u].propertyFlags: ", i);
    print_memoryPropertyFlags(memoryProperties.memoryProperties.memoryTypes[i].propertyFlags);
    printf("memoryTypes[%u].heapIndex: %u\n", i, memoryProperties.memoryProperties.memoryTypes[i].heapIndex);
  }
  for (uint32_t i = 0; i < memoryProperties.memoryProperties.memoryHeapCount; i++) {
    printf("memoryHeaps[%u].size %lu\n", i, memoryProperties.memoryProperties.memoryHeaps[i].size);
    printf("memoryHeaps[%u].flags %08x\n", i, memoryProperties.memoryProperties.memoryHeaps[i].flags);
  }
  */

  //////////////////////////////////////////////////////////////////////
  // device and queue
  //////////////////////////////////////////////////////////////////////

  const float queuePriorities{ 1.0f };
  VkDeviceQueueCreateInfo queueCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .queueFamilyIndex = queueFamilyIndex,
    .queueCount = 1,
    .pQueuePriorities = &queuePriorities
  };
  VkPhysicalDeviceVulkan12Features enabledVulkan12Features{
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
    .descriptorIndexing = true,
    .shaderSampledImageArrayNonUniformIndexing = true,
    .descriptorBindingVariableDescriptorCount = true,
    .runtimeDescriptorArray = true,
    .bufferDeviceAddress = true
  };
  VkPhysicalDeviceVulkan13Features enabledVulkan13Features{
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
    .pNext = &enabledVulkan12Features,
    .synchronization2 = true,
    .dynamicRendering = true,
  };
  VkPhysicalDeviceFeatures enabledFeatures{
    .samplerAnisotropy = VK_TRUE
  };
  constexpr uint32_t enabledExtensionCount = 1;
  char const * enabledExtensionNames[enabledExtensionCount]{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
  VkDeviceCreateInfo deviceCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext = &enabledVulkan13Features,
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &queueCreateInfo,
    .enabledExtensionCount = enabledExtensionCount,
    .ppEnabledExtensionNames = enabledExtensionNames,
    .pEnabledFeatures = &enabledFeatures
  };
  VK_CHECK(vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device));
  vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);

  //////////////////////////////////////////////////////////////////////
  // window and surface
  //////////////////////////////////////////////////////////////////////

  SDL_Window * window = SDL_CreateWindow("Vulkan", 1024, 1024, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
  SDL_CHECK_NONNULL(window);
  SDL_CHECK(SDL_Vulkan_CreateSurface(window, instance, nullptr, &surface));
  SDL_CHECK(SDL_GetWindowSize(window, &windowSize.x, &windowSize.y));
  VkSurfaceCapabilitiesKHR surfaceCapabilities{};
  VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities));
  printf("surfaceCapabilities currentExtent %d %d\n", surfaceCapabilities.currentExtent.width, surfaceCapabilities.currentExtent.height);

  // surface format

  uint32_t surfaceFormatCount{ 0 };
  VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, nullptr));
  VkSurfaceFormatKHR * surfaceFormats = NewM<VkSurfaceFormatKHR>(surfaceFormatCount);
  VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, surfaceFormats));
  uint32_t surfaceFormatIndex{ 0 };
  printf("surfaceFormatCount %d\n", surfaceFormatCount);
  for (uint32_t i = 0; i < surfaceFormatCount; i++) {
    printf("surfaceFormat[%d] %s %s%s\n", i, string_VkFormat(surfaceFormats[i].format), string_VkColorSpaceKHR(surfaceFormats[i].colorSpace), (i == surfaceFormatIndex) ? " [selected]" : "");
  }
  VkSurfaceFormatKHR surfaceFormat = surfaceFormats[surfaceFormatIndex];
  free(surfaceFormats);

  // depth format

  VkFormat depthFormat{ VK_FORMAT_UNDEFINED };
  constexpr uint32_t depthFormatCount = 2;
  VkFormat depthFormatList[depthFormatCount]{ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
  for (uint32_t i = 0; i < depthFormatCount; i++) {
    VkFormatProperties2 formatProperties{ .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 };
    vkGetPhysicalDeviceFormatProperties2(physicalDevice, depthFormatList[i], &formatProperties);
    if (formatProperties.formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
      depthFormat = depthFormatList[i];
      break;
    }
  }
  ASSERT(depthFormat != VK_FORMAT_UNDEFINED, "no depth format with VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT");
  printf("depthFormat: %s\n", string_VkFormat(depthFormat));

  recreateSwapchain(surfaceFormat, depthFormat, memoryProperties, surfaceCapabilities);

  //////////////////////////////////////////////////////////////////////
  // mesh
  //////////////////////////////////////////////////////////////////////

  VkDeviceSize vtxBufferSize{ vtx_size };
  VkDeviceSize idxBufferSize{ idx_size };
  VkBufferCreateInfo vertexIndexBufferCreateInfo{
    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .size = vtxBufferSize + idxBufferSize,
    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE
  };
  VK_CHECK(vkCreateBuffer(device, &vertexIndexBufferCreateInfo, nullptr, &vertexIndexBuffer));

  VkMemoryRequirements vertexIndexBufferMemoryRequirements;
  vkGetBufferMemoryRequirements(device, vertexIndexBuffer, &vertexIndexBufferMemoryRequirements);
  VkMemoryPropertyFlags vertexIndexBufferMemoryPropertyFlags{
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
  };
  uint32_t vertexIndexBufferMemoryTypeIndex = findMemoryTypeIndex(&memoryProperties.memoryProperties, vertexIndexBufferMemoryRequirements.memoryTypeBits, vertexIndexBufferMemoryPropertyFlags);
  VkMemoryAllocateInfo vertexIndexBufferAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .allocationSize = vertexIndexBufferMemoryRequirements.size,
    .memoryTypeIndex = vertexIndexBufferMemoryTypeIndex,
  };
  VkDeviceMemory vertexIndexBufferMemory;
  VK_CHECK(vkAllocateMemory(device, &vertexIndexBufferAllocateInfo, nullptr, &vertexIndexBufferMemory));
  VK_CHECK(vkBindBufferMemory(device, vertexIndexBuffer, vertexIndexBufferMemory, 0));

  void * vertexIndexMappedData;
  VK_CHECK(vkMapMemory(device, vertexIndexBufferMemory, 0, vertexIndexBufferCreateInfo.size, 0, &vertexIndexMappedData));
  memcpy((void *)(((ptrdiff_t)vertexIndexMappedData) + 0), vtx_start, vtx_size);
  memcpy((void *)(((ptrdiff_t)vertexIndexMappedData) + vtx_size), idx_start, idx_size);
  vkUnmapMemory(device, vertexIndexBufferMemory);

  //////////////////////////////////////////////////////////////////////
  // shader buffers
  //////////////////////////////////////////////////////////////////////

  for (uint32_t i = 0; i < maxFramesInFlight; i++) {
    VkBufferCreateInfo shaderBufferCreateInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = (sizeof (ShaderData)),
      .usage = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    VK_CHECK(vkCreateBuffer(device, &shaderBufferCreateInfo, nullptr, &shaderDataBuffers[i].buffer));

    VkMemoryRequirements shaderBufferMemoryRequirements;
    vkGetBufferMemoryRequirements(device, shaderDataBuffers[i].buffer, &shaderBufferMemoryRequirements);

    VkMemoryPropertyFlags shaderBufferMemoryPropertyFlags{
      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    };
    uint32_t shaderBufferMemoryTypeIndex = findMemoryTypeIndex(&memoryProperties.memoryProperties, shaderBufferMemoryRequirements.memoryTypeBits, shaderBufferMemoryPropertyFlags);
    VkMemoryAllocateFlagsInfo shaderBufferAllocateFlagsInfo{
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
      .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    VkMemoryAllocateInfo shaderBufferAllocateInfo{
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .pNext = &shaderBufferAllocateFlagsInfo,
      .allocationSize = shaderBufferMemoryRequirements.size,
      .memoryTypeIndex = shaderBufferMemoryTypeIndex,
    };
    VkDeviceMemory shaderBufferMemory;
    VK_CHECK(vkAllocateMemory(device, &shaderBufferAllocateInfo, nullptr, &shaderBufferMemory));
    VK_CHECK(vkBindBufferMemory(device, shaderDataBuffers[i].buffer, shaderBufferMemory, 0));

    VkBufferDeviceAddressInfo shaderBufferDeviceAddressInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
      .buffer = shaderDataBuffers[i].buffer
    };
    shaderDataBuffers[i].deviceAddress = vkGetBufferDeviceAddress(device, &shaderBufferDeviceAddressInfo);
    void * mappedData;
    VK_CHECK(vkMapMemory(device, shaderBufferMemory, 0, (sizeof (ShaderData)), 0, &mappedData));
    shaderDataBuffers[i].memory = shaderBufferMemory;
    shaderDataBuffers[i].mappedData = mappedData;
  }

  //////////////////////////////////////////////////////////////////////
  // synchronization objects
  //////////////////////////////////////////////////////////////////////

  VkSemaphoreCreateInfo semaphoreCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
  };
  VkFenceCreateInfo fenceCreateInfo{
    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
    .flags = VK_FENCE_CREATE_SIGNALED_BIT
  };
  for (uint32_t i = 0; i < maxFramesInFlight; i++) {
    VK_CHECK(vkCreateFence(device, &fenceCreateInfo, nullptr, &fences[i]));
    VK_CHECK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &presentSemaphores[i]));
  }
  renderSemaphores = NewM<VkSemaphore>(swapchainImageCount);
  for (uint32_t i = 0; i < swapchainImageCount; i++) {
    VK_CHECK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &renderSemaphores[i]));
  }

  //////////////////////////////////////////////////////////////////////
  // command
  //////////////////////////////////////////////////////////////////////

  VkCommandPoolCreateInfo commandPoolCreateInfo{
    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    .queueFamilyIndex = queueFamilyIndex
  };
  VK_CHECK(vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &commandPool));

  VkCommandBufferAllocateInfo commandBufferAllocateCreateInfo{
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .commandPool = commandPool,
    .commandBufferCount = maxFramesInFlight
  };
  VK_CHECK(vkAllocateCommandBuffers(device, &commandBufferAllocateCreateInfo, commandBuffers));

  //////////////////////////////////////////////////////////////////////
  // texture
  //////////////////////////////////////////////////////////////////////

  VkFormat textureFormat{ VK_FORMAT_B8G8R8A8_SRGB };

  VkImageCreateInfo textureImageCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = textureFormat,
    .extent = {.width = 858, .height = 858, .depth = 1 },
    .mipLevels = 1,
    .arrayLayers = 1,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .tiling = VK_IMAGE_TILING_OPTIMAL,
    .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
  };
  VK_CHECK(vkCreateImage(device, &textureImageCreateInfo, nullptr, &textureImage));

  VkMemoryRequirements textureImageMemoryRequirements;
  vkGetImageMemoryRequirements(device, textureImage, &textureImageMemoryRequirements);
  VkMemoryPropertyFlags textureImageMemoryPropertyFlags{
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
  };
  uint32_t textureImageMemoryTypeIndex = findMemoryTypeIndex(&memoryProperties.memoryProperties, textureImageMemoryRequirements.memoryTypeBits, textureImageMemoryPropertyFlags);

  VkMemoryAllocateInfo textureImageAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .allocationSize = textureImageMemoryRequirements.size,
    .memoryTypeIndex = textureImageMemoryTypeIndex,
  };

  VkDeviceMemory textureImageMemory;
  VK_CHECK(vkAllocateMemory(device, &textureImageAllocateInfo, nullptr, &textureImageMemory));
  VK_CHECK(vkBindImageMemory(device, textureImage, textureImageMemory, 0));

  VkImageViewCreateInfo textureViewCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = textureImage,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = textureFormat,
    .subresourceRange{
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .levelCount = 1,
      .layerCount = 1
    }
  };
  VK_CHECK(vkCreateImageView(device, &textureViewCreateInfo, nullptr, &textureImageView));

  // texture transfer: source buffer

  VkBuffer textureSourceBuffer{};
  VkBufferCreateInfo textureSourceBufferCreateInfo{
    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .size = sprite_size,
    .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT
  };
  VK_CHECK(vkCreateBuffer(device, &textureSourceBufferCreateInfo, nullptr, &textureSourceBuffer));
  VkMemoryRequirements textureSourceBufferMemoryRequirements;
  vkGetBufferMemoryRequirements(device, textureSourceBuffer, &textureSourceBufferMemoryRequirements);
  VkMemoryPropertyFlags textureSourceBufferMemoryPropertyFlags{
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
  };
  uint32_t textureSourceBufferMemoryTypeIndex = findMemoryTypeIndex(&memoryProperties.memoryProperties, textureSourceBufferMemoryRequirements.memoryTypeBits, textureSourceBufferMemoryPropertyFlags);
  VkMemoryAllocateInfo textureSourceBufferAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .allocationSize = textureSourceBufferMemoryRequirements.size,
    .memoryTypeIndex = textureSourceBufferMemoryTypeIndex,
  };
  VkDeviceMemory textureSourceBufferMemory;
  VK_CHECK(vkAllocateMemory(device, &textureSourceBufferAllocateInfo, nullptr, &textureSourceBufferMemory));
  VK_CHECK(vkBindBufferMemory(device, textureSourceBuffer, textureSourceBufferMemory, 0));

  void * textureSourceMappedData;
  VK_CHECK(vkMapMemory(device, textureSourceBufferMemory, 0, textureSourceBufferCreateInfo.size, 0, &textureSourceMappedData));
  memcpy((void *)(((ptrdiff_t)textureSourceMappedData) + 0), sprite_start, sprite_size);
  vkUnmapMemory(device, textureSourceBufferMemory);

  VkFenceCreateInfo textureFenceCreateInfo{
    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
  };
  VkFence textureFence{};
  VK_CHECK(vkCreateFence(device, &textureFenceCreateInfo, nullptr, &textureFence));

  // texture transfer: command buffer

  VkCommandBuffer textureCommandBuffer{};
  VkCommandBufferAllocateInfo textureCommandBufferAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .commandPool = commandPool,
    .commandBufferCount = 1
  };
  VK_CHECK(vkAllocateCommandBuffers(device, &textureCommandBufferAllocateInfo, &textureCommandBuffer));

  VkCommandBufferBeginInfo textureCommandBufferBeginInfo{
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
  };
  VK_CHECK(vkBeginCommandBuffer(textureCommandBuffer, &textureCommandBufferBeginInfo));
  VkImageMemoryBarrier2 barrierTextureImage{
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
    .srcStageMask = VK_PIPELINE_STAGE_2_NONE,
    .srcAccessMask = VK_ACCESS_2_NONE,
    .dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
    .dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
    .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    .image = textureImage,
    .subresourceRange = {
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .levelCount = 1,
      .layerCount = 1
    }
  };
  VkDependencyInfo barrierTextureImageDependencyInfo{
    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
    .imageMemoryBarrierCount = 1,
    .pImageMemoryBarriers = &barrierTextureImage
  };
  vkCmdPipelineBarrier2(textureCommandBuffer, &barrierTextureImageDependencyInfo);
  VkBufferImageCopy copyRegion{
    .bufferOffset = 0,
    .imageSubresource{
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .mipLevel = 0,
      .layerCount = 1
    },
    .imageExtent{ .width = 858, .height = 858, .depth = 1 },
  };
  vkCmdCopyBufferToImage(textureCommandBuffer, textureSourceBuffer, textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

  VkImageMemoryBarrier2 barrierTextureRead{
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
    .srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT,
    .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
    .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
    .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
    .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    .newLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL,
    .image = textureImage,
    .subresourceRange = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .levelCount = 1, .layerCount = 1 }
  };
  VkDependencyInfo barrierTextureReadDependencyInfo{
    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
    .imageMemoryBarrierCount = 1,
    .pImageMemoryBarriers = &barrierTextureRead
  };
  vkCmdPipelineBarrier2(textureCommandBuffer, &barrierTextureReadDependencyInfo);

  VK_CHECK(vkEndCommandBuffer(textureCommandBuffer));

  VkSubmitInfo textureSubmitInfo{
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .commandBufferCount = 1,
    .pCommandBuffers = &textureCommandBuffer
  };
  VK_CHECK(vkQueueSubmit(queue, 1, &textureSubmitInfo, textureFence));
  VK_CHECK(vkWaitForFences(device, 1, &textureFence, VK_TRUE, UINT64_MAX));

  // texture sampler

  VkSamplerCreateInfo samplerCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
    .magFilter = VK_FILTER_LINEAR,
    .minFilter = VK_FILTER_LINEAR,
    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
    .anisotropyEnable = VK_FALSE,
    .maxLod = 1,
  };
  VK_CHECK(vkCreateSampler(device, &samplerCreateInfo, nullptr, &textureSampler));

  VkDescriptorImageInfo textureDescriptorImageInfo = {
    .sampler = textureSampler,
    .imageView = textureImageView,
    .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
  };

  //////////////////////////////////////////////////////////////////////
  // descriptors
  //////////////////////////////////////////////////////////////////////

  VkDescriptorBindingFlags descriptorBindingFlags{ VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT };
  VkDescriptorSetLayoutBindingFlagsCreateInfo descriptorSetLayoutBindingFlagsCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
    .bindingCount = 1,
    .pBindingFlags = &descriptorBindingFlags
  };
  VkDescriptorSetLayoutBinding textureDescriptorSetLayoutBinding{
    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    .descriptorCount = 1,
    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
  };
  VkDescriptorSetLayoutCreateInfo textureDescriptorSetLayoutCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
    .pNext = &descriptorSetLayoutBindingFlagsCreateInfo,
    .bindingCount = 1,
    .pBindings = &textureDescriptorSetLayoutBinding
  };
  VK_CHECK(vkCreateDescriptorSetLayout(device, &textureDescriptorSetLayoutCreateInfo, nullptr, &textureDescriptorSetLayout));

  // pool

  VkDescriptorPoolSize poolSize{
    .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    .descriptorCount = 1,
  };
  VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
    .maxSets = 1,
    .poolSizeCount = 1,
    .pPoolSizes = &poolSize
  };
  VK_CHECK(vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

  //

  uint32_t variableDescriptorCount{ 1 };
  VkDescriptorSetVariableDescriptorCountAllocateInfo descriptorSetVariableDescriptorCountAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT,
    .descriptorSetCount = 1,
    .pDescriptorCounts = &variableDescriptorCount
  };
  VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    .pNext = &descriptorSetVariableDescriptorCountAllocateInfo,
    .descriptorPool = descriptorPool,
    .descriptorSetCount = 1,
    .pSetLayouts = &textureDescriptorSetLayout
  };
  VK_CHECK(vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &textureDescriptorSet));

  //

  VkWriteDescriptorSet writeDescriptorSet{
    .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
    .dstSet = textureDescriptorSet,
    .dstBinding = 0,
    .descriptorCount = 1,
    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    .pImageInfo = &textureDescriptorImageInfo
  };
  vkUpdateDescriptorSets(device, 1, &writeDescriptorSet, 0, nullptr);

  //////////////////////////////////////////////////////////////////////
  // shaders
  //////////////////////////////////////////////////////////////////////

  VkShaderModuleCreateInfo vertexShaderModuleCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .codeSize = vs_size,
    .pCode = (uint32_t *)vs_start
  };
  VkShaderModule vertexShaderModule{};
  VK_CHECK(vkCreateShaderModule(device, &vertexShaderModuleCreateInfo, nullptr, &vertexShaderModule));

  VkShaderModuleCreateInfo pixelShaderModuleCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .codeSize = ps_size,
    .pCode = (uint32_t *)ps_start
  };
  VkShaderModule pixelShaderModule{};
  VK_CHECK(vkCreateShaderModule(device, &pixelShaderModuleCreateInfo, nullptr, &pixelShaderModule));

  //////////////////////////////////////////////////////////////////////
  // pipeline
  //////////////////////////////////////////////////////////////////////

  VkPushConstantRange pushConstantRange{
    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
    .size = (sizeof (VkDeviceAddress))
  };
  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    .setLayoutCount = 1,
    .pSetLayouts = &textureDescriptorSetLayout,
    .pushConstantRangeCount = 1,
    .pPushConstantRanges = &pushConstantRange
  };
  VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

  VkVertexInputBindingDescription vertexBindingDescriptions[1]{
    {
      .binding = 0,
      .stride = (3 * (sizeof (float)) * 3),
      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    }
  };
  VkVertexInputAttributeDescription vertexAttributeDescriptions[3]{
    { .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = 3 * 4 * 0 },
    { .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = 3 * 4 * 1 },
    { .location = 2, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = 3 * 4 * 2 },
  };
  VkPipelineVertexInputStateCreateInfo vertexInputState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount = 1,
    .pVertexBindingDescriptions = vertexBindingDescriptions,
    .vertexAttributeDescriptionCount = 3,
    .pVertexAttributeDescriptions = vertexAttributeDescriptions,
  };

  VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
    .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST
  };

  VkPipelineShaderStageCreateInfo shaderStages[2]{
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_VERTEX_BIT,
      .module = vertexShaderModule, .pName = "VSMain"
    },
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = pixelShaderModule, .pName = "PSMain"
    }
  };

  VkPipelineViewportStateCreateInfo viewportState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    .viewportCount = 1,
    .scissorCount = 1
  };

  VkDynamicState dynamicStates[2]{
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };
  VkPipelineDynamicStateCreateInfo dynamicState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
    .dynamicStateCount = 2,
    .pDynamicStates = dynamicStates
  };

  VkPipelineDepthStencilStateCreateInfo depthStencilState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable = VK_TRUE,
    .depthWriteEnable = VK_TRUE,
    .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL
  };

  VkPipelineRenderingCreateInfo renderingCreateInfo{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
    .colorAttachmentCount = 1,
    .pColorAttachmentFormats = &surfaceFormat.format,
    .depthAttachmentFormat = depthFormat
  };

  VkPipelineColorBlendAttachmentState blendAttachment{
    .colorWriteMask = 0xF
  };
  VkPipelineColorBlendStateCreateInfo colorBlendState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .attachmentCount = 1,
    .pAttachments = &blendAttachment
  };
  VkPipelineRasterizationStateCreateInfo rasterizationState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .lineWidth = 1.0f
  };
  VkPipelineMultisampleStateCreateInfo multisampleState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
  };

  VkGraphicsPipelineCreateInfo pipelineCreateInfo{
    .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
    .pNext = &renderingCreateInfo,
    .stageCount = 2,
    .pStages = shaderStages,
    .pVertexInputState = &vertexInputState,
    .pInputAssemblyState = &inputAssemblyState,
    .pViewportState = &viewportState,
    .pRasterizationState = &rasterizationState,
    .pMultisampleState = &multisampleState,
    .pDepthStencilState = &depthStencilState,
    .pColorBlendState = &colorBlendState,
    .pDynamicState = &dynamicState,
    .layout = pipelineLayout
  };
  VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &pipeline));

  //////////////////////////////////////////////////////////////////////
  // loop
  //////////////////////////////////////////////////////////////////////

  bool updateSwapchain{ false };
  uint32_t frameIndex{ 0 };
  uint32_t imageIndex{ 0 };
  bool quit{ false };
  while (quit == false) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
      }
      if (event.type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_CHECK(SDL_GetWindowSize(window, &windowSize.x, &windowSize.y));
      }
    }

    // wait for fence
    VK_CHECK(vkWaitForFences(device, 1, &fences[frameIndex], true, UINT64_MAX));
    VK_CHECK(vkResetFences(device, 1, &fences[frameIndex]));

    // acquire next image
    VK_CHECK_SWAPCHAIN(vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, presentSemaphores[frameIndex], VK_NULL_HANDLE, &imageIndex));

    // shader data
    XMStoreFloat4x4(&shaderData.projection, currentProjection());
    XMStoreFloat4x4(&shaderData.view, currentView());
    XMStoreFloat4x4(&shaderData.model, currentModel());
    memcpy(shaderDataBuffers[frameIndex].mappedData, &shaderData, (sizeof (ShaderData)));

    // command buffer
    VkCommandBuffer& commandBuffer = commandBuffers[frameIndex];
    VK_CHECK(vkResetCommandBuffer(commandBuffer, 0));
    VkCommandBufferBeginInfo commandBufferBeginInfo {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };
    VK_CHECK(vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo));

    VkImageMemoryBarrier2 outputBarriers[2]{
      VkImageMemoryBarrier2{
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .newLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
        .image = swapchainImages[imageIndex],
        .subresourceRange{
          .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
          .levelCount = 1,
          .layerCount = 1
        }
      },
      VkImageMemoryBarrier2{
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
        .srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT,
        .dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .newLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
        .image = depthImage,
        .subresourceRange{
          .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
          .levelCount = 1,
          .layerCount = 1
        }
      }
    };
    VkDependencyInfo barrierDependencyInfo{
      .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
      .imageMemoryBarrierCount = 2,
      .pImageMemoryBarriers = outputBarriers
    };
    vkCmdPipelineBarrier2(commandBuffer, &barrierDependencyInfo);

    VkRenderingAttachmentInfo colorRenderingAttachmentInfo{
      .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
      .imageView = swapchainImageViews[imageIndex],
      .imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .clearValue{ .color{ 0.0f, 0.0f, 0.2f, 1.0f } }
    };
    VkRenderingAttachmentInfo depthRenderingAttachmentInfo{
      .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
      .imageView = depthImageView,
      .imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
      .clearValue{ .depthStencil{ 1.0f, 0 } }
    };

    VkRenderingInfo renderingInfo{
      .sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
      .renderArea{ .extent{ .width = surfaceCapabilities.currentExtent.width, .height = surfaceCapabilities.currentExtent.height } },
      .layerCount = 1,
      .colorAttachmentCount = 1,
      .pColorAttachments = &colorRenderingAttachmentInfo,
      .pDepthAttachment = &depthRenderingAttachmentInfo
    };
    vkCmdBeginRendering(commandBuffer, &renderingInfo);

    VkViewport viewport{
      .width = static_cast<float>(windowSize.x),
      .height = static_cast<float>(windowSize.y),
      .minDepth = 0.0f,
      .maxDepth = 1.0f
    };
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    VkRect2D scissor{ .extent{ .width = (uint32_t)windowSize.x, .height = (uint32_t)windowSize.y } };
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    VkDeviceSize vertexOffset{ 0 };
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &textureDescriptorSet, 0, nullptr);
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexIndexBuffer, &vertexOffset);
    VkDeviceSize indexOffset{ vtxBufferSize };
    vkCmdBindIndexBuffer(commandBuffer, vertexIndexBuffer, indexOffset, VK_INDEX_TYPE_UINT32);
    vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, (sizeof (VkDeviceAddress)), &shaderDataBuffers[frameIndex].deviceAddress);
    VkDeviceSize indexCount{ 9216 };
    vkCmdDrawIndexed(commandBuffer, indexCount, 3, 0, 0, 0);
    vkCmdEndRendering(commandBuffer);

    VkImageMemoryBarrier2 barrierPresent{
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
      .srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
      .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
      .dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
      .dstAccessMask = 0,
      .oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
      .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
      .image = swapchainImages[imageIndex],
      .subresourceRange{ .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .levelCount = 1, .layerCount = 1 }
    };
    VkDependencyInfo barrierPresentDependencyInfo{
      .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
      .imageMemoryBarrierCount = 1,
      .pImageMemoryBarriers = &barrierPresent
    };
    vkCmdPipelineBarrier2(commandBuffer, &barrierPresentDependencyInfo);

    VK_CHECK(vkEndCommandBuffer(commandBuffer));

    // submit to graphics queue
    VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submitInfo{
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &presentSemaphores[frameIndex],
      .pWaitDstStageMask = &waitStages,
      .commandBufferCount = 1,
      .pCommandBuffers = &commandBuffer,
      .signalSemaphoreCount = 1,
      .pSignalSemaphores = &renderSemaphores[imageIndex],
    };
    VK_CHECK(vkQueueSubmit(queue, 1, &submitInfo, fences[frameIndex]));

    frameIndex = (frameIndex + 1) % maxFramesInFlight;

    // present
    VkPresentInfoKHR presentInfo{
      .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &renderSemaphores[imageIndex],
      .swapchainCount = 1,
      .pSwapchains = &swapchain,
      .pImageIndices = &imageIndex
    };
    VK_CHECK_SWAPCHAIN(vkQueuePresentKHR(queue, &presentInfo));

    if (updateSwapchain) {
      //////////////////////////////////////////////////////////////////////
      // recreate swapchain
      //////////////////////////////////////////////////////////////////////
      updateSwapchain = false;
      VK_CHECK(vkDeviceWaitIdle(device));
      VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities));
      recreateSwapchain(surfaceFormat, depthFormat, memoryProperties, surfaceCapabilities);
    }
  }
}
