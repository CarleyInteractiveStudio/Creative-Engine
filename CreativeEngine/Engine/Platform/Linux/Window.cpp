#include "Engine/Platform/Window.h"
#include "Engine/Renderer/Image.h" // We need the Image and Color definitions
#include "Engine/Core/Log.h"

// X11 is the low-level windowing system on Linux. We include its main header.
#include <X11/Xlib.h>
#include <X11/Xutil.h> // For XDestroyImage
#include <vector> // For the temporary buffer in DrawBuffer

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
    GC graphics_context; // Graphics Context for drawing
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

    // 3. Create a Graphics Context
    data->graphics_context = XCreateGC(data->display, data->x11_window, 0, NULL);


    // 4. Set properties and make it visible
    XStoreName(data->display, data->x11_window, title);
    // We want to listen for keyboard, mouse, and other standard events.
    XSelectInput(data->display, data->x11_window, ExposureMask | KeyPressMask | ButtonPressMask);
    // Put the window on the screen.
    XMapWindow(data->display, data->x11_window);

    // 5. Register for the 'close' button event from the window manager
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
        XFreeGC(data->display, data->graphics_context);
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

// --- Window DrawBuffer ---
// This is where we copy our software-rendered image to the screen.
void Window::DrawBuffer(const Image& image)
{
    auto* data = static_cast<PlatformWindowHandles*>(m_NativeWindow);
    if (!data || !data->display)
    {
        return;
    }

    const unsigned int width = image.GetWidth();
    const unsigned int height = image.GetHeight();
    const Color* pixel_data = image.GetData();

    // X11's XPutImage can be picky about pixel formats. The most reliable way
    // is to use a 32-bit BGRX or BGRA format that matches the screen's default visual.
    // We will convert our 24-bit RGB data into a 32-bit buffer.
    // We create this buffer on the heap to avoid stack overflow for large images.
    auto buffer = std::vector<unsigned int>(width * height);
    for (unsigned int i = 0; i < width * height; ++i)
    {
        // Pack the RGB values into a 32-bit integer.
        // The memory layout is 0x00RRGGBB, but X11 on a little-endian system
        // will interpret this as B, G, R, Alpha(unused).
        buffer[i] = (pixel_data[i].r << 16) | (pixel_data[i].g << 8) | pixel_data[i].b;
    }

    // Create an XImage structure which acts as a wrapper around our pixel buffer.
    XImage* x_image = XCreateImage(data->display,
                                   DefaultVisual(data->display, DefaultScreen(data->display)),
                                   DefaultDepth(data->display, DefaultScreen(data->display)),
                                   ZPixmap, 0, (char*)buffer.data(), width, height, 32, 0);

    if (x_image)
    {
        // Copy the image data to the window.
        XPutImage(data->display, data->x11_window, data->graphics_context, x_image,
                  0, 0, 0, 0, width, height);

        // XDestroyImage also frees the buffer `x_image->data` if it was allocated by Xlib,
        // but we allocated it ourselves with std::vector. So we must set the data pointer
        // to null before destroying the XImage wrapper to prevent a double-free.
        x_image->data = nullptr;
        XDestroyImage(x_image);
    }

    // Ensure the drawing commands are sent to the X server immediately.
    XFlush(data->display);
}

} // namespace Creative
