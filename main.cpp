#include "Core/Logger.h"
#include "Core/Time.h"
#include "Object/Object.h"
#include "Object/Component.h"

#include <iostream>
#include <thread>
#include <chrono>

// Define a simple component for demonstration purposes.
class PlayerController : public Creative::Component {
public:
    void Init() override {
        Creative::Logger::Info("PlayerController component initialized for object: '" + GetOwner()->GetName() + "'");
    }

    void Update(float deltaTime) override {
        m_TimeSinceLastLog += deltaTime;
        if (m_TimeSinceLastLog >= 1.0f) {
            Creative::Logger::Info("PlayerController is updating...");
            m_TimeSinceLastLog = 0.0f;
        }
    }

    void Shutdown() override {
        Creative::Logger::Info("PlayerController component shut down.");
    }

private:
    float m_TimeSinceLastLog = 0.0f;
};

int main(int argc, char* argv[]) {
    Creative::Logger::Init();

    // Create a game object and add our test component to it.
    Creative::Object player("Player");
    player.AddComponent<PlayerController>();

    Creative::Time::Init();
    Creative::Logger::Info("Starting simulated game loop...");

    // Simulate a simple game loop for a few "frames".
    for (int i = 0; i < 5; ++i) {
        // In a real engine, this would be the start of the frame.
        Creative::Time::Update();
        float dt = Creative::Time::GetDeltaTime();

        std::cout << "\n--- Frame " << i << " (DeltaTime: " << dt << "s) ---" << std::endl;

        // Update all game objects.
        player.Update(dt);

        // Simulate a delay as if rendering and other tasks were running.
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    Creative::Logger::Info("Simulated game loop finished.");

    // Clean up the game object and its components.
    player.Shutdown();

    return 0;
}
