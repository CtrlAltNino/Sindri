target_sources(${targetName}
    PRIVATE
    WorkflowSettings.cpp
)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})