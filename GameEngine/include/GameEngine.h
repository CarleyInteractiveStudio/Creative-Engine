#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "SDL.h"
#include "glad/glad.h" // Include glad for OpenGL functions

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    SDL_Window* m_Window;
    SDL_GLContext m_GLContext; // OpenGL context
    bool m_IsRunning;
};

#endif // GAMEENGINE_H
