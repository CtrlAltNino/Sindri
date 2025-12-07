IF(NOT APPLE)
  target_sources(${targetName}
    PRIVATE
    OpenGLContext.cpp
    OpenGLImGuiLayer.cpp
    OpenGLPreviewTexture.cpp
  )
ENDIF()

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})