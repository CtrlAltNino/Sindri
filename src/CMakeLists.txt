target_sources(${targetName}
    PRIVATE
    main.cpp
)

add_subdirectory(Application)
add_subdirectory(DI)
add_subdirectory(GpuPreviewTexture)
add_subdirectory(GraphicsContext)
add_subdirectory(Gui)
add_subdirectory(NoiseLayer)
add_subdirectory(TextureBuffer)
add_subdirectory(TextureExporter)
add_subdirectory(TexturePipeline)
add_subdirectory(TexturePipelineExecutor)
add_subdirectory(TexturePreview)
add_subdirectory(Window)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})