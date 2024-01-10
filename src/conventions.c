#include "memory.h"
#include <conventions.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

void vkresult_check(VkResult result, const char *error) {
    if(result != VK_SUCCESS) {
        TREAT fprintf(stderr, "%s: %u\n", error, result);

        memory_free();

        exit(1);
    }
}
