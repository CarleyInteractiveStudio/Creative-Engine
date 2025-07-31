#include "InputManager.h"
#include <SDL2/SDL.h>

namespace Creative {

// Initialize static members
std::unordered_map<SDL_Scancode, bool> InputManager::s_KeyPressed;
std::unordered_map<SDL_Scancode, bool> InputManager::s_KeyReleased;
const Uint8* InputManager::s_CurrentKeyState = nullptr;

std::unordered_map<int, bool> InputManager::s_MouseButtonPressed;
std::unordered_map<int, bool> InputManager::s_MouseButtonReleased;
Uint32 InputManager::s_CurrentMouseButtonState = 0;
int InputManager::s_MouseX = 0;
int InputManager::s_MouseY = 0;
int InputManager::s_MouseDeltaX = 0;
int InputManager::s_MouseDeltaY = 0;


void InputManager::PrepareForNewFrame() {
    // Clear single-frame event states
    s_KeyPressed.clear();
    s_KeyReleased.clear();
    s_MouseButtonPressed.clear();
    s_MouseButtonReleased.clear();
    s_MouseDeltaX = 0;
    s_MouseDeltaY = 0;

    // Update the state snapshots
    s_CurrentKeyState = SDL_GetKeyboardState(NULL);
    s_CurrentMouseButtonState = SDL_GetMouseState(&s_MouseX, &s_MouseY);
}

void InputManager::ProcessEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            // We only care about the first press, not repeats
            if (event.key.repeat == 0) {
                s_KeyPressed[event.key.keysym.scancode] = true;
            }
            break;
        case SDL_KEYUP:
            s_KeyReleased[event.key.keysym.scancode] = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            s_MouseButtonPressed[event.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            s_MouseButtonReleased[event.button.button] = true;
            break;
        case SDL_MOUSEMOTION:
            s_MouseDeltaX = event.motion.xrel;
            s_MouseDeltaY = event.motion.yrel;
            break;
    }
}

// ---- Keyboard ----
bool InputManager::IsKeyDown(SDL_Scancode key) {
    if (s_CurrentKeyState == nullptr) {
        return false;
    }
    return s_CurrentKeyState[key];
}

bool InputManager::IsKeyPressed(SDL_Scancode key) {
    return s_KeyPressed.count(key);
}

bool InputManager::IsKeyReleased(SDL_Scancode key) {
    return s_KeyReleased.count(key);
}

// ---- Mouse ----
bool InputManager::IsMouseButtonDown(int button) {
    return (s_CurrentMouseButtonState & SDL_BUTTON(button));
}

bool InputManager::IsMouseButtonPressed(int button) {
    return s_MouseButtonPressed.count(button);
}

bool InputManager::IsMouseButtonReleased(int button) {
    return s_MouseButtonReleased.count(button);
}

void InputManager::GetMousePosition(int* x, int* y) {
    *x = s_MouseX;
    *y = s_MouseY;
}

void InputManager::GetMouseDelta(int* dx, int* dy) {
    *dx = s_MouseDeltaX;
    *dy = s_MouseDeltaY;
}

} // namespace Creative
