#include "conventions.h"
#include <instance.h>
#include <vulkan/vulkan_core.h>

/*
static void destroy_command_buffer(void *pointer) {
    
}
*/

void vulkan_create_command_buffer() {
    VkCommandBufferAllocateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.commandPool = vulkan.command_pool;
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    info.commandBufferCount = 1;

    vkresult_check(vkAllocateCommandBuffers(vulkan.logical_device, &info, &vulkan.command_buffer), "error creating command buffer");

    // destroy command pool destroys command buffers
    // memory_push(vulkan.command_buffer, destroy_command_buffer);
}
