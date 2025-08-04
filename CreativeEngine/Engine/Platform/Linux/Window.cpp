#include "Engine/Platform/Window.h"
#include "Engine/Core/Log.h"

// X11 is the low-level windowing system on Linux. We include its main header.
#include <X11/Xlib.h>

namespace Creative {

// We need a place to store the platform-specific window data (the X11 Display and Window handles).
// This struct is only visible within this .cpp file, hiding the implementation details
// from the rest of the engine. The void* in the header points to this.
struct PlatformWindowHandles
{
    Display* display = nullptr;
    // We must use the global namespace `::` to refer to the X11 `Window` type,
    // to avoid collision with our own `Creative::Window` class.
    ::Window x11_window;
    Atom wmDeleteMessage;
};

// --- Window Constructor ---
// This is where we connect to the OS and create a window.
Window::Window(const char* title, int width, int height)
{
    // The m_NativeWindow from the header is a void pointer, so we cast it to our struct.
    m_NativeWindow = new PlatformWindowHandles();
    auto* data = static_cast<PlatformWindowHandles*>(m_NativeWindow);

    // 1. Connect to the X Server
    data->display = XOpenDisplay(NULL);
    if (data->display == NULL)
    {
        Log::Core_Error("Could not open X11 display. Is the X server running?");
        m_IsOpen = false;
        return;
    }

    int screen = DefaultScreen(data->display);

    // 2. Create the Window
    data->x11_window = XCreateSimpleWindow(data->display, RootWindow(data->display, screen),
                                           10, 10, width, height, 1,
                                           BlackPixel(data->display, screen),
                                           WhitePixel(data->display, screen));

    // 3. Set properties and make it visible
    XStoreName(data->display, data->x11_window, title);
    // We want to listen for keyboard, mouse, and other standard events.
    XSelectInput(data->display, data->x11_window, ExposureMask | KeyPressMask | ButtonPressMask);
    // Put the window on the screen.
    XMapWindow(data->display, data->x11_window);

    // 4. Register for the 'close' button event from the window manager
    data->wmDeleteMessage = XInternAtom(data->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(data->display, data->x11_window, &data->wmDeleteMessage, 1);

    m_IsOpen = true;
    Log::Core_Info("Linux (X11) Window created successfully.");
}

// --- Window Destructor ---
// Cleans up the OS resources.
Window::~Window()
{
    auto* data = static_cast<PlatformWindowHandles*>(m_NativeWindow);
    if (data && data->display)
    {
        XDestroyWindow(data->display, data->x11_window);
        XCloseDisplay(data->display);
        Log::Core_Info("X11 Window destroyed.");
    }
    delete data;
}

// --- Window Update ---
// This is called every frame to process messages from the OS.
void Window::Update()
{
    auto* data = static_cast<PlatformWindowHandles*>(m_NativeWindow);
    XEvent e;

    // Check for pending events from the X server and process them.
    // In a more advanced engine, this would be a more complex event dispatch system.
    while (XPending(data->display) > 0)
    {
        XNextEvent(data->display, &e);

        // We only care about the close event for now.
        if (e.type == ClientMessage)
        {
            if (static_cast<Atom>(e.xclient.data.l[0]) == data->wmDeleteMessage)
            {
                m_IsOpen = false;
            }
        }
    }
}

bool Window::IsOpen() const
{
    return m_IsOpen;
}

} // namespace Creative
