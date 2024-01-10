#include "conventions.h"
#include <GLFW/glfw3.h>
#include <instance.h>

void vulkan_create_surface(GLFWwindow *window) {
    vkresult_check(glfwCreateWindowSurface(vulkan.instance, window, 0x0, &vulkan.surface), "error creating window surface");
}
