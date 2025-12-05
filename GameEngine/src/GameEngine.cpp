#include "GameEngine.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GameEngine::GameEngine()
    : m_Window(nullptr), m_GLContext(nullptr), m_IsRunning(false) {}

GameEngine::~GameEngine() {}

bool GameEngine::Initialize() {
    // Request OpenGL 3.3 Core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow(
        "Creative Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN // Use OpenGL flag
    );
    if (m_Window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_GLContext = SDL_GL_CreateContext(m_Window);
    if (m_GLContext == nullptr) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize glad
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // Use V-Sync
    SDL_GL_SetSwapInterval(1);

    // Set OpenGL viewport
    glViewport(0, 0, 800, 600);

    m_IsRunning = true;
    return true;
}

void GameEngine::Run() {
    while (m_IsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
        }

        // Render with OpenGL
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the window to show the new frame
        SDL_GL_SwapWindow(m_Window);
    }
}

void GameEngine::Shutdown() {
    if (m_GLContext) {
        SDL_GL_DeleteContext(m_GLContext);
    }
    if (m_Window) {
        SDL_DestroyWindow(m_Window);
    }
    SDL_Quit();
}