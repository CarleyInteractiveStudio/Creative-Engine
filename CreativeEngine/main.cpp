#include "Engine/Core/Log.h"
#include "Engine/Core/Memory.h"
#include "Engine/SceneSpace/SceneSpace.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/Image.h"
#include "Engine/Renderer/Camera2D.h"
#include "Engine/MatterSystem/Laws/AppearanceLaw.h"

int main(int argc, char** argv)
{
    Creative::Log::Core_Info("Initializing Creative Engine for camera test...");

    // --- Initialization ---
    auto scene = Creative::CreateScope<Creative::SceneSpace>();
    auto renderer = Creative::CreateScope<Creative::Renderer2D>();
    auto image = Creative::CreateScope<Creative::Image>(400, 300);

    // --- Scene Setup ---
    Creative::Log::Core_Info("Setting up scene...");

    // Create the camera using the new templated method.
    auto* camera = scene->CreateMatter<Creative::Camera2D>("Primary Camera");
    camera->position = { 0.0f, 10.0f, 0.0f }; // Move camera up slightly
    camera->orthographicSize = 250.0f; // Zoom out a bit, so we see more of the world.

    // Create a Player Matter (a red square)
    auto* player = scene->CreateMatter<Creative::Matter>("Player");
    player->position = { -80.0f, 0.0f, 0.0f };
    player->AddLaw<Creative::AppearanceLaw>(
        Creative::Vec2{50, 50},
        Creative::Color{200, 50, 50}
    );

    // Create an Enemy Matter (a green rectangle)
    auto* enemy = scene->CreateMatter<Creative::Matter>("Enemy");
    enemy->position = { 80.0f, 25.0f, 0.0f };
    enemy->AddLaw<Creative::AppearanceLaw>(
        Creative::Vec2{40, 80},
        Creative::Color{50, 200, 50}
    );

    // --- Logic & Render ---
    // No loop needed for a static image test.
    scene->Update(0.0f);
    renderer->Render(*scene, *image);

    // --- Save Output ---
    image->Save("/app/CreativeEngine/frame.ppm");

    Creative::Log::Core_Info("Shutting down Creative Engine.");

    return 0;
}
