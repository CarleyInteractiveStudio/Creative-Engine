CXX = g++
CXXFLAGS = -std=c++11 -Isrc -Ivendor/imgui
LDFLAGS = -lSDL2 -lGL

SRCS = src/main.cpp \
       src/core/Vector3.cpp \
       src/core/Matrix4.cpp \
       src/renderer/Camera.cpp \
       src/renderer/Mesh.cpp \
       src/renderer/Material.cpp \
       src/renderer/Renderer.cpp \
       src/renderer/Window.cpp \
       src/editor/Editor.cpp \
       vendor/imgui/imgui.cpp \
       vendor/imgui/imgui_demo.cpp \
       vendor/imgui/imgui_draw.cpp \
       vendor/imgui/imgui_impl_sdl.cpp \
       vendor/imgui/imgui_impl_opengl3.cpp \
       vendor/imgui/imgui_widgets.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = engine

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
