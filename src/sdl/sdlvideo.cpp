#include <SDL2/SDL.h>

#include "sdlvideo.h"

static SDL_Window *window;

namespace {
    constexpr int WIDTH = 256;
    constexpr int HEIGHT = 240;
}

void sdlVideoInit()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH * 2,
        HEIGHT * 2,
        windowFlags);
}

void sdlVideoSetTitle(const char *title)
{
    SDL_SetWindowTitle(window, title);
}

void sdlVideoClose()
{
    SDL_DestroyWindow(window);
}