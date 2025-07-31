#ifndef CREATIVE_ENGINE_GAMELOOP_H
#define CREATIVE_ENGINE_GAMELOOP_H

namespace Creative {

// The GameLoop class will be responsible for the main loop's timing and structure.
// For now, this is a placeholder for a more complex implementation later.
// The logic is currently inside Application::Run(). We will refactor it
// into this class in a later step.

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    void Start();
    void Stop();

private:
    bool m_IsRunning = false;
};

} // namespace Creative

#endif //CREATIVE_ENGINE_GAMELOOP_H
