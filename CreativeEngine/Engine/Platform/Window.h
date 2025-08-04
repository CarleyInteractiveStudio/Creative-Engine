#pragma once

namespace Creative {

// Forward-declare the Image class to avoid including the full header here.
// This is a good practice to reduce compilation times and header dependencies.
class Image;

class Window
{
public:
    Window(const char* title, int width, int height);
    ~Window();

    void Update();
    bool IsOpen() const;

    // Draws the content of an Image buffer to the window's client area.
    void DrawBuffer(const Image& image);

private:
    // Platform-specific window handle will go here.
    void* m_NativeWindow = nullptr;
    bool m_IsOpen = true;
};

} // namespace Creative
