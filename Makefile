CXX = g++
CXXFLAGS = -std=c++14 -Isrc -Ivendor -IGlad/include -Iexternal/SDL2-Binaries/include
LDFLAGS = -lSDL2 -lGL -Lexternal/SDL2-Binaries/lib

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

TARGET = engine

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
