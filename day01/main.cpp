#include "tasks.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string input;
    if (argc > 1) {
        input = argv[1];
    }

    std::cout << part_a(input) << '\n';
    std::cout << part_b(input) << '\n';

    return 0;
}
