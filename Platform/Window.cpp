#include "Window.h"
#include "Core/Logger.h"
#include <SDL2/SDL.h>
#include "glad.h"

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

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);


    // Create an SDL Window
    m_SdlWindow = SDL_CreateWindow(
        m_Title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_Width,
        m_Height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (m_SdlWindow == nullptr) {
        Logger::Error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        SDL_Quit();
        return false;
    }

    m_GlContext = SDL_GL_CreateContext(m_SdlWindow);
    if (m_GlContext == nullptr) {
        Logger::Error("SDL_GL_CreateContext Error: " + std::string(SDL_GetError()));
        SDL_DestroyWindow(m_SdlWindow);
        SDL_Quit();
        return false;
    }

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        Logger::Error("Failed to initialize Glad");
        return false;
    }

    Logger::Info("Window and OpenGL context created successfully.");
    return true;
}

void Window::Shutdown() {
    if (m_GlContext) {
        SDL_GL_DeleteContext(m_GlContext);
        m_GlContext = nullptr;
    }

    if (m_SdlWindow != nullptr) {
        SDL_DestroyWindow(m_SdlWindow);
        m_SdlWindow = nullptr;
        // SDL_Quit is called to clean up all initialized subsystems.
        SDL_Quit();
        Logger::Info("Window system shut down.");
    }
}

void Window::SwapBuffers() {
    SDL_GL_SwapWindow(m_SdlWindow);
}

} // namespace Creative
