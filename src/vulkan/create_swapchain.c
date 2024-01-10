#include "conventions.h"
#include "memory.h"
#include "window.h"
#include <instance.h>
#include <vulkan/vulkan_core.h>

static void destroy_swapchain(void *pointer) {
    vkDestroySwapchainKHR(vulkan.logical_device, vulkan.swapchain, 0x0);
}

void vulkan_create_swapchain() {
    VkSwapchainCreateInfoKHR info = {0};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.surface = vulkan.surface;
    info.clipped = VK_TRUE;
    info.imageExtent.width = WIDTH;
    info.imageExtent.height = HEIGHT;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.imageFormat = VK_FORMAT_B8G8R8A8_SRGB;
    info.imageArrayLayers = 1;
    info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    info.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    info.minImageCount = MIN_IMAGE_COUNT;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    vkresult_check(vkCreateSwapchainKHR(vulkan.logical_device, &info, 0x0, &vulkan.swapchain), "error creating swapchain");

    memory_push(vulkan.swapchain, destroy_swapchain);
}
