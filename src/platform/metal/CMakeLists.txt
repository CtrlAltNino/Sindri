IF(APPLE)
  target_sources(${targetName}
    PRIVATE
    definitions.cpp
    MetalContext.cpp
    MetalImGuiLayer.cpp
    MetalPreviewTexture.cpp
  )
ENDIF()

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})