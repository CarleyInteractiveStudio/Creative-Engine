#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "editor/Editor.h"

int main(int argc, char* argv[]) {
    Editor editor;
    editor.run();
    return 0;
}
