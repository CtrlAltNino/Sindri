add_subdirectory(GpuPreviewTexture)
add_subdirectory(TextureBuffer)
add_subdirectory(TexturePipeline)
add_subdirectory(TexturePipelineExecutor)
add_subdirectory(TexturePreview)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})