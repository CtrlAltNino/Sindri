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
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/app_icon_windows.rc")
    set(EXECUTABLE_ADDITIONAL_SETTINGS ${APP_ICON_RESOURCE_WINDOWS})
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
target_sources(${targetName} PRIVATE ${EXECUTABLE_ADDITIONAL_SETTINGS})

# Add the source files to the target through directory level CMakeLists.txt
add_subdirectory(src)

# =======================================
# ========== Target Properties ==========
# =======================================
# set_target_properties(${targetName} PROPERTIES VERSION ${PROJECT_VERSION})
target_compile_options(${targetName} PRIVATE
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-command-line-argument>
)

IF(WIN32)
    target_link_options(${targetName} PRIVATE
        $<$<CONFIG:Debug>:/SUBSYSTEM:CONSOLE>
        $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>)

    target_compile_definitions(${targetName} PRIVATE UNICODE _UNICODE)
ENDIF()

target_compile_definitions(${targetName} PRIVATE
    $<$<CONFIG:Debug>:SINDRI_DEBUG_BUILD>
)

target_include_directories(${targetName} PRIVATE src)
target_precompile_headers(${targetName} PRIVATE src/pch.hpp)

# =========================================
# ========== Target Dependencies ==========
# =========================================
include(FetchContent)

FetchContent_Declare(ImNodeFlow
    GIT_REPOSITORY "https://github.com/Fattorino/ImNodeFlow.git"
    GIT_TAG master
)

FetchContent_MakeAvailable(ImNodeFlow)

# Define the directory manually (ImNodeFlow doesn't have CMakeLists.txt)
set(IMNODEFLOW_DIR ${imnodeflow_SOURCE_DIR})

list(APPEND imnode_flow_sources
    ${IMNODEFLOW_DIR}/src/ImNodeFlow.cpp
)

target_sources(${targetName}
    PRIVATE
    ${imnode_flow_sources}
)

target_include_directories(${targetName}
    PRIVATE ${IMNODEFLOW_DIR}/include
)

# this is heuristically generated, and may not be correct
find_package(glad CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE glm::glm)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
target_link_libraries(${targetName} PRIVATE SDL3::SDL3)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE imgui::imgui)
target_compile_definitions(${targetName}
    PRIVATE IMGUI_DEFINE_MATH_OPERATORS
)

find_package(nfd CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE nfd::nfd)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

find_package(magic_enum CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE magic_enum::magic_enum)

find_package(Lua REQUIRED)
target_include_directories(${targetName} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${targetName} PRIVATE ${LUA_LIBRARIES})

find_path(SOL2_INCLUDE_DIRS "sol/abort.hpp")
target_include_directories(${targetName} PRIVATE ${SOL2_INCLUDE_DIRS})

find_package(SPNG CONFIG REQUIRED)
target_link_libraries(${targetName} PRIVATE $<IF:$<TARGET_EXISTS:spng::spng>,spng::spng,spng::spng_static>)

find_path(BEXT_DI_INCLUDE_DIRS "boost/di.hpp")
target_include_directories(${targetName} PRIVATE ${BEXT_DI_INCLUDE_DIRS})

# ===============================================
# ========== Copy into build directory ==========
# ===============================================

# Copy files to build folder
add_custom_command(TARGET
    ${targetName}
    POST_BUILD COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_SOURCE_DIR}/lua $<TARGET_FILE_DIR:${targetName}>/lua)

add_custom_command(TARGET
    ${targetName}
    POST_BUILD COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${targetName}>/shaders)

add_custom_command(TARGET
    ${targetName}
    POST_BUILD COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:${targetName}>/fonts)