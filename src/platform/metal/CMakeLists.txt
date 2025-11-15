IF(APPLE)
  target_sources(${targetName}
    PRIVATE
    MetalContext.cpp
    MetalImGuiLayer.cpp
    MetalTexture.cpp
  )
ENDIF()

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})