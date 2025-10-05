add_subdirectory(graphics_context)
add_subdirectory(image)
add_subdirectory(noise)
add_subdirectory(texture)
add_subdirectory(variables)
add_subdirectory(workflow_settings)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})