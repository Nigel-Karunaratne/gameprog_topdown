cmake_minimum_required(VERSION 4.1)

project(
    GameProgrammingHonorsProject
    VERSION 0.1
    LANGUAGES CXX
)

# Set CXX version
set(CMAKE_CXX STANDARD 17)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Fetch packages/libraries
include(FetchContent)

# Raylib
message(STATUS, "Preparing raylib...")
set(RAYLIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/vendor/raylib)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5  # You can pin to a specific release tag
)

FetchContent_MakeAvailable(raylib)

set(FETCHCONTENT_QUIET OFF)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Build raylib games" FORCE)

add_library(raylib_static ALIAS raylib)

add_custom_command(TARGET raylib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RAYLIB_INSTALL_DIR}/lib
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RAYLIB_INSTALL_DIR}/include
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:raylib> ${RAYLIB_INSTALL_DIR}/lib/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${raylib_SOURCE_DIR}/../src ${RAYLIB_INSTALL_DIR}/include
    COMMENT "Copying raylib static lib and headers to ${RAYLIB_INSTALL_DIR}"
)

# RayCPP
message(STATUS, "Preparing raylib-cpp...")

# Imgui
message(STATUS, "Preparing imgui...")

set(IMGUI_VERSION 1.92.2b)
FetchContent_Declare(
    imgui
    URL https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}.zip
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/vendor/imgui
)
FetchContent_MakeAvailable(imgui)
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR})

# rlimgui
message(STATUS, "Preparing rlimgui...")

# Compile 

add_executable(Game main.cpp)
