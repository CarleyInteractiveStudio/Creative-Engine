# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Define the project
project(CreativeEngine CXX C)

# Set the C++ standard to 17 to use std::filesystem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the SDL git submodule to the build.
# This will use SDL's own CMakeLists.txt to build it as part of our project.
add_subdirectory(SDL)

# Add the source directory, which contains the engine's code.
# This will cause CMake to look for a CMakeLists.txt file in the 'src' directory.
add_subdirectory(src)
