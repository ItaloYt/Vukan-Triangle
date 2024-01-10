#include "memory.h"
#include "window.h"
#include <conventions.h>
#include <instance.h>

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vulkan/vulkan_core.h>

static void terminate(void *pointer) {
    glfwTerminate();
}

int main() {
    memory_init();

	if(!glfwInit()) {
        const char *error = 0x0;
        glfwGetError(&error);

		TREAT fprintf(stderr, "error glfw init: %s\n", error);

        return 1;
	}

    memory_push(0x0, terminate);
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "vulkan", 0x0, 0x0);

    if(!window) {
        const char *error = 0x0;
        glfwGetError(&error);

		TREAT fprintf(stderr, "error glfw create window: %s\n", error);

        memory_free();

        return 1;
    }

    memory_push(window, (MemoryFreeCallback) glfwDestroyWindow);

    vulkan_create_instance();
    vulkan_create_surface(window);
    vulkan_pick_physical_device();
    vulkan_create_logical_device();
    vulkan_create_swapchain();
    vulkan_create_image_views();
    vulkan_create_shader_modules();
    vulkan_create_renderpass();
    vulkan_create_pipeline();
    vulkan_create_framebuffers();
    vulkan_create_command_pool();
    vulkan_create_command_buffer();
    vulkan_create_signals();

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        vulkan_draw_frame();
    }

    vkDeviceWaitIdle(vulkan.logical_device);

    memory_free();
}
