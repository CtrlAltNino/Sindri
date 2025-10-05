target_sources(${targetName}
  PRIVATE
  NodeEditor.cpp
)

add_subdirectory(nodes)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})