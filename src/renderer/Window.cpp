#include "Window.h"
#include <iostream>
#include "glad/glad.h"

Window::Window(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    open = true;
}

Window::~Window() {
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::swap_buffers() {
    SDL_GL_SwapWindow(window);
}

bool Window::is_open() const {
    return open;
}

void Window::close() {
    open = false;
}
