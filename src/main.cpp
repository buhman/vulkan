#include <stdio.h>
#include <stdlib.h>

#include "volk/volk.h"
#include "vulkan/vk_enum_string_helper.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
#include "directxmath/directxmath.h"

#include "check.h"
#include "new.h"
#include "file.h"
#include "dds/validate.h"
#include "vulkan_helper.h"
#include "shader_data.h"
#include "minmax.h"

#include "collada/scene.h"
#include "collada/scene/vulkan.h"

#include "scenes/shadow_test/shadow_test.h"

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
VkDeviceMemory depthMemory{ VK_NULL_HANDLE };

VkImage shadowDepthImage{ VK_NULL_HANDLE };
VkImageView shadowDepthImageView{ VK_NULL_HANDLE };
VkImageView shadowDepthImageViewDepth{ VK_NULL_HANDLE };
VkDeviceMemory shadowDepthMemory{ VK_NULL_HANDLE };

VkFence fences[maxFramesInFlight];
VkSemaphore presentSemaphores[maxFramesInFlight];
VkSemaphore * renderSemaphores{ nullptr };

VkCommandPool commandPool{ VK_NULL_HANDLE };
VkCommandBuffer commandBuffers[maxFramesInFlight];

VkSampler textureSamplers[3]{ VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE };

VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };

XMINT2 windowSize{};

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

XMMATRIX currentProjection()
{
  float fov_angle_y = XMConvertToRadians(45 * 1.0);
  float aspect_ratio = (float)windowSize.x / (float)windowSize.y;
  float near_z = 0.1;
  float far_z = 1000.0;
  XMMATRIX projection = XMMatrixPerspectiveFovLH(fov_angle_y, aspect_ratio, near_z, far_z);
  return projection;
}

XMMATRIX currentView(collada::instance_types::node const & camera_node,
                     collada::instance_types::node const & camera_target_node)
{

  XMVECTOR eye = XMVector3Transform(XMVectorZero(), camera_node.world);
  XMVECTOR at = XMVector3Transform(XMVectorZero(), camera_target_node.world);
  XMVECTOR up = XMVectorSet(0, 0, 1, 0);
  XMMATRIX view = XMMatrixLookAtLH(eye, at, up);
  return view;
}

float theta = 0;

XMMATRIX currentModel()
{
  theta += 0.01;
  return XMMatrixTranslation(0, 0, 0.0) * XMMatrixRotationX(theta) * XMMatrixRotationZ(XM_PI * 0.5f);
}

void createDepth(VkDeviceSize nonCoherentAtomSize,
                 VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                 uint32_t width,
                 uint32_t height,
                 VkFormat format,
                 VkImageUsageFlags usage,
                 VkImage * image,
                 VkDeviceMemory * memory,
                 VkImageView * imageView)
{
  VkImageCreateInfo imageCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = format,
    .extent{
      .width = width,
      .height = height,
      .depth = 1,
    },
    .mipLevels = 1,
    .arrayLayers = 1,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .tiling = VK_IMAGE_TILING_OPTIMAL,
    .usage = usage,
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
  };
  VK_CHECK(vkCreateImage(device, &imageCreateInfo, nullptr, image));

  VkMemoryRequirements memoryRequirements;
  vkGetImageMemoryRequirements(device, *image, &memoryRequirements);
  VkMemoryPropertyFlags memoryPropertyFlags{ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT };
  VkMemoryAllocateFlags memoryAllocateFlags{ };
  VkDeviceSize stride;
  allocateFromMemoryRequirements(device,
                                 nonCoherentAtomSize,
                                 physicalDeviceMemoryProperties,
                                 memoryRequirements,
                                 memoryPropertyFlags,
                                 memoryAllocateFlags,
                                 1,
                                 memory,
                                 &stride);
  VK_CHECK(vkBindImageMemory(device, *image, *memory, 0));

  VkImageViewCreateInfo imageViewCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = *image,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = format,
    .subresourceRange{
      .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
      .levelCount = 1,
      .layerCount = 1
    }
  };
  VK_CHECK(vkCreateImageView(device, &imageViewCreateInfo, nullptr, imageView));
}

void createCubeDepth(VkDeviceSize nonCoherentAtomSize,
                     VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                     uint32_t width,
                     uint32_t height,
                     VkFormat format,
                     VkImageUsageFlags usage,
                     VkImage * image,
                     VkDeviceMemory * memory,
                     VkImageView * imageView)
{

}

void recreateSwapchain(VkSurfaceFormatKHR surfaceFormat,
                       VkFormat depthFormat,
                       VkDeviceSize nonCoherentAtomSize,
                       VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties,
                       VkSurfaceCapabilitiesKHR const & surfaceCapabilities)
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
  if (depthMemory != VK_NULL_HANDLE) {
    vkFreeMemory(device, depthMemory, nullptr);
  }
  if (depthImageView != VK_NULL_HANDLE) {
    vkDestroyImageView(device, depthImageView, nullptr);
  }

  createDepth(nonCoherentAtomSize,
              physicalDeviceMemoryProperties,
              imageExtent.width,
              imageExtent.height,
              depthFormat,
              VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
              &depthImage,
              &depthMemory,
              &depthImageView);
}

inline static int positive_modulo(int i, unsigned int n) {
  return (i % n + n) % n;
}

inline static double getTime(int64_t start_time)
{
  int64_t current_time;
  SDL_GetCurrentTime(&current_time);
  int64_t time = current_time - start_time;
  return (double)(time / 1000) * 0.000001;
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

  VkPhysicalDeviceMemoryProperties2 physicalDeviceMemoryProperties2{
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2,
    .pNext = nullptr
  };
  vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &physicalDeviceMemoryProperties2);
  VkPhysicalDeviceMemoryProperties const & physicalDeviceMemoryProperties = physicalDeviceMemoryProperties2.memoryProperties;
  if constexpr (true) {
    for (uint32_t i = 0; i < physicalDeviceMemoryProperties.memoryTypeCount; i++) {
      printf("memoryTypes[%u].propertyFlags: ", i);
      print_memoryPropertyFlags(physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags);
      printf("memoryTypes[%u].heapIndex: %u\n", i, physicalDeviceMemoryProperties.memoryTypes[i].heapIndex);
    }
    for (uint32_t i = 0; i < physicalDeviceMemoryProperties.memoryHeapCount; i++) {
      printf("memoryHeaps[%u].size %lu\n", i, physicalDeviceMemoryProperties.memoryHeaps[i].size);
      printf("memoryHeaps[%u].flags %08x\n", i, physicalDeviceMemoryProperties.memoryHeaps[i].flags);
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
    .geometryShader = true,
    .samplerAnisotropy = true,
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
  if ((surfaceCapabilities.currentExtent.width == ~0u) && (surfaceCapabilities.currentExtent.width == ~0u)) {
    surfaceCapabilities.currentExtent.width = windowSize.x;
    surfaceCapabilities.currentExtent.height = windowSize.y;
  }
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

  recreateSwapchain(surfaceFormat, depthFormat, physicalDeviceProperties.limits.nonCoherentAtomSize, physicalDeviceMemoryProperties, surfaceCapabilities);

  //////////////////////////////////////////////////////////////////////
  // shadow
  //////////////////////////////////////////////////////////////////////

  createDepth(physicalDeviceProperties.limits.nonCoherentAtomSize,
              physicalDeviceMemoryProperties,
              1024,
              1024,
              depthFormat,
              VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
              &shadowDepthImage,
              &shadowDepthMemory,
              &shadowDepthImageView);


  VkImageViewCreateInfo imageViewCreateInfo{
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = shadowDepthImage,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = depthFormat,
    .subresourceRange{
      .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
      .levelCount = 1,
      .layerCount = 1
    }
  };
  VK_CHECK(vkCreateImageView(device, &imageViewCreateInfo, nullptr, &shadowDepthImageViewDepth));

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
  // texture sampler
  //////////////////////////////////////////////////////////////////////

  VkSamplerCreateInfo samplerCreateInfo0{
    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
    .magFilter = VK_FILTER_LINEAR,
    .minFilter = VK_FILTER_LINEAR,
    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .anisotropyEnable = VK_FALSE,
    .maxLod = 0.0, // (float)ddsFile->header.dwMipMapCount
  };
  VK_CHECK(vkCreateSampler(device, &samplerCreateInfo0, nullptr, &textureSamplers[0]));
  VkSamplerCreateInfo samplerCreateInfo1{
    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
    .magFilter = VK_FILTER_LINEAR,
    .minFilter = VK_FILTER_LINEAR,
    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .anisotropyEnable = VK_FALSE,
    .maxLod = VK_LOD_CLAMP_NONE, // (float)ddsFile->header.dwMipMapCount,
  };
  VK_CHECK(vkCreateSampler(device, &samplerCreateInfo1, nullptr, &textureSamplers[1]));
  VkSamplerCreateInfo samplerCreateInfo2{
    .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
    .magFilter = VK_FILTER_LINEAR,
    .minFilter = VK_FILTER_LINEAR,
    .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
    .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
    .anisotropyEnable = VK_TRUE,
    .maxAnisotropy = 16.0f,
    .maxLod = VK_LOD_CLAMP_NONE, // (float)ddsFile->header.dwMipMapCount,
  };
  VK_CHECK(vkCreateSampler(device, &samplerCreateInfo2, nullptr, &textureSamplers[2]));

  //////////////////////////////////////////////////////////////////////
  // initialize collada
  //////////////////////////////////////////////////////////////////////

  collada::scene::state collada_state;

  collada_state.vulkan.initial_state(instance,
                                     device,
                                     queue,
                                     commandPool,
                                     physicalDeviceProperties,
                                     physicalDeviceMemoryProperties,
                                     surfaceFormat.format,
                                     depthFormat,
                                     textureSamplers[0],
                                     shadowDepthImageViewDepth);

  collada::types::descriptor const * collada_scene_descriptor = &shadow_test::descriptor;
  collada_state.load_scene(collada_scene_descriptor);

  //////////////////////////////////////////////////////////////////////
  // loop
  //////////////////////////////////////////////////////////////////////

  bool updateSwapchain{ false };
  uint32_t frameIndex{ 0 };
  uint32_t imageIndex{ 0 };
  bool quit{ false };
  int32_t samplerIndex{ 0 };
  int64_t start_time;
  SDL_GetCurrentTime(&start_time);

  int cameraIndex = collada_state.find_node_index_by_name("Camera001");
  int cameraTargetIndex = collada_state.find_node_index_by_name("Camera001.Target");
  int lightIndex = collada_state.find_node_index_by_name("DirectLight");
  int lightTargetIndex = collada_state.find_node_index_by_name("DirectLight.Target");
  int lightMaterialIndex = collada_state.find_material_index_by_name("LightMaterial");

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
        if (!event.key.repeat) {
          switch (event.key.key) {
          case SDLK_LEFT:
            samplerIndex = positive_modulo(samplerIndex - 1, 3);
            printf("samplerIndex: %d\n", samplerIndex);
            break;
          case SDLK_RIGHT:
            samplerIndex = positive_modulo(samplerIndex + 1, 3);
            printf("samplerIndex: %d\n", samplerIndex);
            break;
          default:
            break;
          }
        }
      }
      if (event.type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_CHECK(SDL_GetWindowSize(window, &windowSize.x, &windowSize.y));
      }
    }

    //////////////////////////////////////////////////////////////////////
    // collada update
    //////////////////////////////////////////////////////////////////////

    double time = getTime(start_time);
    collada_state.update(time / 8.0f);

    //////////////////////////////////////////////////////////////////////
    // fence
    //////////////////////////////////////////////////////////////////////

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

    //////////////////////////////////////////////////////////////////////
    // shadow render
    //////////////////////////////////////////////////////////////////////

    // barrier

    VkImageMemoryBarrier2 shadowBarriers[1]{
      VkImageMemoryBarrier2{
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
        .srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
        .dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .newLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
        .image = shadowDepthImage,
        .subresourceRange{
          .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
          .levelCount = 1,
          .layerCount = 1
        }
      }
    };
    VkDependencyInfo shadowBarrierDependencyInfo{
      .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
      .imageMemoryBarrierCount = 1,
      .pImageMemoryBarriers = shadowBarriers
    };
    vkCmdPipelineBarrier2(commandBuffer, &shadowBarrierDependencyInfo);

    // attachments

    VkRenderingAttachmentInfo shadowDepthRenderingAttachmentInfo{
      .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
      .imageView = shadowDepthImageView,
      .imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .clearValue{ .depthStencil{ 1.0f, 0 } }
    };

    VkRenderingInfo shadowRenderingInfo{
      .sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
      .renderArea{ .extent{ .width = 1024, .height = 1024 } },
      .layerCount = 1,
      .colorAttachmentCount = 0,
      .pDepthAttachment = &shadowDepthRenderingAttachmentInfo,
      .pStencilAttachment = &shadowDepthRenderingAttachmentInfo,
    };
    vkCmdBeginRendering(commandBuffer, &shadowRenderingInfo);

    // viewport/scissor

    VkViewport shadowViewport{
      .x = 0,
      .y = 0,
      .width = 1024,
      .height = 1024,
      .minDepth = 0.0f,
      .maxDepth = 1.0f
    };
    vkCmdSetViewport(commandBuffer, 0, 1, &shadowViewport);
    VkRect2D shadowScissor{
      .extent{
        .width = 1024,
        .height = 1024
      }
    };
    vkCmdSetScissor(commandBuffer, 0, 1, &shadowScissor);

    // transfer

    {
      collada_state.vulkan.change_frame(commandBuffer, frameIndex);

      XMMATRIX projection = currentProjection();
      XMMATRIX view = currentView(collada_state.node_state.node_instances[cameraIndex],
                                  collada_state.node_state.node_instances[cameraTargetIndex]);
      XMMATRIX shadowProjection = XMMatrixOrthographicLH(300, 300, 0.1, 500);
      XMMATRIX shadowView = currentView(collada_state.node_state.node_instances[lightIndex],
                                        collada_state.node_state.node_instances[lightTargetIndex]);

      collada::instance_types::node const & lightNode = collada_state.node_state.node_instances[lightIndex];
      XMVECTOR lightPositionWorld = XMVector3Transform(XMVectorZero(), lightNode.world);

      collada_state.vulkan.transfer_transforms(projection,
                                               view,
                                               shadowProjection,
                                               shadowView,
                                               lightPositionWorld,
                                               collada_state.descriptor->nodes_count,
                                               collada_state.node_state.node_instances);
    }

    // draw

    collada_state.vulkan.excludeMaterialIndex = lightMaterialIndex;
    collada_state.vulkan.pipelineIndex = 0; // shadow pipeline
    collada_state.draw();

    vkCmdEndRendering(commandBuffer);

    // barrier

    {
      VkImageMemoryBarrier2 shadowBarriers[1]{
        {
          .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
          .srcStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
          .srcAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
          .dstStageMask = VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT,
          .dstAccessMask = VK_ACCESS_2_INPUT_ATTACHMENT_READ_BIT,
          .oldLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
          .newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
          .image = shadowDepthImage,
          .subresourceRange{
            .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
            .levelCount = 1,
            .layerCount = 1
          }
        }
      };
      VkDependencyInfo shadowBarrierDependencyInfo{
        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
        .imageMemoryBarrierCount = 1,
        .pImageMemoryBarriers = shadowBarriers
      };
      vkCmdPipelineBarrier2(commandBuffer, &shadowBarrierDependencyInfo);
    }

    //////////////////////////////////////////////////////////////////////
    // render
    //////////////////////////////////////////////////////////////////////

    VkImageMemoryBarrier2 outputBarriers[2]{
      {
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
      {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
        .srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT,
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

    // attachments

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
      .x = 0,
      .y = 0,
      .width = static_cast<float>(windowSize.x),
      .height = static_cast<float>(windowSize.y),
      .minDepth = 0.0f,
      .maxDepth = 1.0f
    };
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    VkRect2D scissor{ .extent{ .width = (uint32_t)windowSize.x, .height = (uint32_t)windowSize.y } };
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    // draw

    collada_state.vulkan.excludeMaterialIndex = -1;
    collada_state.vulkan.pipelineIndex = 1; // non-shadow pipeline
    collada_state.draw();
    collada_state.vulkan.pipelineIndex = 2; // geometry shader pipeline
    collada_state.draw();

    vkCmdEndRendering(commandBuffer);

    // barrier

    VkImageMemoryBarrier2 presentBarriers[1]{
      {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstAccessMask = 0,
        .oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        .image = swapchainImages[imageIndex],
        .subresourceRange{ .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .levelCount = 1, .layerCount = 1 }
      },
      /*
      {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstAccessMask = 0,
        .oldLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
        .newLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .image = shadowDepthImage,
        .subresourceRange{
          .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT,
          .levelCount = 1,
          .layerCount = 1
        }
      }
      */
    };
    VkDependencyInfo barrierPresentDependencyInfo{
      .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
      .imageMemoryBarrierCount = 1,
      .pImageMemoryBarriers = presentBarriers
    };
    vkCmdPipelineBarrier2(commandBuffer, &barrierPresentDependencyInfo);

    VK_CHECK(vkEndCommandBuffer(commandBuffer));

    //////////////////////////////////////////////////////////////////////
    // submit to graphics queue
    //////////////////////////////////////////////////////////////////////

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
      if ((surfaceCapabilities.currentExtent.width == ~0u) && (surfaceCapabilities.currentExtent.width == ~0u)) {
        surfaceCapabilities.currentExtent.width = windowSize.x;
        surfaceCapabilities.currentExtent.height = windowSize.y;
      }
      recreateSwapchain(surfaceFormat, depthFormat, physicalDeviceProperties.limits.nonCoherentAtomSize, physicalDeviceMemoryProperties, surfaceCapabilities);
    }
  }

  VK_CHECK(vkDeviceWaitIdle(device));

  collada_state.vulkan.destroy_all(collada_scene_descriptor);
  collada_state.unload_scene();

  for (uint32_t i = 0; i < maxFramesInFlight; i++) {
    vkDestroyFence(device, fences[i], nullptr);
    vkDestroySemaphore(device, presentSemaphores[i], nullptr);
  }

  for (uint32_t i = 0; i < swapchainImageCount; i++) {
    vkDestroySemaphore(device, renderSemaphores[i], nullptr);
    vkDestroyImageView(device, swapchainImageViews[i], nullptr);
  }

  vkDestroyImage(device, depthImage, nullptr);
  vkFreeMemory(device, depthMemory, nullptr);
  vkDestroyImageView(device, depthImageView, nullptr);

  vkDestroyImage(device, shadowDepthImage, nullptr);
  vkFreeMemory(device, shadowDepthMemory, nullptr);
  vkDestroyImageView(device, shadowDepthImageView, nullptr);
  vkDestroyImageView(device, shadowDepthImageViewDepth, nullptr);

  vkDestroySampler(device, textureSamplers[0], nullptr);
  vkDestroySampler(device, textureSamplers[1], nullptr);
  vkDestroySampler(device, textureSamplers[2], nullptr);

  vkDestroyDescriptorPool(device, descriptorPool, nullptr);
  vkDestroySwapchainKHR(device, swapchain, nullptr);
  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyCommandPool(device, commandPool, nullptr);

  SDL_DestroyWindow(window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_Quit();

  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
}
