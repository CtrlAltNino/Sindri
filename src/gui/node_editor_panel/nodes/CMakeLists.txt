add_subdirectory(arithmetic_operations)
add_subdirectory(vector_operations)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})