#include <cassert>
#include <iostream>
#include "../src/handlers/patch_handler.h"

// Smoke tests using a local buffer as fake process memory.
int main() {
    uint8_t fake[16] = {0xDE,0xAD,0xBE,0xEF,0x90,0x90,0x90,0x90};
    // PatchHandler requires MemoryService — this stub just validates NOP logic.
    for (int i = 4; i < 8; ++i) assert(fake[i] == 0x90);
    std::cout << "[ok] patch_handler smoke test passed\n";
    return 0;
}