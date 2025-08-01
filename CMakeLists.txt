# Sets the minimum version of CMake required to build this project.
cmake_minimum_required(VERSION 3.10)

# Declares the project name, version, and language.
project(CreativeEngine VERSION 1.0 LANGUAGES CXX C)

# Sets the C++ standard to C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Gather all source files for our core engine library.
# Using GLOB is convenient for now, but for larger projects,
# listing files explicitly is often preferred.
file(GLOB_RECURSE ENGINE_CORE_SOURCES
    "Core/*.cpp"
    "Object/*.cpp"
    "Engine/*.cpp"
    "Platform/*.cpp"
    "Input/*.cpp"
    "ImGui/*.cpp"
)

# Create a static library named "CreativeEngineCore" from the source files.
add_library(CreativeEngineCore STATIC ${ENGINE_CORE_SOURCES})

# Specify the include directories for the CreativeEngineCore library.
# This allows the compiler to find the header files (.h) when compiling.
# `PUBLIC` means that any other target linking against this library
# will also inherit these include directories.
target_include_directories(CreativeEngineCore PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "ImGui"
)

target_compile_definitions(CreativeEngineCore PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

# Create a static library for Glad
add_library(glad STATIC Glad/glad.c)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" Glad)

# Link CreativeEngineCore against SDL2 and glad
target_link_libraries(CreativeEngineCore PUBLIC SDL2::SDL2 glad)

# --------------------------------------------------------------------
# Executable
# --------------------------------------------------------------------

# Creates an executable named "CreativeEngine" from main.cpp.
add_executable(CreativeEngine main.cpp)

# Find external packages
find_package(SDL2 REQUIRED)

# Links our executable against the core engine library and other dependencies.
# This makes the classes and functions in our library available to the executable.
target_link_libraries(CreativeEngine PRIVATE CreativeEngineCore)
