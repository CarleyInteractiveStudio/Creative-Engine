CXX = g++
CXXFLAGS = -std=c++11 -Isrc
LDFLAGS = -lSDL2 -lGL

SRCS = src/main.cpp \
       src/core/Vector3.cpp \
       src/core/Matrix4.cpp \
       src/renderer/Camera.cpp \
       src/renderer/Mesh.cpp \
       src/renderer/Material.cpp \
       src/renderer/Renderer.cpp \
       src/renderer/Window.cpp

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
