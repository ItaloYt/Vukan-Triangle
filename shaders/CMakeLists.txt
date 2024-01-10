cmake_minimum_required(VERSION 3.27.7)

if(NOT EXISTS ${SHADER_BINARIES_DIRECTORY})
    file(MAKE_DIRECTORY ${SHADER_BINARIES_DIRECTORY})
endif()

file(GLOB_RECURSE shader_sources "*.vert" "*.frag")

foreach(shader_source ${shader_sources})
    get_filename_component(shader_filename ${shader_source} NAME)

    string(REPLACE "${SHADER_DIRECTORY}" "" shader_relative_file ${shader_source})
    string(REPLACE "${shader_filename}" "" shader_relative_directory ${shader_relative_file})

    set(shader_spirv_directory "${SHADER_BINARIES_DIRECTORY}${shader_relative_directory}")

    if(NOT EXISTS ${shader_spirv_directory})
        file(MAKE_DIRECTORY ${shader_spirv_directory})
    endif()

    set(shader_spirv_path "${shader_spirv_directory}${shader_filename}.spv")

    add_custom_command(
        OUTPUT ${shader_spirv_path}
        COMMAND ${GLSL_COMPILER} -o ${shader_spirv_path} ${shader_source}
    )

    string(REPLACE "/" "_" shader_variable_name ${shader_relative_file})
    string(REPLACE "." "_" shader_variable_name ${shader_variable_name})

    list(APPEND shader_variable_names _${shader_variable_name}_spv)
    list(APPEND shader_binaries ${shader_spirv_path})
endforeach()

add_custom_target(
    shader_target ALL
    DEPENDS ${shader_binaries}
)

file(WRITE ${SHADER_VARIABLES_FILE} "")

foreach(variable_name shader_spirv IN ZIP_LISTS shader_variable_names shader_binaries)
    add_custom_command(
        TARGET shader_target
        POST_BUILD
        COMMAND ${SPIRV_TO_C} ${variable_name} ${shader_spirv} ${SHADER_VARIABLES_FILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endforeach()
