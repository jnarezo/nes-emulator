#include "sdlvideo.h"

static SDL_Window *window;

void sdlVideoInit()
{
    uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        512,
        480,
        windowFlags);
}

void sdlVideoSetTitle(const char *title)
{
    SDL_SetWindowTitle(window, title);
}