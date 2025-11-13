add_subdirectory(opengl)
add_subdirectory(metal)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})