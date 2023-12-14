// main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "tasks.h"

const size_t MY_CYCLES = 1000000000;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::vector<std::string> input;
    std::string temp;
    std::ifstream fIn(argv[1]);
    while (std::getline(fIn, temp)) {
        if (!temp.empty()) {
            input.push_back(temp);
        }
    }
    fIn.close();

    int loadA = part_a(input);
    std::cout << "Part A: " << loadA << std::endl;

    int loadB = part_b(input, MY_CYCLES);
    std::cout << "Part B: " << loadB << std::endl;

    return 0;
}
