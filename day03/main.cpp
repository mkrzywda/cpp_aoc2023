#include <iostream>
#include "tasks.h"

int main(int argc, char* argv[]) {
    std::string input;
    if (argc > 1) {
        input = argv[1];
    } else {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    try {
        std::vector<std::string> fileVec = file2Vec(input);

        std::cout << "Part A: " << part_a(fileVec) << std::endl;
        std::cout << "Part B: " << part_b(fileVec) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
