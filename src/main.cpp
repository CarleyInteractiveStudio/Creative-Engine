#include <iostream>
#include <vector>
#include "core/Vector3.h"
#include "renderer/Camera.h"
#include "renderer/Mesh.h"
#include "renderer/Material.h"
#include "renderer/Renderer.h"
#include "renderer/Window.h"

void render_loop() {
    Window window("3D Engine", 800, 600);

    Camera camera;
    camera.set_perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    camera.set_position(Vector3(0, 0, 5));
    camera.look_at(Vector3(0, 0, 0), Vector3(0, 1, 0));

    std::vector<Vertex> vertices = {
        { Vector3(-1, -1, -1) },
        { Vector3(1, -1, -1) },
        { Vector3(1, 1, -1) },
        { Vector3(-1, 1, -1) },
        { Vector3(-1, -1, 1) },
        { Vector3(1, -1, 1) },
        { Vector3(1, 1, 1) },
        { Vector3(-1, 1, 1) },
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        5, 4, 7, 7, 6, 5,
        4, 0, 3, 3, 7, 4,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4
    };

    Mesh cube(vertices, indices);
    Material red(Vector3(1, 0, 0));
    Renderer renderer;

    while (window.is_open()) {
        window.poll_events();

        // Clear the screen
        // In a real engine, this would be part of the renderer
        // For now, we'll just print a message
        std::cout << "Clearing the screen..." << std::endl;

        Matrix4 model_matrix = Matrix4::identity();
        renderer.render(cube, red, camera, model_matrix);

        window.swap_buffers();
    }
}

int main(int argc, char* argv[]) {
    render_loop();
    return 0;
}
