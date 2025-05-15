# =======================================
# ========== CMAKE ENVIRONMENT ==========
# =======================================

# Set the minimum required CMake Version
cmake_minimum_required(VERSION 3.22)

# Add the vcpkg toolchain file
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

set(DNFD_PORTAL ON CACHE BOOL "Use portal for NFD")
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(VCPKG_MAX_CONCURRENCY 8)

# Platform dependant settings
IF(WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows-static")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ELSEIF(UNIX)
    set(VCPKG_TARGET_TRIPLET "x64-linux")
ENDIF()

# =========================================
# ========== Project Declaration ==========
# =========================================
project(Sindri VERSION 0.1.0 LANGUAGES C CXX)

# ========== Global Behaviour ==========
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ===================================
# ========== Sindri Target ==========
# ===================================

# Executable name
set(targetName sindri)

# Create an executable
add_executable(${targetName})

# Add the source files to the target through directory level CMakeLists.txt
add_subdirectory(src)

# =======================================
# ========== Target Properties ==========
# =======================================
set_target_properties(${targetName} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${targetName} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_compile_options(${targetName} PRIVATE
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-command-line-argument>
)

IF(WIN32)
    target_link_options(${targetName} PRIVATE
        $<$<CONFIG:Debug>:/SUBSYSTEM:CONSOLE>
        $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>)

    target_compile_definitions(${targetName} PRIVATE UNICODE _UNICODE)
ENDIF()

target_include_directories(${targetName} PRIVATE src)
target_precompile_headers(${targetName} PRIVATE src/pch.hpp)

# =========================================
# ========== Target Dependencies ==========
# =========================================

# this is heuristically generated, and may not be correct
find_package(glad CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE glm::glm)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
target_link_libraries(${targetName} PRIVATE SDL3::SDL3)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE imgui::imgui)

find_package(nfd CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE nfd::nfd)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

# ===============================================
# ========== Copy into build directory ==========
# ===============================================

# Copy files to build folder
# add_custom_command(TARGET
# ${targetName}
# POST_BUILD COMMAND ${CMAKE_COMMAND}
# -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${targetName}>/data)