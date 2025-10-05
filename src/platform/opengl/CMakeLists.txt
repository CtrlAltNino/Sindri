target_sources(${targetName}
  PRIVATE
  OpenGLContext.cpp
  OpenGLImGuiLayer.cpp
  OpenGLPreviewTexture.cpp
)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})