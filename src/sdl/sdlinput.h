#pragma once

#include <SDL2/SDL.h>

#include "stdio.h"

void sdlInputInit();
void sdlInputLoadConfig();
void sdlInputSaveConfig();
void sdlHandleKey(SDL_Event event);