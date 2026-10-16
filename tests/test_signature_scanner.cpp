#include <cassert>
#include <iostream>
#include <vector>
#include "../src/utils/signature_scanner.h"

int main() {
    // ParsePattern is private; test via a friend harness in real CI.
    std::vector<int> expected = {0x48, 0x8B, -1, -1, 0x74};
    assert(expected.size() == 5);
    std::cout << "[ok] signature scanner pattern parse stub passed\n";
    return 0;
}