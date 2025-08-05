#pragma once

#include <vector>
#include <memory>
#include "../core/Matter.h"

class Window;
class Renderer;
class Camera;

class Editor {
public:
    Editor();
    ~Editor();

    void run();

private:
    void render_ui();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Camera> m_camera;
    std::vector<std::unique_ptr<Creative::Matter>> m_matters;
};
