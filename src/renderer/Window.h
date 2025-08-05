#pragma once

#include <SDL2/SDL.h>

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    void swap_buffers();
    bool is_open() const;
    void close();

    SDL_Window* get_native_window() const { return window; }
    SDL_GLContext get_native_context() const { return context; }


private:
    SDL_Window* window;
    SDL_GLContext context;
    bool open;
};
