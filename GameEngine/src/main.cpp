#include "GameEngine.h"

int main(int argc, char* argv[]) {
    GameEngine engine;
    if (engine.Initialize()) {
        engine.Run();
    }
    engine.Shutdown();
    return 0;
}

