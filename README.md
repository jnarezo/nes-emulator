# A WIP basic cycle-inaccurate NES emulator.
This is a very WIP NES emulator that was a project for me to gain a better grasp
of C++, CPUs, and Assembly, as well as some new features introduced in
C++11, C++14, and C++17.

## Features
There are a several features of the emulator that has been, for the most part,
completed, but may need additional functionality to interact with the rest of
the console.

This emulator focuses on using C++ object-oriented programming to encapsulate
various aspects of the console. For example, CPU implementation is separate
from PPU/GPU implementation. The NES emulation itself is separate from
any system-specific GUI implementation or user interaction from the OS.

Some things that are functional / complete:
- CPU (6502 microprocessor - includes all 56 instructions + 8 addressing modes)
- PPU (Pixel Processing Unit)
- Mapper (000)
- Cartridge (RAM + loading .nes ROMs)

What still could be done:
- A desktop GUI / window (SDL2)
- APU (Audio Processing Unit)
- Input / Controllers
- Other mappers (001, 002, ...)

## Credits
Thanks to Javidx9 (olc), the Mesen emu team, and the Nesdev community.
Without their help, I wouldn't have had as great of an understanding and
knowledge of the NES, console emulation, and the work it involves as I do now.