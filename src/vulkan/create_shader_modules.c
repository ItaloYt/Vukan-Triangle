#include "conventions.h"
#include "memory.h"
#include <instance.h>
#include <vulkan/vulkan_core.h>

extern const char *__shader_vert_spv;
extern unsigned __shader_vert_spv_length;

extern const char *__shader_frag_spv;
extern unsigned __shader_frag_spv_length;

static void create_module(unsigned length, const char *code, VkShaderModule *module);

void vulkan_create_shader_modules() {
    create_module(__shader_vert_spv_length, __shader_vert_spv, &vulkan.vertex_shader);
    create_module(__shader_frag_spv_length, __shader_frag_spv, &vulkan.fragment_shader);
}

static void destroy_shader(void *pointer) {
    vkDestroyShaderModule(vulkan.logical_device, pointer, 0x0);
}

static void create_module(unsigned length, const char *code, VkShaderModule *module) {
    VkShaderModuleCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = length;
    info.pCode = (const unsigned *) code;

    vkresult_check(vkCreateShaderModule(vulkan.logical_device, &info, 0x0, module), "error creating shader module");

    memory_push(*module, destroy_shader);
}
