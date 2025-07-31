#ifndef CREATIVE_ENGINE_INPUTMANAGER_H
#define CREATIVE_ENGINE_INPUTMANAGER_H

#include <SDL2/SDL_scancode.h>
#include <unordered_map>

union SDL_Event;

namespace Creative {

class InputManager {
public:
    // Call once at the beginning of each frame, before processing events.
    static void PrepareForNewFrame();
    // Process a single event from the SDL event queue.
    static void ProcessEvent(const SDL_Event& event);

    // Keyboard state checks
    static bool IsKeyDown(SDL_Scancode key);
    static bool IsKeyPressed(SDL_Scancode key);
    static bool IsKeyReleased(SDL_Scancode key);

    // Mouse state checks
    static bool IsMouseButtonDown(int button);
    static bool IsMouseButtonPressed(int button);
    static bool IsMouseButtonReleased(int button);
    static void GetMousePosition(int* x, int* y);
    static void GetMouseDelta(int* dx, int* dy);

private:
    InputManager() {} // Static class

    // Keyboard state
    static std::unordered_map<SDL_Scancode, bool> s_KeyPressed;
    static std::unordered_map<SDL_Scancode, bool> s_KeyReleased;
    static const Uint8* s_CurrentKeyState;

    // Mouse state
    static std::unordered_map<int, bool> s_MouseButtonPressed;
    static std::unordered_map<int, bool> s_MouseButtonReleased;
    static Uint32 s_CurrentMouseButtonState;
    static int s_MouseX, s_MouseY;
    static int s_MouseDeltaX, s_MouseDeltaY;
};

} // namespace Creative

#endif //CREATIVE_ENGINE_INPUTMANAGER_H
