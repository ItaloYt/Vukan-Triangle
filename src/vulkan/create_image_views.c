#include "conventions.h"
#include "memory.h"
#include <errno.h>
#include <instance.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan_core.h>

static void destroy_image_view(void *pointer) {
    vkDestroyImageView(vulkan.logical_device, pointer, 0x0);
}

void vulkan_create_image_views() {
    vkresult_check(vkGetSwapchainImagesKHR(vulkan.logical_device, vulkan.swapchain, &vulkan.image_count, 0x0), "error getting swapchain images");

    vulkan.images = malloc(vulkan.image_count * sizeof(VkImage));

    if(!vulkan.images) {
        TREAT fprintf(stderr, "error allocating images: %s\n", strerror(errno));

        memory_free();

        exit(1);
    }
    
    vkresult_check(vkGetSwapchainImagesKHR(vulkan.logical_device, vulkan.swapchain, &vulkan.image_count, vulkan.images), "error getting swapchain images");

    vulkan.views = malloc(vulkan.image_count * sizeof(VkImage));

    if(!vulkan.views) {
        TREAT fprintf(stderr, "error using malloc: %s\n", strerror(errno));

        memory_free();

        exit(1);
    }

    memory_push(vulkan.views, 0x0);

    VkImageViewCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    info.format = VK_FORMAT_B8G8R8A8_SRGB;
    info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    info.subresourceRange.layerCount = 1;
    info.subresourceRange.levelCount = 1;
    info.subresourceRange.baseMipLevel = 0;
    info.subresourceRange.baseArrayLayer = 0;
    info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

    for(unsigned index = 0; index < vulkan.image_count; ++index) {
        info.image = vulkan.images[index];

        vkresult_check(vkCreateImageView(vulkan.logical_device, &info, 0x0, vulkan.views + index), "error creating image view");

        memory_push(vulkan.views[index], destroy_image_view);
    }
}
