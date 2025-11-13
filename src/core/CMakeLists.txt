add_subdirectory(image)
add_subdirectory(noise)
add_subdirectory(variables)
add_subdirectory(workflow_settings)
add_subdirectory(rendering)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})