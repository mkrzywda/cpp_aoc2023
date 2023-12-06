// main.cpp
#include "tasks.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::string input;

    if (argc > 1) {
        input = argv[1];
    } else {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream fIn(input);
    if (!fIn.is_open()) {
        std::cerr << "Error opening input file: " << input << std::endl;
        return 1;
    }

    std::vector<std::string> inputLines;
    std::string temp;

    while (std::getline(fIn, temp)) {
        if (!temp.empty()) {
            inputLines.push_back(temp);
        }
    }

    fIn.close();

    part_a(inputLines);
    part_b(inputLines);

    return 0;
}
