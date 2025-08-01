#ifndef CREATIVE_ENGINE_WINDOW_H
#define CREATIVE_ENGINE_WINDOW_H

#include <string>

// Forward declaration for the SDL_Window struct from the SDL library.
// This avoids needing to include the full SDL.h header in our public Window.h.
struct SDL_Window;
typedef void* SDL_GLContext;

namespace Creative {

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    // Initializes the window system and creates the window.
    bool Init();
    // Destroys the window and shuts down the window system.
    void Shutdown();

    // Swaps the front and back buffers to display the rendered frame.
    void SwapBuffers();

    // Provides access to the underlying native window handle if needed.
    SDL_Window* GetNativeWindow() const { return m_SdlWindow; }
    SDL_GLContext GetGLContext() const { return m_GlContext; }

private:
    std::string m_Title;
    int m_Width;
    int m_Height;

    SDL_Window* m_SdlWindow = nullptr;
    SDL_GLContext m_GlContext = nullptr;
};

} // namespace Creative

#endif //CREATIVE_ENGINE_WINDOW_H
