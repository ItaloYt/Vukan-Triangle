#include "conventions.h"
#include "instance.h"
#include "memory.h"
#include <vulkan/vulkan_core.h>

static void destroy_semaphore(void *pointer) {
    vkDestroySemaphore(vulkan.logical_device, pointer, 0x0);
}

static void destroy_fence(void *pointer) {
    vkDestroyFence(vulkan.logical_device, pointer, 0x0);
}

void vulkan_create_signals() {
    VkSemaphoreCreateInfo semaphore = {0};
    semaphore.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence = {0};
    fence.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    vkresult_check(vkCreateSemaphore(vulkan.logical_device, &semaphore, 0x0, &vulkan.image_available), "error creating 'image available' signal");
    vkresult_check(vkCreateSemaphore(vulkan.logical_device, &semaphore, 0x0, &vulkan.render_finished), "error creating 'render finished' signal");
    vkresult_check(vkCreateFence(vulkan.logical_device, &fence, 0x0, &vulkan.frame_finished), "error creating 'frame finished' signal");

    memory_push(vulkan.image_available, destroy_semaphore);
    memory_push(vulkan.render_finished, destroy_semaphore);
    memory_push(vulkan.frame_finished, destroy_fence);
}
