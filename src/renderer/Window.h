#pragma once

#include <SDL2/SDL.h>

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    void swap_buffers();
    void poll_events();
    bool is_open() const;

private:
    SDL_Window* window;
    SDL_GLContext context;
    bool open;
};
