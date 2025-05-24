target_sources(${targetName}
    PRIVATE
    OpenGLImGuiLayer.cpp
    ImGuiLayerFactory.cpp
)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})