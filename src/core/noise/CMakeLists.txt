target_sources(${targetName}
    PRIVATE
    NoiseLayer.cpp
    NoiseLayerFactory.cpp
)

target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})