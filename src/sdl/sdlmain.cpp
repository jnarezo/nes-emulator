#include <sstream>

#include "sdlmain.h"
#include "sdlvideo.h"
#include "sdlinput.h"

#include "Bus.h"
#include "CPU.h"

static bool isExiting = false;

namespace {
    Bus nes;
    std::shared_ptr<Cartridge> cart;
}

int main(int argc, char* argv[])
{
    // Create directories.
    // Set default config options.
    // Load app config file.
    // Handle command-line args.
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;
    // Setup joystick input.
        // sdlInputLoadConfig();
    // Setup input.
    // Load input config file.
    // Initialize audio.
    // Initialize video.
    sdlVideoInit();
    // Load ROM.
    if (argc > 1) {
        cart = std::make_shared<Cartridge>(argv[0]);
        // if (cart->imageValid()) {
        if (1 != 0) {
            nes.insertCart(cart);
            nes.reset();
            sdlVideoSetTitle("Emulator - Test");
        } else {
            isExiting = true;
        }
    }
    // Start main loop.
    while (!isExiting) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isExiting = true;
            } else if (event.type == SDL_KEYDOWN) {
                sdlHandleKey(event);
            }
        }
        // nes.clock();
    }
    // Remove cartridge. Shut down.
    sdlVideoClose();
    // Stop audio.
    // Stop joystick input.
    SDL_Quit();
    // Save input config.
        // sdlInputSaveConfig();
    // Save app config.
    return 0;
}
