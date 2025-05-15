target_sources(${targetName}
    PRIVATE
    CompositionStack.cpp
    StackEntry.cpp
)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})