target_sources(${targetName}
  PRIVATE
  main.cpp
)

add_subdirectory(application)
add_subdirectory(core)
add_subdirectory(di)
add_subdirectory(gui)
add_subdirectory(helper)
add_subdirectory(platform)
add_subdirectory(window)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})