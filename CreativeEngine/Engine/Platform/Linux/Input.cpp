#include "Engine/Platform/Input.h"

// ===================================================================================
// TODO: This is a stub implementation.
//
// A proper implementation for Linux/X11 has an architectural dependency on the
// `Display*` handle, which is created and owned by the `Window` class. To make
// the static `Input` functions work, we would need to solve this.
//
// Common solutions include:
// 1. A static global pointer to the Display handle (simple, but not ideal).
// 2. An Application class that owns all platform systems and provides access.
// 3. Changing the Input class to be a non-static object that is initialized
//    with the necessary platform handles.
//
// For now, to keep moving forward, we provide non-functional stubs.
// This will be addressed in a future architectural refinement step.
// ===================================================================================

namespace Creative {

bool Input::IsKeyPressed(int keycode)
{
    return false;
}

bool Input::IsMouseButtonPressed(int button)
{
    return false;
}

void Input::GetMousePosition(float& x, float& y)
{
    x = 0.0f;
    y = 0.0f;
}

} // namespace Creative
