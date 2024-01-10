#include "conventions.h"
#include "memory.h"
#include "window.h"
#include <instance.h>
#include <stdio.h>
#include <vulkan/vulkan_core.h>

static void destroy_pipeline_layout(void *pointer) {
    vkDestroyPipelineLayout(vulkan.logical_device, pointer, 0x0);
}

static void destroy_pipeline(void *pointer) {
    vkDestroyPipeline(vulkan.logical_device, pointer, 0x0);
}

void vulkan_create_pipeline() {
    VkPipelineShaderStageCreateInfo vertex = {0};
    vertex.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertex.module = vulkan.vertex_shader;
    vertex.pName = SHADER_ENTRY_POINT;

    VkPipelineShaderStageCreateInfo fragment = {0};
    fragment.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment.module = vulkan.fragment_shader;
    fragment.pName = SHADER_ENTRY_POINT;

    VkPipelineDynamicStateCreateInfo dynamic = {0};
    dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic.dynamicStateCount = 2;
    dynamic.pDynamicStates = (VkDynamicState[]) { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    
    VkPipelineVertexInputStateCreateInfo vertex_info = {0};
    vertex_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkPipelineInputAssemblyStateCreateInfo assembly = {0};
    assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    vulkan.viewport.width = WIDTH;
    vulkan.viewport.height = HEIGHT;
    vulkan.viewport.maxDepth = 1;

    vulkan.scissor.extent.height = HEIGHT;
    vulkan.scissor.extent.width = WIDTH;

    VkPipelineViewportStateCreateInfo viewport_info = {0};
    viewport_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_info.viewportCount = 1;
    viewport_info.scissorCount = 1;

    VkPipelineRasterizationStateCreateInfo rasterizer = {0};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1;
    rasterizer.cullMode = VK_CULL_MODE_NONE;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    
    VkPipelineMultisampleStateCreateInfo multisample = {0};
    multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState color_attachment = {0};
    color_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo color_blend = {0};
    color_blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blend.attachmentCount = 1;
    color_blend.pAttachments = &color_attachment;

    VkPipelineLayoutCreateInfo pipeline_info = {0};
    pipeline_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    vkresult_check(vkCreatePipelineLayout(vulkan.logical_device, &pipeline_info, 0x0, &vulkan.pipeline_layout), "error creating pipeline layout");

    memory_push(vulkan.pipeline_layout, destroy_pipeline_layout);

    VkGraphicsPipelineCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    info.stageCount = 2;
    info.pStages = (VkPipelineShaderStageCreateInfo[]) { vertex, fragment };
    info.pVertexInputState = &vertex_info;
    info.pInputAssemblyState = &assembly;
    info.pViewportState = &viewport_info;
    info.pRasterizationState = &rasterizer;
    info.pMultisampleState = &multisample;
    info.pColorBlendState = &color_blend;
    info.pDynamicState = &dynamic;
    info.layout = vulkan.pipeline_layout;
    info.renderPass = vulkan.renderpass;

    vkresult_check(vkCreateGraphicsPipelines(vulkan.logical_device, 0x0, 1, &info, 0x0, &vulkan.pipeline), "error creating pipeline");

    memory_push(vulkan.pipeline, destroy_pipeline);
}
