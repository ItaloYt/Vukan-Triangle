#include "conventions.h"
#include "window.h"
#include <instance.h>
#include <vulkan/vulkan_core.h>

void vulkan_record_commands(unsigned image_index) {
    VkCommandBufferBeginInfo begin_info = {0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkresult_check(vkBeginCommandBuffer(vulkan.command_buffer, &begin_info), "error beggining command buffer");

    VkRenderPassBeginInfo render_info = {0};
    render_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_info.renderPass = vulkan.renderpass;
    render_info.framebuffer = vulkan.framebuffers[image_index];
    render_info.renderArea.extent.width = WIDTH;
    render_info.renderArea.extent.height = HEIGHT;

    VkClearValue clear_color = {0};
    clear_color.color.float32[3] = 1;

    render_info.clearValueCount = 1;
    render_info.pClearValues = &clear_color;

    vkCmdBeginRenderPass(vulkan.command_buffer, &render_info, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(vulkan.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan.pipeline);
    vkCmdSetViewport(vulkan.command_buffer, 0, 1, &vulkan.viewport);
    vkCmdSetScissor(vulkan.command_buffer, 0, 1, &vulkan.scissor);
    
    vkCmdDraw(vulkan.command_buffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(vulkan.command_buffer);

    vkresult_check(vkEndCommandBuffer(vulkan.command_buffer), "error ending command buffer");
}
