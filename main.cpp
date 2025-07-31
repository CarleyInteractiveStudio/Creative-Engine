#include "Engine/Application.h"

int main(int argc, char* argv[]) {
    // The main entry point of the engine.
    // This creates the application, runs it, and then cleans up.

    Creative::Application app;

    app.Init();
    app.Run();
    app.Shutdown();

    return 0;
}
