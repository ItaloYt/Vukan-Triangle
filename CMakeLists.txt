if(NOT DEFINED LIBRARY_PATH)
    set(LIBRARY_PATH "./")
endif()

if(NOT DEFINED VULKAN_LIBRARY_NAME)
    set(VULKAN_LIBRARY_NAME "vulkan")
endif()

if(NOT DEFINED GLFW3_LIBRARY_NAME)
    set(GLFW3_LIBRARY_NAME "glfw")
endif()

if(NOT DEFINED GLSL_COMPILER)
    set(GLSL_COMPILER "glslc")
endif()

if(NOT DEFINED SHADER_DIRECTORY)
    set(SHADER_DIRECTORY "${CMAKE_SOURCE_DIR}/shaders")
endif()

if(NOT DEFINED SHADER_BINARIES_DIRECTORY)
    set(SHADER_BINARIES_DIRECTORY "${CMAKE_SOURCE_DIR}/shader_binaries")
endif()

if(NOT DEFINED SPIRV_TO_C)
    set(SPIRV_TO_C "${CMAKE_SOURCE_DIR}/spirv_to_c.sh")
endif()

if(NOT DEFINED INCLUDE_DIRECTORY)
    set(INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/include")
endif()

if(NOT DEFINED SOURCE_DIRECTORY)
    set(SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/src")
endif()

if(NOT DEFINED SHADER_VARIABLES_FILE)
    set(SHADER_VARIABLES_FILE "${SOURCE_DIRECTORY}/shader_variables.c")
endif()

cmake_minimum_required(VERSION 3.27.7)
project(vktest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(${SHADER_DIRECTORY})

file(GLOB_RECURSE src "${SOURCE_DIRECTORY}/*.c" "${INCLUDE_DIRECTORY}/*.h")

add_executable(vktest ${src})
add_dependencies(vktest shader_target)

target_include_directories(vktest PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(vktest PUBLIC ${VULKAN_LIBRARY_NAME} ${GLFW3_LIBRARY_NAME})
target_link_directories(vktest PUBLIC ${LIBRARY_PATH})
# target_compile_options(vktest PUBLIC "-g3" "-O0")
