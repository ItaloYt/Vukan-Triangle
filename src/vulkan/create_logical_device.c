#include "conventions.h"
#include "memory.h"
#include <instance.h>
#include <vulkan/vulkan_core.h>

static void destroy_logical_device(void *pointer) {
    vkDestroyDevice(pointer, 0x0);
}

void vulkan_create_logical_device() {
    VkDeviceQueueCreateInfo graphic = {0};
    graphic.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    graphic.queueCount = 1;
    graphic.pQueuePriorities = &(float) { 1 };
    graphic.queueFamilyIndex = vulkan.graphic_index;

    VkDeviceQueueCreateInfo present = {0};
    present.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    present.queueCount = 1;
    present.pQueuePriorities = &(float) { 1 };
    present.queueFamilyIndex = vulkan.present_index;

    VkDeviceCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.ppEnabledExtensionNames = (const char *[]) { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    info.enabledExtensionCount = 1;
    info.pEnabledFeatures = &(VkPhysicalDeviceFeatures) {0};
    info.queueCreateInfoCount = 2;
    info.pQueueCreateInfos = (VkDeviceQueueCreateInfo[]) { graphic, present };

    vkresult_check(vkCreateDevice(vulkan.physical_device, &info, 0x0, &vulkan.logical_device), "error creating logical device");

    memory_push(vulkan.logical_device, destroy_logical_device);

    vkGetDeviceQueue(vulkan.logical_device, vulkan.graphic_index, 0, &vulkan.graphic);
    vkGetDeviceQueue(vulkan.logical_device, vulkan.present_index, 0, &vulkan.present);
}
