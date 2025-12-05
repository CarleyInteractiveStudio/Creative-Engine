# Create the executable for our game engine from main.cpp, GameEngine.cpp, and glad.c
add_executable(GameEngine main.cpp GameEngine.cpp ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c)

# --- Link SDL2 libraries ---
# Find the SDL2 library file inside the downloaded folder
find_library(SDL2_LIBRARY NAMES SDL2 PATHS ${SDL2_DIR}/lib/x64)
# Find the SDL2main library file (required on Windows)
find_library(SDL2MAIN_LIBRARY NAMES SDL2main PATHS ${SDL2_DIR}/lib/x64)

# Link SDL2 and SDL2main to our executable
target_link_libraries(GameEngine PRIVATE ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})

# --- Box2D Configuration ---
# Gather all Box2D source files
file(GLOB BOX2D_SOURCES "${CMAKE_SOURCE_DIR}/vendor/Box2D/src/**/*.cpp")

# Add Box2D sources to the executable
target_sources(GameEngine PRIVATE ${BOX2D_SOURCES})

# --- miniaudio Configuration ---
# Add miniaudio source file to the executable
target_sources(GameEngine PRIVATE ${CMAKE_SOURCE_DIR}/vendor/miniaudio/miniaudio.c)

# Link Audio libraries (SDL2 includes audio functionality)
target_link_libraries(GameEngine PRIVATE SDL2)

