#ifndef CREATIVE_ENGINE_APPLICATION_H
#define CREATIVE_ENGINE_APPLICATION_H

#include <memory>

namespace Creative {

class Window; // Forward-declare Window

class Application {
public:
    Application();
    virtual ~Application();

    // Initializes all engine systems.
    void Init();

    // Contains the main game loop.
    void Run();

    // Shuts down all engine systems and cleans up resources.
    void Shutdown();

private:
    std::unique_ptr<Window> m_Window;
    bool m_IsRunning = false;
};

} // namespace Creative

#endif //CREATIVE_ENGINE_APPLICATION_H
