#include "memory.h"
#include <GLFW/glfw3.h>
#include <instance.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>
#include <conventions.h>

struct Instance vulkan;

static void destroy_vk_instance(void *pointer) {
    vkDestroyInstance(pointer, 0x0);
}

void vulkan_create_instance() {
    unsigned glfw_extension_count = 0;
    const char **glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    VkApplicationInfo appinfo = {0};
    appinfo.pEngineName = "Italo's Engine";
    appinfo.engineVersion = 1;
    appinfo.pApplicationName = "vulkan";
    appinfo.applicationVersion = 1;
    appinfo.apiVersion = VK_API_VERSION_1_3;
    appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    VkInstanceCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &appinfo;
    info.enabledExtensionCount = glfw_extension_count;
    info.ppEnabledExtensionNames = glfw_extensions;
    
    vkresult_check(vkCreateInstance(&info, 0x0, &vulkan.instance), "error creating vulkan instance");

    memory_push(vulkan.instance, destroy_vk_instance);
}
