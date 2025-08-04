# Simple Makefile for the Creative Engine

# --- Variables ---

# Compiler
CXX = g++

# Compiler flags
# -std=c++17: Use the C++17 standard
# -g: Include debug symbols
# -I.: Add the root project directory ('CreativeEngine/') to the include path
#      so we can use #include "Engine/Core/Log.h"
# -Wall: Enable all standard warnings
CXXFLAGS = -std=c++17 -g -I. -Wall

# Linker flags
# -lX11: Link against the X11 library (Xlib)
LDFLAGS = -lX11

# Executable name
TARGET = creative_engine

# --- Source Files ---

# List all C++ source files here
SRCS = main.cpp \
       Engine/Platform/Linux/Window.cpp \
       Engine/Platform/Linux/Input.cpp \
       Engine/Platform/Timer.cpp \
       Engine/MatterSystem/Matter.cpp \
       Engine/MatterSystem/Laws/SpriteLaw.cpp \
       Engine/MatterSystem/Laws/AnimationLaw.cpp \
       Engine/SceneSpace/SceneSpace.cpp \
       Engine/Renderer/Image.cpp \
       Engine/Renderer/Renderer2D.cpp

# Object files are derived from the source files (e.g., main.cpp -> main.o)
OBJS = $(SRCS:.cpp=.o)


# --- Rules ---

# The default target, 'all', depends on the final executable.
all: $(TARGET)

# Rule for linking the final executable.
# It depends on all the object files.
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete. Executable: $(TARGET)"

# Rule for compiling a .cpp file into a .o object file.
# The '$<' is an automatic variable for the dependency (the .cpp file).
# The '$@' is an automatic variable for the target (the .o file).
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for cleaning up build files.
clean:
	@echo "Cleaning up..."
	rm -f $(OBJS) $(TARGET)

# Phony targets are not actual files.
.PHONY: all clean
