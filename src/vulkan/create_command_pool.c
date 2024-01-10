#include "conventions.h"
#include "memory.h"
#include <instance.h>
#include <vulkan/vulkan_core.h>

static void destroy_command_pool(void *pointer) {
    vkDestroyCommandPool(vulkan.logical_device, pointer, 0x0);
}

void vulkan_create_command_pool() {
    VkCommandPoolCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    info.queueFamilyIndex = vulkan.graphic_index;

    vkresult_check(vkCreateCommandPool(vulkan.logical_device, &info, 0x0, &vulkan.command_pool), "error creating command pool");

    memory_push(vulkan.command_pool, destroy_command_pool);
}
