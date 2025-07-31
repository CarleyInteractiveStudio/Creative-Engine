#include "Window.h"
#include "Core/Logger.h"
#include <SDL2/SDL.h>

namespace Creative {

Window::Window(const std::string& title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height) {
}

Window::~Window() {
    // Shutdown should be called explicitly, but this is a safeguard.
    Shutdown();
}

bool Window::Init() {
    Logger::Info("Initializing Window System (SDL)...");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        Logger::Error("SDL_Init Error: " + std::string(SDL_GetError()));
        return false;
    }

    // Create an SDL Window
    m_SdlWindow = SDL_CreateWindow(
        m_Title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_Width,
        m_Height,
        SDL_WINDOW_SHOWN // We will add graphics API flags later (e.g., SDL_WINDOW_OPENGL)
    );

    if (m_SdlWindow == nullptr) {
        Logger::Error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        SDL_Quit();
        return false;
    }

    Logger::Info("Window created successfully.");
    return true;
}

void Window::Shutdown() {
    if (m_SdlWindow != nullptr) {
        SDL_DestroyWindow(m_SdlWindow);
        m_SdlWindow = nullptr;
        // SDL_Quit is called to clean up all initialized subsystems.
        SDL_Quit();
        Logger::Info("Window system shut down.");
    }
}

void Window::SwapBuffers() {
    // This will be used later when we have a graphics context (e.g., OpenGL).
    // For OpenGL, this would call SDL_GL_SwapWindow(m_SdlWindow);
}

} // namespace Creative
