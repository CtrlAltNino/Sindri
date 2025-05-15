# Set the minimum required CMake Version
cmake_minimum_required(VERSION 3.22)


if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

# Project declaration
project(Sindri VERSION 0.1.0 LANGUAGES C CXX)

# Helper functions
set(DNFD_PORTAL ON CACHE BOOL "Use portal for NFD")

# add_compile_definitions(NOMINMAX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(targetName sindri)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(VCPKG_MAX_CONCURRENCY 8)
set(VCPKG_FEATURE_FLAGS "manifests")


file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.hpp
)

# Platform dependant settings
IF(WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows-static")
    #set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/app_icon_windows.rc")
    #set(EXECUTABLE_ADDITIONAL_SETTINGS ${APP_ICON_RESOURCE_WINDOWS})
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    # Hiding the console window in release mode
    target_link_options(${targetName} PRIVATE
        $<$<CONFIG:Debug>:/SUBSYSTEM:CONSOLE>
        $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>)

    # Maybe move to windows only, need to test
    ADD_DEFINITIONS(-DUNICODE)
    ADD_DEFINITIONS(-D_UNICODE)
ELSEIF(UNIX)
    set(VCPKG_TARGET_TRIPLET "x64-linux")
ENDIF()

    add_executable(${targetName} ${SOURCES})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
endif()

include_directories(src)
target_precompile_headers(${targetName} PUBLIC src/pch.hpp)


IF(WIN32)
    target_link_libraries(${targetName} PUBLIC bcrypt)
ENDIF()

# Linking dependencies

# this is heuristically generated, and may not be correct
find_package(glad CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE glm::glm)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE SDL3::SDL3)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE imgui::imgui)

find_package(nfd CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE nfd::nfd)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE SDL3::SDL3)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)


# Copy files to build folder
#add_custom_command(TARGET
#    ${targetName}
#    POST_BUILD COMMAND ${CMAKE_COMMAND}
#    -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${targetName}>/data)