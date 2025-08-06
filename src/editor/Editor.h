#pragma once

#include <vector>
#include <memory>
#include "../core/Matter.h"

class Window;
class Renderer;
class Camera;
class Framebuffer;

class Editor {
public:
    Editor();
    ~Editor();

    void run();

private:
    void render_ui();
    void render_hierarchy_panel();
    void render_inspector_panel();
    void render_scene_view_panel();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Framebuffer> m_framebuffer;
    std::vector<std::unique_ptr<Creative::Matter>> m_matters;
    Creative::Matter* m_selected_matter = nullptr;
};
