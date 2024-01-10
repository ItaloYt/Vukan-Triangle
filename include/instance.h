#ifndef INSTANCE_HEADER
#define INSTANCE_HEADER

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#define MIN_IMAGE_COUNT 4
#define SHADER_ENTRY_POINT "main"

struct Instance {
    VkInstance instance;
    VkPhysicalDevice physical_device;
    VkSurfaceKHR surface;
    VkDevice logical_device;
    VkSwapchainKHR swapchain;
    VkImage *images;
    VkImageView *views;
    VkPipelineLayout pipeline_layout;
    VkRenderPass renderpass;
    VkPipeline pipeline;
    VkFramebuffer *framebuffers;
    VkCommandPool command_pool;
    VkCommandBuffer command_buffer;

    VkSemaphore image_available;
    VkSemaphore render_finished;
    VkFence frame_finished;

    VkViewport viewport;
    VkRect2D scissor;

    VkQueue graphic;
    VkQueue present;

    VkShaderModule vertex_shader;
    VkShaderModule fragment_shader;

    unsigned image_count;

    int graphic_index;
    int present_index;

    VkDebugUtilsMessengerEXT messenger;
};

extern struct Instance vulkan;

void vulkan_create_instance();
void vulkan_create_surface(GLFWwindow *window);
void vulkan_pick_physical_device();
void vulkan_create_logical_device();
void vulkan_create_swapchain();
void vulkan_create_image_views();
void vulkan_create_shader_modules();
void vulkan_create_renderpass();
void vulkan_create_pipeline();
void vulkan_create_framebuffers();
void vulkan_create_command_pool();
void vulkan_create_command_buffer();
void vulkan_record_commands(unsigned image_index);
void vulkan_create_signals();
void vulkan_draw_frame();

#endif
