#include "Editor.h"
#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "../renderer/Window.h"
#include "../renderer/Renderer.h"
#include "../renderer/Camera.h"
#include "../core/Matter.h"
#include "../core/TransformLaw.h"
#include "../core/AppearanceLaw.h"

Editor::Editor() {
    m_window = std::make_unique<Window>("Creative Engine", 1280, 720);
    m_renderer = std::make_unique<Renderer>();
    m_camera = std::make_unique<Camera>();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(m_window->get_native_window(), m_window->get_native_context());
    ImGui_ImplOpenGL3_Init("#version 330");

    // Create a sample matter
    auto matter = std::make_unique<Creative::Matter>();
    matter->AddLaw<Creative::TransformLaw>();
    matter->AddLaw<Creative::AppearanceLaw>();
    m_matters.push_back(std::move(matter));
}

Editor::~Editor() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Editor::run() {
    while (m_window->is_open()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                m_window->close();
            }
        }

        for (auto& matter : m_matters) {
            matter->OnUpdate(0.0f); // TODO: pass real delta time
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window->get_native_window());
        ImGui::NewFrame();

        render_ui();

        // Rendering
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& matter : m_matters) {
            m_renderer->draw(*matter, *m_camera);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_window->swap_buffers();
    }
}

void Editor::render_ui() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) {
            }
            if (ImGui::MenuItem("Open Project")) {
            }
            if (ImGui::MenuItem("Export Project")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo")) {
            }
            if (ImGui::MenuItem("Redo")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Inspector");
    for (auto& matter : m_matters) {
        if (ImGui::TreeNode("Matter")) {
            auto* transform = matter->GetLaw<Creative::TransformLaw>();
            if (transform && ImGui::TreeNode("Transform")) {
                ImGui::DragFloat3("Position", &transform->position.x, 0.1f);
                ImGui::DragFloat3("Rotation", &transform->rotation.x, 0.1f);
                ImGui::DragFloat3("Scale", &transform->scale.x, 0.1f);
                ImGui::TreePop();
            }
            auto* appearance = matter->GetLaw<Creative::AppearanceLaw>();
            if (appearance && ImGui::TreeNode("Appearance")) {
                ImGui::ColorEdit3("Color", &appearance->color.x);
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
    ImGui::End();
}
