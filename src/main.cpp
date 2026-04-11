#include <stdio.h>
#include <stdlib.h>

#include "volk/volk.h"
#include "vulkan/vk_enum_string_helper.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
#include "directxmath/directxmath.h"

#include "new.h"
#include "file.h"
#include "dds_validate.h"

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
VkDeviceMemory vertexIndexBufferMemory{ VK_NULL_HANDLE };
VkDeviceSize vertexBufferSize{ 0 };
VkDeviceSize indexBufferSize{ 0 };

VkFence fences[maxFramesInFlight];
VkSemaphore presentSemaphores[maxFramesInFlight];
VkSemaphore * renderSemaphores{ nullptr };

VkCommandPool commandPool{ VK_NULL_HANDLE };
VkCommandBuffer commandBuffers[maxFramesInFlight];

enum {
  MAIN_PIPELINE = 0,
  OUTLINE_PIPELINE = 1,
};

VkPipeline pipelines[2]{ VK_NULL_HANDLE, VK_NULL_HANDLE };
VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };

VkImage textureImage{ VK_NULL_HANDLE };
VkImageView textureImageView{ VK_NULL_HANDLE };
VkDeviceMemory textureImageMemory{ VK_NULL_HANDLE };
VkSampler textureSampler{ VK_NULL_HANDLE };

VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };
VkDescriptorSetLayout uniformBufferDescriptorSetLayout{ VK_NULL_HANDLE };
VkDescriptorSet uniformBufferDescriptorSets[maxFramesInFlight];
VkDescriptorSetLayout textureDescriptorSetLayout{ VK_NULL_HANDLE };
VkDescriptorSet textureDescriptorSet{ VK_NULL_HANDLE };

XMINT2 windowSize{};

struct ShaderData {
  XMFLOAT4X4 transform;
  XMFLOAT4X4 modelView;
  XMFLOAT4 lightPosition;
  uint32_t selected;
};

ShaderData shaderData{};

struct ShaderDataDevice {
  VkDeviceMemory memory;
  VkDeviceAddress stride;
  void * mappedData;
  struct {
    VkBuffer buffer{ VK_NULL_HANDLE };
    VkDeviceAddress deviceAddress{};
  } frame[maxFramesInFlight];
};

ShaderDataDevice shaderDataDevice{};

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

uint32_t findMemoryTypeIndex(VkPhysicalDeviceMemoryProperties const & memoryProperties, uint32_t memoryTypeBits, VkMemoryPropertyFlags propertyFlags)
{
  // find an exact match
  for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
    if (!(memoryTypeBits & (1u << i)))
      continue;

    if (memoryProperties.memoryTypes[i].propertyFlags == propertyFlags) {
      return i;
    }
  }

  // find a partial match
  for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
    if (!(memoryTypeBits & (1u << i)))
      continue;

    if ((memoryProperties.memoryTypes[i].propertyFlags & propertyFlags) == propertyFlags) {
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
  return XMMatrixTranslation(0, 0, 0.0) * XMMatrixRotationX(theta) * XMMatrixRotationZ(XM_PI * 0.5f);
}

void recreateSwapchain(VkSurfaceFormatKHR surfaceFormat, VkFormat depthFormat, VkPhysicalDeviceMemoryProperties const & memoryProperties, VkSurfaceCapabilitiesKHR const & surfaceCapabilities)
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
  if (renderSemaphores != nullptr) {
    for (uint32_t i = 0; i < swapchainImageCount; i++) {
      vkDestroySemaphore(device, renderSemaphores[i], nullptr);
    }
    free(renderSemaphores);
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
  // render semaphores
  //////////////////////////////////////////////////////////////////////

  VkSemaphoreCreateInfo semaphoreCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
  };
  renderSemaphores = NewM<VkSemaphore>(swapchainImageCount);
  for (uint32_t i = 0; i < swapchainImageCount; i++) {
    VK_CHECK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &renderSemaphores[i]));
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
  uint32_t depthImageMemoryTypeIndex = findMemoryTypeIndex(memoryProperties, depthImageMemoryRequirements.memoryTypeBits, depthImageMemoryPropertyFlags);
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
      .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
      .levelCount = 1,
      .layerCount = 1
    }
  };
  VK_CHECK(vkCreateImageView(device, &depthViewCreateInfo, nullptr, &depthImageView));
}

inline static constexpr VkDeviceSize roundAlignment(VkDeviceSize offset, VkDeviceSize alignment)
{
  // must be a power of two
  assert(alignment && ((alignment & (alignment - 1)) == 0));
  return (offset + (alignment - 1)) & (-alignment);
}

VkDeviceSize allocateFromMemoryRequirements(VkPhysicalDeviceMemoryProperties2 const & physicalDeviceMemoryProperties,
                                            VkMemoryRequirements const & memoryRequirements,
                                            VkMemoryPropertyFlags memoryPropertyFlags,
                                            VkMemoryAllocateFlags memoryAllocateFlags,
                                            uint32_t count,
                                            VkDeviceMemory * memory)
{
  uint32_t memoryTypeIndex = findMemoryTypeIndex(physicalDeviceMemoryProperties.memoryProperties,
                                                 memoryRequirements.memoryTypeBits,
                                                 memoryPropertyFlags);

  VkDeviceSize stride = (count == 1) ? memoryRequirements.size : roundAlignment(memoryRequirements.size, memoryRequirements.alignment);

  VkMemoryAllocateFlagsInfo memoryAllocateFlagsInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
    .flags = memoryAllocateFlags,
  };
  VkMemoryAllocateInfo memoryAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext = &memoryAllocateFlagsInfo,
    .allocationSize = stride * count,
    .memoryTypeIndex = memoryTypeIndex,
  };
  VK_CHECK(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, memory));

  return stride;
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
  VkPhysicalDeviceProperties physicalDeviceProperties;
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
      printf("  nonCoherentAtomSize %lu\n", properties.properties.limits.nonCoherentAtomSize);
      printf("  minUniformBufferOffsetAlignment %lu\n", properties.properties.limits.minUniformBufferOffsetAlignment);
      printf("  maxSamplerLodBias %f\n", properties.properties.limits.maxSamplerLodBias);
      printf("  maxSamplerAnisotropy %f\n", properties.properties.limits.maxSamplerAnisotropy);
      physicalDeviceProperties = properties.properties;
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

  VkPhysicalDeviceMemoryProperties2 physicalDeviceMemoryProperties{
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2,
    .pNext = nullptr
  };
  vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &physicalDeviceMemoryProperties);
  if constexpr (true) {
    VkPhysicalDeviceMemoryProperties const & memoryProperties = physicalDeviceMemoryProperties.memoryProperties;
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
      printf("memoryTypes[%u].propertyFlags: ", i);
      print_memoryPropertyFlags(memoryProperties.memoryTypes[i].propertyFlags);
      printf("memoryTypes[%u].heapIndex: %u\n", i, memoryProperties.memoryTypes[i].heapIndex);
    }
    for (uint32_t i = 0; i < memoryProperties.memoryHeapCount; i++) {
      printf("memoryHeaps[%u].size %lu\n", i, memoryProperties.memoryHeaps[i].size);
      printf("memoryHeaps[%u].flags %08x\n", i, memoryProperties.memoryHeaps[i].flags);
    }
  }

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

  recreateSwapchain(surfaceFormat, depthFormat, physicalDeviceMemoryProperties.memoryProperties, surfaceCapabilities);

  //////////////////////////////////////////////////////////////////////
  // mesh
  //////////////////////////////////////////////////////////////////////

  {
    uint32_t vertexSize;
    void const * vertexStart = file::open("checker.vtx", &vertexSize);
    uint32_t indexSize;
    void const * indexStart = file::open("checker.idx", &indexSize);
    vertexBufferSize = vertexSize;
    indexBufferSize = indexSize;

    VkDeviceSize bufferSize{ vertexSize + indexSize };
    VkBufferCreateInfo vertexIndexBufferCreateInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = bufferSize,
      .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };
    VK_CHECK(vkCreateBuffer(device, &vertexIndexBufferCreateInfo, nullptr, &vertexIndexBuffer));

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, vertexIndexBuffer, &memoryRequirements);
    VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
    VkMemoryAllocateFlags memoryAllocateFlags{};

    allocateFromMemoryRequirements(physicalDeviceMemoryProperties,
                                   memoryRequirements,
                                   memoryPropertyFlags,
                                   memoryAllocateFlags,
                                   1,
                                   &vertexIndexBufferMemory);

    VK_CHECK(vkBindBufferMemory(device, vertexIndexBuffer, vertexIndexBufferMemory, 0));

    void * vertexIndexMappedData;
    VK_CHECK(vkMapMemory(device, vertexIndexBufferMemory, 0, vertexIndexBufferCreateInfo.size, 0, &vertexIndexMappedData));
    memcpy((void *)(((ptrdiff_t)vertexIndexMappedData) + 0), vertexStart, vertexSize);
    memcpy((void *)(((ptrdiff_t)vertexIndexMappedData) + vertexSize), indexStart, indexSize);

    VkMappedMemoryRange mappedMemoryRange{
      .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
      .memory = vertexIndexBufferMemory,
      .offset = 0,
      .size = VK_WHOLE_SIZE,
    };
    vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);

    vkUnmapMemory(device, vertexIndexBufferMemory);
  }

  //////////////////////////////////////////////////////////////////////
  // shader buffers
  //////////////////////////////////////////////////////////////////////

  {
    for (uint32_t i = 0; i < maxFramesInFlight; i++) {
      VkBufferCreateInfo bufferCreateInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = (sizeof (ShaderData)),
        .usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      };

      VK_CHECK(vkCreateBuffer(device, &bufferCreateInfo, nullptr, &shaderDataDevice.frame[i].buffer));
    }

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, shaderDataDevice.frame[0].buffer, &memoryRequirements);

    VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT };
    VkMemoryAllocateFlags memoryAllocateFlags{ };
    shaderDataDevice.stride = allocateFromMemoryRequirements(physicalDeviceMemoryProperties,
                                                             memoryRequirements,
                                                             memoryPropertyFlags,
                                                             memoryAllocateFlags,
                                                             maxFramesInFlight,
                                                             &shaderDataDevice.memory);

    VkDeviceSize offset{ 0 };
    VkDeviceSize size{ VK_WHOLE_SIZE };
    VkMemoryMapFlags flags{ 0 };
    VK_CHECK(vkMapMemory(device, shaderDataDevice.memory, offset, size, flags, &shaderDataDevice.mappedData));

    for (uint32_t i = 0; i < maxFramesInFlight; i++) {
      VkDeviceSize offset{ shaderDataDevice.stride * i };

      VK_CHECK(vkBindBufferMemory(device, shaderDataDevice.frame[i].buffer, shaderDataDevice.memory, offset));
    }
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

  uint32_t checkerSize;
  void const * checkerStart = file::open("checker.dds", &checkerSize);
  void * checkerData;
  uint32_t * mipOffsets;
  DDS_FILE const * ddsFile = dds_validate(checkerStart, checkerSize, &mipOffsets, &checkerData);
  uint32_t checkerDataSize = checkerSize - (sizeof (DDS_FILE));

  VkFormat textureFormat{ VK_FORMAT_B8G8R8A8_SRGB };

  VkImageCreateInfo textureImageCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = textureFormat,
    .extent = {
      .width = ddsFile->header.dwWidth,
      .height = ddsFile->header.dwHeight,
      .depth = 1
    },
    .mipLevels = ddsFile->header.dwMipMapCount,
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
  uint32_t textureImageMemoryTypeIndex = findMemoryTypeIndex(physicalDeviceMemoryProperties.memoryProperties, textureImageMemoryRequirements.memoryTypeBits, textureImageMemoryPropertyFlags);

  VkMemoryAllocateInfo textureImageAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .allocationSize = textureImageMemoryRequirements.size,
    .memoryTypeIndex = textureImageMemoryTypeIndex,
  };

  VK_CHECK(vkAllocateMemory(device, &textureImageAllocateInfo, nullptr, &textureImageMemory));
  VK_CHECK(vkBindImageMemory(device, textureImage, textureImageMemory, 0));

  VkImageViewCreateInfo textureViewCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = textureImage,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = textureFormat,
    .subresourceRange{
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .levelCount = ddsFile->header.dwMipMapCount,
      .layerCount = 1
    }
  };
  VK_CHECK(vkCreateImageView(device, &textureViewCreateInfo, nullptr, &textureImageView));

  // texture transfer: source buffer

  VkBuffer textureSourceBuffer{};
  VkBufferCreateInfo textureSourceBufferCreateInfo{
    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .size = checkerDataSize,
    .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT
  };
  VK_CHECK(vkCreateBuffer(device, &textureSourceBufferCreateInfo, nullptr, &textureSourceBuffer));
  VkMemoryRequirements textureSourceBufferMemoryRequirements;
  vkGetBufferMemoryRequirements(device, textureSourceBuffer, &textureSourceBufferMemoryRequirements);
  VkMemoryPropertyFlags textureSourceBufferMemoryPropertyFlags{
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
  };
  uint32_t textureSourceBufferMemoryTypeIndex = findMemoryTypeIndex(physicalDeviceMemoryProperties.memoryProperties, textureSourceBufferMemoryRequirements.memoryTypeBits, textureSourceBufferMemoryPropertyFlags);
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
  memcpy((void *)(((ptrdiff_t)textureSourceMappedData) + 0), checkerData, checkerDataSize);
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
      .levelCount = ddsFile->header.dwMipMapCount,
      .layerCount = 1
    }
  };
  VkDependencyInfo barrierTextureImageDependencyInfo{
    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
    .imageMemoryBarrierCount = 1,
    .pImageMemoryBarriers = &barrierTextureImage
  };
  vkCmdPipelineBarrier2(textureCommandBuffer, &barrierTextureImageDependencyInfo);
  VkBufferImageCopy * copyRegions = NewM<VkBufferImageCopy>(ddsFile->header.dwMipMapCount);
  for (uint32_t level = 0; level < ddsFile->header.dwMipMapCount; level++) {
    copyRegions[level] = {
      .bufferOffset = mipOffsets[level],
      .imageSubresource{
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = level,
        .layerCount = 1
      },
      .imageExtent{
        .width = max(1u, ddsFile->header.dwWidth >> level),
        .height = max(1u, ddsFile->header.dwHeight >> level),
        .depth = 1
      },
    };
  }
  vkCmdCopyBufferToImage(textureCommandBuffer, textureSourceBuffer, textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ddsFile->header.dwMipMapCount, copyRegions);
  free(mipOffsets);
  free(copyRegions);

  VkImageMemoryBarrier2 barrierTextureRead{
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
    .srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT,
    .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
    .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
    .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
    .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    .newLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL,
    .image = textureImage,
    .subresourceRange = { .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .levelCount = ddsFile->header.dwMipMapCount, .layerCount = 1 }
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
  vkDestroyFence(device, textureFence, nullptr);
  vkDestroyBuffer(device, textureSourceBuffer, nullptr);
  vkFreeMemory(device, textureSourceBufferMemory, nullptr);

  // texture sampler

  VkSamplerCreateInfo samplerCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
    .magFilter = VK_FILTER_LINEAR,
    .minFilter = VK_FILTER_LINEAR,
    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .anisotropyEnable = VK_TRUE,
    .maxAnisotropy = 16.0f,
    .maxLod = (float)ddsFile->header.dwMipMapCount,
  };
  VK_CHECK(vkCreateSampler(device, &samplerCreateInfo, nullptr, &textureSampler));

  //////////////////////////////////////////////////////////////////////
  // descriptors
  //////////////////////////////////////////////////////////////////////

  //
  // pool
  //

  VkDescriptorPoolSize descriptorPoolSizes[2]{
    {
      .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .descriptorCount = 1,
    },
    {
      .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .descriptorCount = maxFramesInFlight,
    }
  };
  VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
    .maxSets = 3,
    .poolSizeCount = 2,
    .pPoolSizes = descriptorPoolSizes
  };
  VK_CHECK(vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

  //
  // uniform buffer descriptor set layout/allocation
  //

  VkDescriptorSetLayoutBinding uniformBufferDescriptorSetLayoutBinding{
    .binding = 0,
    .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    .descriptorCount = 1,
    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT
  };

  VkDescriptorSetLayoutCreateInfo uniformBufferDescriptorSetLayoutCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
    .bindingCount = 1,
    .pBindings = &uniformBufferDescriptorSetLayoutBinding
  };
  VK_CHECK(vkCreateDescriptorSetLayout(device, &uniformBufferDescriptorSetLayoutCreateInfo, nullptr, &uniformBufferDescriptorSetLayout));

  VkDescriptorSetLayout uniformBufferDescriptorSetLayouts[maxFramesInFlight];
  for (uint32_t i = 0; i < maxFramesInFlight; i++) {
    uniformBufferDescriptorSetLayouts[i] = uniformBufferDescriptorSetLayout;
  };

  VkDescriptorSetAllocateInfo uniformBufferDescriptorSetAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    .descriptorPool = descriptorPool,
    .descriptorSetCount = maxFramesInFlight,
    .pSetLayouts = uniformBufferDescriptorSetLayouts
  };
  VK_CHECK(vkAllocateDescriptorSets(device, &uniformBufferDescriptorSetAllocateInfo, uniformBufferDescriptorSets));

  //
  // texture descriptor set layout/allocation
  //

  VkDescriptorSetLayoutBinding textureDescriptorSetLayoutBinding{
    .binding = 0,
    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    .descriptorCount = 1,
    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
  };

  VkDescriptorSetLayoutCreateInfo textureDescriptorSetLayoutCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
    .bindingCount = 1,
    .pBindings = &textureDescriptorSetLayoutBinding
  };
  VK_CHECK(vkCreateDescriptorSetLayout(device, &textureDescriptorSetLayoutCreateInfo, nullptr, &textureDescriptorSetLayout));

  VkDescriptorSetAllocateInfo textureDescriptorSetAllocateInfo{
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    .descriptorPool = descriptorPool,
    .descriptorSetCount = 1,
    .pSetLayouts = &textureDescriptorSetLayout
  };
  VK_CHECK(vkAllocateDescriptorSets(device, &textureDescriptorSetAllocateInfo, &textureDescriptorSet));

  //////////////////////////////////////////////////////////////////////
  // descriptor set writes
  //////////////////////////////////////////////////////////////////////

  constexpr int writeDescriptorSetsCount = 1 + maxFramesInFlight;
  VkWriteDescriptorSet writeDescriptorSets[writeDescriptorSetsCount];

  VkDescriptorImageInfo textureDescriptorImageInfo = {
    .sampler = textureSampler,
    .imageView = textureImageView,
    .imageLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL
  };

  writeDescriptorSets[0] = {
    .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
    .dstSet = textureDescriptorSet,
    .dstBinding = 0,
    .descriptorCount = 1,
    .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    .pImageInfo = &textureDescriptorImageInfo
  };

  for (uint32_t i = 0; i < maxFramesInFlight; i++) {
    VkDescriptorBufferInfo descriptorBufferInfo {
      .buffer = shaderDataDevice.frame[i].buffer,
      .offset = 0,
      .range = VK_WHOLE_SIZE,
    };

    writeDescriptorSets[1 + i] = {
      .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .dstSet = uniformBufferDescriptorSets[i],
      .dstBinding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .pBufferInfo = &descriptorBufferInfo
    };
  }

  // update all three descriptor sets
  vkUpdateDescriptorSets(device, writeDescriptorSetsCount, writeDescriptorSets, 0, nullptr);

  //////////////////////////////////////////////////////////////////////
  // shaders
  //////////////////////////////////////////////////////////////////////

  uint32_t triangleSize;
  void const * triangleStart = file::open("shader/triangle.spv", &triangleSize);

  VkShaderModuleCreateInfo shaderModuleCreateInfo{
    .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .codeSize = triangleSize,
    .pCode = (uint32_t *)triangleStart
  };
  VkShaderModule shaderModule{};
  VK_CHECK(vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule));

  //////////////////////////////////////////////////////////////////////
  // pipeline
  //////////////////////////////////////////////////////////////////////

  VkDescriptorSetLayout descriptorSetLayouts[2] = {
    uniformBufferDescriptorSetLayout,
    textureDescriptorSetLayout,
  };

  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    .setLayoutCount = 2,
    .pSetLayouts = descriptorSetLayouts,
  };
  VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

  VkVertexInputBindingDescription vertexBindingDescriptions[1]{
    {
      .binding = 0,
      .stride = ((3 + 3 + 2) * (sizeof (float))),
      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    }
  };
  VkVertexInputAttributeDescription vertexAttributeDescriptions[3]{
    { .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = 3 * 4 * 0 },
    { .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = 3 * 4 * 1 },
    { .location = 2, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = 3 * 4 * 2 },
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
      .module = shaderModule,
      .pName = "VSMain"
    },
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = shaderModule,
      .pName = "PSMain"
    }
  };

  VkPipelineShaderStageCreateInfo outlineShaderStages[2]{
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_VERTEX_BIT,
      .module = shaderModule,
      .pName = "VSOutlineMain"
    },
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = shaderModule,
      .pName = "PSOutlineMain"
    }
  };

  VkPipelineViewportStateCreateInfo viewportState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    .viewportCount = 1,
    .scissorCount = 1
  };

  constexpr uint32_t dynamicStateCount = 2;
  VkDynamicState dynamicStates[dynamicStateCount]{
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR,
  };
  VkPipelineDynamicStateCreateInfo dynamicState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
    .dynamicStateCount = dynamicStateCount,
    .pDynamicStates = dynamicStates
  };

  VkPipelineDepthStencilStateCreateInfo depthStencilState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable = VK_TRUE,
    .depthWriteEnable = VK_TRUE,
    .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
    .stencilTestEnable = VK_TRUE,
    .front = {
      .failOp = VK_STENCIL_OP_REPLACE,
      .passOp = VK_STENCIL_OP_REPLACE,
      .depthFailOp = VK_STENCIL_OP_REPLACE,
      .compareOp = VK_COMPARE_OP_ALWAYS,
      .compareMask = 0x01,
      .writeMask = 0x01,
      .reference = 1,
    },
  };

  VkPipelineDepthStencilStateCreateInfo outlineDepthStencilState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable = VK_TRUE,
    .depthWriteEnable = VK_TRUE,
    .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
    .stencilTestEnable = VK_TRUE,
    .front = {
      .failOp = VK_STENCIL_OP_KEEP,
      .passOp = VK_STENCIL_OP_REPLACE,
      .depthFailOp = VK_STENCIL_OP_KEEP,
      .compareOp = VK_COMPARE_OP_NOT_EQUAL,
      .compareMask = 0x01,
      .writeMask = 0x00,
      .reference = 1,
    },
  };

  VkPipelineRenderingCreateInfo renderingCreateInfo{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
    .colorAttachmentCount = 1,
    .pColorAttachmentFormats = &surfaceFormat.format,
    .depthAttachmentFormat = depthFormat,
    .stencilAttachmentFormat = depthFormat
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
    .cullMode = VK_CULL_MODE_BACK_BIT,
    .frontFace = VK_FRONT_FACE_CLOCKWISE,
    .lineWidth = 1.0f
  };
  VkPipelineMultisampleStateCreateInfo multisampleState{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
  };

  VkGraphicsPipelineCreateInfo pipelineCreateInfos[2]{
    {
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
    },
    {
      .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
      .pNext = &renderingCreateInfo,
      .stageCount = 2,
      .pStages = outlineShaderStages,
      .pVertexInputState = &vertexInputState,
      .pInputAssemblyState = &inputAssemblyState,
      .pViewportState = &viewportState,
      .pRasterizationState = &rasterizationState,
      .pMultisampleState = &multisampleState,
      .pDepthStencilState = &outlineDepthStencilState,
      .pColorBlendState = &colorBlendState,
      .pDynamicState = &dynamicState,
      .layout = pipelineLayout
    }
  };
  VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 2, pipelineCreateInfos, nullptr, pipelines));

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
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
          quit = true;
        }
      }
      if (event.type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_CHECK(SDL_GetWindowSize(window, &windowSize.x, &windowSize.y));
      }
    }

    // shader data
    XMMATRIX model = currentModel();
    XMMATRIX view = currentView();
    XMMATRIX modelView = model * view;
    XMMATRIX transform = modelView * currentProjection();
    XMStoreFloat4x4(&shaderData.transform, transform);
    XMStoreFloat4x4(&shaderData.modelView, modelView);
    XMVECTOR lightPosition = XMVector3Transform(XMVectorSet(-3, -3, 0, 0), view);
    XMStoreFloat4(&shaderData.lightPosition, lightPosition);

    size_t frameOffset = shaderDataDevice.stride * frameIndex;
    void * frameData = (void *)(((VkDeviceSize)shaderDataDevice.mappedData) + frameOffset);
    VkDeviceSize frameSize{ (sizeof (ShaderData)) };
    memcpy(frameData, &shaderData, frameSize);
    VkDeviceSize flushSize{ roundAlignment(frameSize, physicalDeviceProperties.limits.nonCoherentAtomSize) };
    VkMappedMemoryRange shaderDataMemoryRange{
      .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
      .memory = shaderDataDevice.memory,
      .offset = frameOffset,
      .size = flushSize,
    };
    vkFlushMappedMemoryRanges(device, 1, &shaderDataMemoryRange);


    // wait for fence
    VK_CHECK(vkWaitForFences(device, 1, &fences[frameIndex], true, UINT64_MAX));
    VK_CHECK(vkResetFences(device, 1, &fences[frameIndex]));

    // acquire next image
    VK_CHECK_SWAPCHAIN(vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, presentSemaphores[frameIndex], VK_NULL_HANDLE, &imageIndex));

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
        .srcStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
        .srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT,
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
      .pDepthAttachment = &depthRenderingAttachmentInfo,
      .pStencilAttachment = &depthRenderingAttachmentInfo,
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

    VkDeviceSize vertexOffset{ 0 };
    VkDescriptorSet descriptorSets[2] = {
      uniformBufferDescriptorSets[frameIndex],
      textureDescriptorSet,
    };
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 2, descriptorSets, 0, nullptr);
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexIndexBuffer, &vertexOffset);
    VkDeviceSize indexOffset{ vertexBufferSize };
    vkCmdBindIndexBuffer(commandBuffer, vertexIndexBuffer, indexOffset, VK_INDEX_TYPE_UINT32);
    VkDeviceSize indexCount{ 2400 };

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[MAIN_PIPELINE]);
    vkCmdDrawIndexed(commandBuffer, indexCount, 3, 0, 0, 0);

    //vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[OUTLINE_PIPELINE]);
    //vkCmdDrawIndexed(commandBuffer, indexCount, 3, 0, 0, 0);

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
      recreateSwapchain(surfaceFormat, depthFormat, physicalDeviceMemoryProperties.memoryProperties, surfaceCapabilities);
    }
  }

  VK_CHECK(vkDeviceWaitIdle(device));
  for (uint32_t i = 0; i < maxFramesInFlight; i++) {
    vkDestroyFence(device, fences[i], nullptr);
    vkDestroySemaphore(device, presentSemaphores[i], nullptr);

    vkDestroyBuffer(device, shaderDataDevice.frame[i].buffer, nullptr);
  }
  vkUnmapMemory(device, shaderDataDevice.memory);
  vkFreeMemory(device, shaderDataDevice.memory, nullptr);

  for (uint32_t i = 0; i < swapchainImageCount; i++) {
    vkDestroySemaphore(device, renderSemaphores[i], nullptr);
    vkDestroyImageView(device, swapchainImageViews[i], nullptr);
  }

  vkDestroyImage(device, depthImage, nullptr);
  vkFreeMemory(device, depthImageMemory, nullptr);
  vkDestroyImageView(device, depthImageView, nullptr);

  vkDestroyBuffer(device, vertexIndexBuffer, nullptr);
  vkFreeMemory(device, vertexIndexBufferMemory, nullptr);

  vkDestroyImageView(device, textureImageView, nullptr);
  vkDestroySampler(device, textureSampler, nullptr);
  vkDestroyImage(device, textureImage, nullptr);
  vkFreeMemory(device, textureImageMemory, nullptr);

  vkDestroyDescriptorSetLayout(device, uniformBufferDescriptorSetLayout, nullptr);
  vkDestroyDescriptorSetLayout(device, textureDescriptorSetLayout, nullptr);
  vkDestroyDescriptorPool(device, descriptorPool, nullptr);
  vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
  vkDestroyPipeline(device, pipelines[0], nullptr);
  vkDestroyPipeline(device, pipelines[1], nullptr);
  vkDestroySwapchainKHR(device, swapchain, nullptr);
  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyCommandPool(device, commandPool, nullptr);
  vkDestroyShaderModule(device, shaderModule, nullptr);

  SDL_DestroyWindow(window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_Quit();

  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
}
