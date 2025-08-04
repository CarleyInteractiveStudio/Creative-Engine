#include "Engine/Core/Log.h"
#include "Engine/Core/Memory.h"
#include "Engine/SceneSpace/SceneSpace.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/Image.h"
#include "Engine/MatterSystem/Laws/AppearanceLaw.h"

// This main function is dedicated to testing the software renderer.
// It will create a scene, render it to an image, and save the image.
int main(int argc, char** argv)
{
    Creative::Log::Core_Info("Initializing Creative Engine for render test...");

    // --- Initialization ---
    auto scene = Creative::CreateScope<Creative::SceneSpace>();
    auto renderer = Creative::CreateScope<Creative::Renderer2D>();
    auto image = Creative::CreateScope<Creative::Image>(400, 300);

    // --- Scene Setup ---
    Creative::Log::Core_Info("Setting up scene...");
    // Create a Player Matter (a red square)
    Creative::Matter* player = scene->CreateMatter("Player");
    player->position = { -80.0f, 0.0f, 0.0f }; // Positioned to the left of center
    player->AddLaw<Creative::AppearanceLaw>(
        Creative::Vec2{50, 50},              // Size
        Creative::Color{200, 50, 50}         // Color (Red)
    );

    // Create an Enemy Matter (a green rectangle)
    Creative::Matter* enemy = scene->CreateMatter("Enemy");
    enemy->position = { 80.0f, 25.0f, 0.0f }; // Positioned to the right and up
    enemy->AddLaw<Creative::AppearanceLaw>(
        Creative::Vec2{40, 80},              // Size
        Creative::Color{50, 200, 50}         // Color (Green)
    );

    // --- Logic & Render ---
    // In a real game, you'd have a loop here. For this test, we just need one frame.
    scene->Update(0.0f); // Run a single logic update (no-op for now)
    renderer->Render(*scene, *image);

    // --- Save Output ---
    image->Save("/app/CreativeEngine/frame.ppm");

    Creative::Log::Core_Info("Shutting down Creative Engine.");

    return 0;
}
