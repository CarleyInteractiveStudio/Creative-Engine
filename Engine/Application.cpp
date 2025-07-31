#include "Application.h"
#include "Core/Logger.h"
#include "Core/Time.h"

#include "Input/InputManager.h"
#include "Platform/Window.h"
#include <SDL2/SDL.h>

namespace Creative {

Application::Application() {
    // Constructor
}

Application::~Application() {
    // Destructor
}

void Application::Init() {
    Logger::Init();
    Time::Init();

    m_Window = std::make_unique<Window>("Creative-Engine v0.1", 1280, 720);
    if (!m_Window->Init()) {
        Logger::Error("Window initialization failed. Shutting down.");
        m_IsRunning = false;
        return;
    }

    Logger::Info("Application initialized.");
    m_IsRunning = true;
}

void Application::Run() {
    Logger::Info("Starting main loop. Press ESC to quit.");
    while (m_IsRunning) {
        InputManager::PrepareForNewFrame();

        // --- Event Processing ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            InputManager::ProcessEvent(event); // Forward event to InputManager

            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
        }

        // --- Input-based Logic ---
        if (InputManager::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
            m_IsRunning = false;
        }

        // --- Update ---
        Time::Update();
        float dt = Time::GetDeltaTime();
        // (Game logic updates would go here)

        // --- Render ---
        SDL_Surface* surface = SDL_GetWindowSurface(m_Window->GetNativeWindow());
        if (surface) {
            // Fill the surface with a solid color
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 34, 34, 34));
            SDL_UpdateWindowSurface(m_Window->GetNativeWindow());
        }
    }
}

void Application::Shutdown() {
    if (m_Window) {
        m_Window->Shutdown();
    }
    Logger::Info("Application shutting down.");
}

} // namespace Creative
