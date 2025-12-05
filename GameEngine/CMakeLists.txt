cmake_minimum_required(VERSION 3.10)
project(GameEngine VERSION 0.1.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- SDL2 Configuration ---
# Set a variable to point to our downloaded SDL2 folder
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2")
# Add the SDL2 'include' directory to the list of places the compiler will look for files
include_directories(${SDL2_DIR}/include)

# Add our own 'include' directory to the list of places the compiler will look for files
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glad/include)
# Add stb_image's directory to include paths
include_directories(${CMAKE_SOURCE_DIR}/vendor/stb)
# Add Box2D's include directory
include_directories(${CMAKE_SOURCE_DIR}/vendor/Box2D/include)

add_subdirectory(src)
