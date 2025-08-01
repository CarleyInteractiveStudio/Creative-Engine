#include "Application.h"
#include "Core/Logger.h"
#include "Core/Time.h"

#include "Input/InputManager.h"
#include "Platform/Window.h"
#include <SDL2/SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "glad.h"

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(m_Window->GetNativeWindow(), m_Window->GetGLContext());
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Application::Run() {
    Logger::Info("Starting main loop. Press ESC to quit.");
    while (m_IsRunning) {
        InputManager::PrepareForNewFrame();

        // --- Event Processing ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
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
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();
        SDL_GL_MakeCurrent(m_Window->GetNativeWindow(), m_Window->GetGLContext());
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        m_Window->SwapBuffers();
    }
}

void Application::Shutdown() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    if (m_Window) {
        m_Window->Shutdown();
    }
    Logger::Info("Application shutting down.");
}

} // namespace Creative
