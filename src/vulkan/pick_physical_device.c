#include "conventions.h"
#include "memory.h"
#include <instance.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

static void select_physical_device();
static void load_queue_families();

static void log_formats();
static void log_present_modes();
static void log_capabilities();

void vulkan_pick_physical_device() {
    select_physical_device();
    load_queue_families();
}

static void log_capabilities() {
    VkSurfaceCapabilitiesKHR capabilities = {0};
    vkresult_check(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkan.physical_device, vulkan.surface, &capabilities), "error getting physical device surface capabilities");

    TREAT printf("Surface Capabilites:\n| min_image_count='%u'\n| max_image_count='%u'\n| min_extent='(%u, %u)'\n| max_extend='(%u, %u)'", capabilities.minImageCount, capabilities.maxImageCount, capabilities.minImageExtent.width, capabilities.minImageExtent.height, capabilities.maxImageExtent.width, capabilities.maxImageExtent.height);
}

static void log_present_modes() {
    unsigned count = 0;
    vkresult_check(vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan.physical_device, vulkan.surface, &count, 0x0), "error getting physical device surface present modes");

    VkPresentModeKHR modes[count];
    vkresult_check(vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan.physical_device, vulkan.surface, &count, modes), "error getting physical device surface present modes");

    for(unsigned index = 0; index < count; ++index)
        TREAT printf("Present mode: %u\n", modes[index]);
}

static void log_formats() {
    unsigned count = 0;
    vkresult_check(vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan.physical_device, vulkan.surface, &count, 0x0), "error getting physical device surface formats");

    VkSurfaceFormatKHR formats[count];
    vkresult_check(vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan.physical_device, vulkan.surface, &count, formats), "error getting physical device surface formats");

    for(unsigned index = 0; index < count; ++index)
        TREAT printf("surface format: format='%u', colorspace='%u'\n", formats[index].format, formats[index].colorSpace);
}

static void load_queue_families() {
    unsigned count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vulkan.physical_device, &count, 0x0);
    
    VkQueueFamilyProperties properties[count];
    vkGetPhysicalDeviceQueueFamilyProperties(vulkan.physical_device, &count, properties);

    vulkan.graphic_index = -1;
    vulkan.present_index = -1;

    for(unsigned index = 0; index < count; ++index) {
        if(vulkan.graphic_index == -1 && properties[index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            vulkan.graphic_index = index;

        if(vulkan.present_index == -1) {
            VkBool32 present = VK_FALSE;
            vkresult_check(vkGetPhysicalDeviceSurfaceSupportKHR(vulkan.physical_device, index, vulkan.surface, &present), "error getting physical device surface support");

            if(present)
                vulkan.present_index = index;
        }
    }

    if(vulkan.graphic_index == -1) {
        TREAT fputs("error getting graphic queue family index\n", stderr);

        memory_free();

        exit(1);
    }

    if(vulkan.present_index == -1) {
        TREAT fputs("error getting present queue family index\n", stderr);

        memory_free();

        exit(1);
    }
}

static void select_physical_device() {
    unsigned count = 0;
    vkresult_check(vkEnumeratePhysicalDevices(vulkan.instance, &count, 0x0), "error enumerating physical devices");

    VkPhysicalDevice devices[count];
    vkresult_check(vkEnumeratePhysicalDevices(vulkan.instance, &count, devices), "error enumerating physical devices");

    if(count == 0) {
        TREAT fputs("error no physical device found\n", stderr);

        memory_free();

        exit(1);
    }

    vulkan.physical_device = devices[0];
}
