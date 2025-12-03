# Example of using a C++ Framework (Raylib) with custom development tools 
## CMPSC F124 1 Game Programming - Fall 2025

This project is a simple C++ application, written using Raylib, that is a top-down, room-based game prototype.

It also demonstrates using an intermediate GUI (DearImGUI) to create debug menus

## Building

This project relies on several external libraries:

- [Raylib](https://www.raylib.com/) - The framework used to make the game.
- [Raylib-Cpp](https://github.com/RobLoach/raylib-cpp) - CPP wrapper around Raylib's C functions
- [nlohmann/json](https://github.com/nlohmann/json) - Used for parsing JSON files which store map data (created as a custom export with [Tiled](https://www.mapeditor.org/))
- [DearImGui](https://github.com/ocornut/imgui) - The immediate GUI library used for debug information
- [rlImGui](https://github.com/raylib-extras/rlImGui) - The raylib backend for DearImGui

All libraries should be placed in a `./vendor` folder in the repo

- rlImGui contains a premake script that will download DearImGui and Raylib, compile them, and produce a library (ex: librlImGui.a, librlImGui.dll). Place this in the root of the `vendor` folder.
- Place raylib's headers and library files in the `vendor/raylib` folder.
- Place the header files for nlohmann/json in the `vendor/json` folder.
- Place the header files for rlImGui in the `vendor/rlimgui` folder.
- Place the header files for Raylib-Cpp in the `vendor/rlcpp` folder.
- Place the ImGui files in the `vendor/imgui` folder.

Please note that the Makefiles' `all` target can compile for both Windows and Linux, but using the makefile, anything related to Imgui (the debug features) only works with Linux for now.

To compile without Debug features, use the command `make DEBUG_ON=0`
