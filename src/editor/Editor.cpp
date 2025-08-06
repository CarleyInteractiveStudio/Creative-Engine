#include "Editor.h"
#include <typeinfo>
#include <filesystem>
#include <fstream>
#include <SDL3/SDL.h>
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "../renderer/Window.h"
#include "../renderer/Renderer.h"
#include "../renderer/Camera.h"
#include "../renderer/Framebuffer.h"
#include "../core/Matter.h"
#include "../core/TransformLaw.h"
#include "../core/MaterialColorLaw.h"

Editor::Editor() {
    m_window = std::make_unique<Window>("Creative Engine", 1280, 720);
    m_renderer = std::make_unique<Renderer>();
    m_camera = std::make_unique<Camera>();
    m_framebuffer = std::make_unique<Framebuffer>(1280, 720);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(m_window->get_native_window(), m_window->get_native_context());
    ImGui_ImplOpenGL3_Init("#version 330");

    // Create a sample matter
    auto matter = std::make_unique<Creative::Matter>();
    matter->AddLaw<Creative::TransformLaw>();
    matter->AddLaw<Creative::MaterialColorLaw>();
    m_matters.push_back(std::move(matter));
}

Editor::~Editor() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void Editor::run() {
    while (m_window->is_open()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                m_window->close();
            }
        }

        for (auto& matter : m_matters) {
            matter->OnUpdate(0.0f); // TODO: pass real delta time
        }

        // --- Scene Rendering ---
        m_framebuffer->Bind();
        glViewport(0, 0, 1280, 720); // TODO: Make this dynamic
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& matter : m_matters) {
            m_renderer->draw(*matter, *m_camera);
        }
        m_framebuffer->Unbind();


        // --- UI Rendering ---
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        render_ui();

        ImGui::Render();

        // Clear the main window before drawing the UI
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        m_window->swap_buffers();
    }
}

void Editor::render_ui() {
    // We are using the ImGuiWindowFlags_NoDocking flag to prevent the main window from being docked into itself.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    ImGui::PopStyleVar(3);

    // Submit the DockSpace
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                m_window->close();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

    // The demo window will now be dockable
    ImGui::ShowDemoWindow();

    // Our custom editor panels
    render_hierarchy_panel();
    render_inspector_panel();
    render_scene_view_panel();
    render_asset_panel();
}

void Editor::render_hierarchy_panel() {
    ImGui::Begin("Hierarchy");

    for (const auto& matter : m_matters) {
        // Basic selectable text. We can add more features like rename, delete, etc. later.
        if (ImGui::Selectable(matter->m_name.c_str(), m_selected_matter == matter.get())) {
            m_selected_matter = matter.get();
        }
    }

    ImGui::End();
}

void Editor::render_asset_panel() {
    ImGui::Begin("Assets");

    const std::filesystem::path asset_path = "."; // Project root

    if (ImGui::Button("Create Folder")) {
        ImGui::OpenPopup("CreateFolderPopup");
    }

    ImGui::SameLine();
    if (ImGui::Button("Create Script")) {
        ImGui::OpenPopup("CreateScriptPopup");
    }

    if (ImGui::BeginPopup("CreateFolderPopup")) {
        static char folderName[128] = "";
        ImGui::InputText("Folder Name", folderName, sizeof(folderName));
        if (ImGui::Button("Create")) {
            if (strlen(folderName) > 0) {
                std::filesystem::create_directory(asset_path / folderName);
                // Reset the buffer after creation
                memset(folderName, 0, sizeof(folderName));
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("CreateScriptPopup")) {
        static char scriptName[128] = "";
        ImGui::InputText("Script Name", scriptName, sizeof(scriptName));
        if (ImGui::Button("Create")) {
            if (strlen(scriptName) > 0) {
                const std::filesystem::path asset_path = ".";
                std::string filename = std::string(scriptName) + ".cs";
                std::ofstream file(asset_path / filename);
                file.close();
                // Reset the buffer after creation
                memset(scriptName, 0, sizeof(scriptName));
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }

    ImGui::Separator();

    for (const auto& entry : std::filesystem::directory_iterator(asset_path)) {
        const auto& path = entry.path();
        auto relative_path = std::filesystem::relative(path, asset_path);
        std::string filename_string = relative_path.filename().string();

        if (entry.is_directory()) {
            ImGui::Text("[D] %s", filename_string.c_str());
        } else {
            ImGui::Text("[F] %s", filename_string.c_str());
        }
    }

    ImGui::End();
}

void Editor::render_scene_view_panel() {
    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    uint32_t textureID = m_framebuffer->GetColorAttachmentRendererID();
    ImGui::Image((void*)(intptr_t)textureID, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void Editor::render_inspector_panel() {
    ImGui::Begin("Inspector");

    if (m_selected_matter) {
        // Display Matter's name (and allow editing it)
        char buffer[256];
        strncpy(buffer, m_selected_matter->m_name.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = 0;
        if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
            m_selected_matter->m_name = buffer;
        }

        ImGui::Separator();

        // Display TransformLaw properties
        if (auto* transform_law = m_selected_matter->GetLaw<Creative::TransformLaw>()) {
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::DragFloat3("Position", &transform_law->position.x, 0.1f);
                ImGui::DragFloat3("Rotation", &transform_law->rotation.x, 0.1f);
                ImGui::DragFloat3("Scale", &transform_law->scale.x, 0.1f);
            }
        }

        // Display MaterialColorLaw properties
        if (auto* color_law = m_selected_matter->GetLaw<Creative::MaterialColorLaw>()) {
            if (ImGui::CollapsingHeader("Material Color", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::ColorEdit3("Color", &color_law->color.x);
            }
        }

        ImGui::Separator();
        if (ImGui::Button("Add Law")) {
            ImGui::OpenPopup("AddLawPopup");
        }

        if (ImGui::BeginPopup("AddLawPopup")) {
            if (ImGui::MenuItem("Transform Law")) {
                if (m_selected_matter->GetLaw<Creative::TransformLaw>() == nullptr) {
                    m_selected_matter->AddLaw<Creative::TransformLaw>();
                }
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::MenuItem("Material Color Law")) {
                if (m_selected_matter->GetLaw<Creative::MaterialColorLaw>() == nullptr) {
                    m_selected_matter->AddLaw<Creative::MaterialColorLaw>();
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

    } else {
        ImGui::Text("No matter selected.");
    }

    ImGui::End();
}
