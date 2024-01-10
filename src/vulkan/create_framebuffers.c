#include "conventions.h"
#include "memory.h"
#include "window.h"
#include <errno.h>
#include <instance.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan_core.h>

static void destroy_framebuffer(void *pointer) {
    vkDestroyFramebuffer(vulkan.logical_device, pointer, 0x0);
}

void vulkan_create_framebuffers() {
    vulkan.framebuffers = malloc(vulkan.image_count * sizeof(VkFramebuffer));

    if(!vulkan.framebuffers) {
        TREAT fprintf(stderr, "error allocating framebuffers: %s\n", strerror(errno));

        memory_free();

        exit(1);
    }

    VkFramebufferCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    info.renderPass = vulkan.renderpass;
    info.attachmentCount = 1;
    info.width = WIDTH;
    info.height = HEIGHT;
    info.layers = 1;

    for(unsigned index = 0; index < vulkan.image_count; ++index) {
        info.pAttachments = vulkan.views + index;

        vkresult_check(vkCreateFramebuffer(vulkan.logical_device, &info, 0x0, vulkan.framebuffers + index), "error creating framebuffer");

        memory_push(vulkan.framebuffers[index], destroy_framebuffer);
    }
}
