#include <instance.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>
#include <conventions.h>

void vulkan_draw_frame() {
    vkresult_check(vkWaitForFences(vulkan.logical_device, 1, &vulkan.frame_finished, VK_TRUE, UINT64_MAX), "error waiting for signal 'frame finished'");
    vkresult_check(vkResetFences(vulkan.logical_device, 1, &vulkan.frame_finished), "error reseting signal 'frame finished'");

    unsigned image_index = 0;
    vkresult_check(vkAcquireNextImageKHR(vulkan.logical_device, vulkan.swapchain, UINT64_MAX, vulkan.image_available, 0x0, &image_index), "error acquiring next image");

    vkresult_check(vkResetCommandBuffer(vulkan.command_buffer, 0), "error reseting command buffer");
    vulkan_record_commands(image_index);

    VkSubmitInfo submit = {0};
    submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit.waitSemaphoreCount = 1;
    submit.pWaitSemaphores = &vulkan.image_available;
    submit.pWaitDstStageMask = (VkPipelineStageFlags[]) { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &vulkan.command_buffer;
    submit.signalSemaphoreCount = 1;
    submit.pSignalSemaphores = &vulkan.render_finished;

    vkresult_check(vkQueueSubmit(vulkan.graphic, 1, &submit, vulkan.frame_finished), "error submiting queue");

    VkPresentInfoKHR present_info = {0};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = &vulkan.render_finished;
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &vulkan.swapchain;
    present_info.pImageIndices = &image_index;

    vkresult_check(vkQueuePresentKHR(vulkan.present, &present_info), "error presenting image");
}
