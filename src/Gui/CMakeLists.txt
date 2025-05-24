target_sources(${targetName}
    PRIVATE
    SindriGui.cpp
)

add_subdirectory(ImGui)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})