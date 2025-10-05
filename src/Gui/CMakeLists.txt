target_sources(${targetName}
  PRIVATE
  SindriGui.cpp
)

add_subdirectory(imgui)
add_subdirectory(node_editor_panel)
add_subdirectory(variables_panel)
add_subdirectory(workflow_settings_panel)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})