#include "GeometryFunctions.h"
#include "InputProcessing.h"
#include <iostream>

template <typename T>
void part(const std::string &inputPath, const std::string &partName);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    part<int>(input, "Part A");
    part<long long>(input, "Part B");

    return 0;
}

template <typename T>
void part(const std::string &inputPath, const std::string &partName) {
    if (partName == "Part A") {
        std::vector<std::pair<char, T>> instructions;
        processInput_partA<T>(inputPath, instructions);

        auto vertices = processInstructions_partA<T>(instructions);
        std::cout << partName << " Result: " << area_partA(vertices) << std::endl;
    } else {
        std::vector<std::pair<int, T>> instructions;
        processInput_partB<T>(inputPath, instructions);

        auto vertices = processInstructions_partB<T>(instructions);
        std::cout << partName << " Result: " << area_partB(vertices) << std::endl;
    }
}
