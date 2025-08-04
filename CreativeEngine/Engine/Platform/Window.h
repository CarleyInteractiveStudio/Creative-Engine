#pragma once

namespace Creative {

class Window
{
public:
    Window(const char* title, int width, int height);
    ~Window();

    void Update();
    bool IsOpen() const;

private:
    // Platform-specific window handle will go here.
    void* m_NativeWindow = nullptr;
    bool m_IsOpen = true;
};

} // namespace Creative
