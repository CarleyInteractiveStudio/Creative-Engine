#pragma once

#include "../renderer/Window.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

class Editor {
public:
    Editor();
    ~Editor();

    void run();

private:
    void handle_input();
    void render_ui();

    Window window;
};
