#include "Engine/Core/Log.h"
#include "Engine/Core/Memory.h"
#include "Engine/SceneSpace/SceneSpace.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/Image.h"
#include "Engine/Renderer/Camera2D.h"
#include "Engine/MatterSystem/Laws/AppearanceLaw.h"
#include "Engine/MatterSystem/Laws/SpriteLaw.h"
#include "Engine/MatterSystem/Laws/AnimationLaw.h"
#include "Engine/Platform/Window.h"

int main(int argc, char** argv)
{
    Creative::Log::Core_Info("Initializing Creative Engine...");

    // --- Initialization ---
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;

    auto window = Creative::CreateScope<Creative::Window>("Creative Engine", WIDTH, HEIGHT);
    auto scene = Creative::CreateScope<Creative::SceneSpace>();
    auto renderer = Creative::CreateScope<Creative::Renderer2D>();
    auto image = Creative::CreateScope<Creative::Image>(WIDTH, HEIGHT);

    // --- Scene Setup ---
    Creative::Log::Core_Info("Setting up scene...");

    // Create the camera
    auto* camera = scene->CreateMatter<Creative::Camera2D>("Primary Camera");
    camera->position = { 0.0f, 0.0f, 0.0f };
    camera->orthographicSize = (float)HEIGHT / 2.0f;

    // Create a Player Matter that will be animated
    auto* player = scene->CreateMatter<Creative::Matter>("Player");
    player->position = { -40.0f, 0.0f, 0.0f };
    // The AppearanceLaw now only defines the size of the quad.
    player->AddLaw<Creative::AppearanceLaw>(Creative::Vec2{16, 16}, Creative::Color{});
    // The SpriteLaw provides the sprite sheet texture.
    player->AddLaw<Creative::SpriteLaw>("walk_cycle.ppm");
    // The AnimationLaw drives the animation.
    // 2 frames total, at 2 frames per second, from a sheet with 2 columns and 1 row.
    player->AddLaw<Creative::AnimationLaw>(2, 2.0f, 2, 1);


    // Create an Enemy Matter (a green rectangle, not animated)
    auto* enemy = scene->CreateMatter<Creative::Matter>("Enemy");
    enemy->position = { 40.0f, 0.0f, 0.0f };
    enemy->AddLaw<Creative::AppearanceLaw>(
        Creative::Vec2{20, 40},
        Creative::Color{50, 200, 50}
    );

    // --- Main Loop ---
    Creative::Log::Core_Info("Starting main loop...");
    while (window->IsOpen())
    {
        // 1. Process OS messages
        window->Update();

        // 2. Update scene logic (this will call OnUpdate on all laws, including AnimationLaw)
        scene->Update(0.016f);

        // 3. Render the scene to our image buffer
        renderer->Render(*scene, *image);

        // 4. Draw the image buffer to the window
        window->DrawBuffer(*image);
    }

    Creative::Log::Core_Info("Shutting down Creative Engine.");

    return 0;
}
