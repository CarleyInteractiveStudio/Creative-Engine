# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Isrc -Ivendor -IGlad/include
LDFLAGS = -lSDL2 -lGL

# Windows cross-compilation
WIN_CXX = x86_64-w64-mingw32-g++
WIN_CXXFLAGS = -std=c++14 -Isrc -Ivendor -IGlad/include -I/path/to/your/SDL2/windows/include
WIN_LDFLAGS = -L/path/to/your/SDL2/windows/lib -lSDL2 -lglew32 -lopengl32

# Source files
SRCS = src/main.cpp \
       src/core/Vector3.cpp \
       src/core/Matrix4.cpp \
       src/core/Matter.cpp \
       src/core/TransformLaw.cpp \
       src/core/AppearanceLaw.cpp \
       src/renderer/Camera.cpp \
       src/renderer/Mesh.cpp \
       src/renderer/Material.cpp \
       src/renderer/Renderer.cpp \
       src/renderer/Window.cpp \
       src/editor/Editor.cpp \
       vendor/imgui.cpp \
       vendor/imgui_demo.cpp \
       vendor/imgui_draw.cpp \
       vendor/imgui_impl_sdl.cpp \
       vendor/imgui_impl_opengl3.cpp \
       vendor/imgui_widgets.cpp \
       Glad/src/glad.c

OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

# Targets
TARGET = engine
WIN_TARGET = engine.exe

all: $(TARGET)

windows: $(WIN_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(WIN_TARGET): $(OBJS)
	$(WIN_CXX) $(WIN_CXXFLAGS) -o $(WIN_TARGET) $(OBJS) $(WIN_LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(WIN_TARGET)
