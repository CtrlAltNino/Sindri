target_sources(${targetName}
    PRIVATE
    main.cpp
)

add_subdirectory(Application)
add_subdirectory(ProceduralTexture)
add_subdirectory(NoiseGenerator)
add_subdirectory(CompositionStack)
add_subdirectory(TextureExporter)
add_subdirectory(TexturePreview)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})