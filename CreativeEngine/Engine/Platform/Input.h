#pragma once

namespace Creative {

class Input
{
public:
    // For now, these will be static methods.
    // A more robust system might use a singleton or be part of an application class.
    static bool IsKeyPressed(int keycode);
    static bool IsMouseButtonPressed(int button);
    static void GetMousePosition(float& x, float& y);
};

} // namespace Creative
