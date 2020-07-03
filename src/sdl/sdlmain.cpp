#include <sstream>

#include "sdlmain.h"

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
    // Setup joystick input.
    // Setup input.
    // Load input config file.
    // Initialize audio.
    // Initialize video.
    // Load ROM.
    if (argc > 1) {
        cart = std::make_shared<Cartridge>(argv[0]);
        if (cart->imageValid()) {
            nes.insertCart(cart);
            nes.reset();
        } else {
            isExiting = true;
        }
    }
    // Start main loop.
    while (!isExiting) {
        
        nes.clock();
    }
    // Remove cartridge. Shut down.
    // Stop audio.
    // Stop joystick input.
    // Save input config.
    // Save app config.
    return 0;
}
