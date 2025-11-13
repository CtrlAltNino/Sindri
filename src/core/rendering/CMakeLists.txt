add_subdirectory(graphics_context)
add_subdirectory(texture)
add_subdirectory(shader)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})