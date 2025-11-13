target_sources(${targetName}
  PRIVATE
  NodeEditorPanel.cpp
)

add_subdirectory(nodes)
add_subdirectory(node_editor)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})