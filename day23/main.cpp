#include <iostream>
#include <fstream>
#include "tasks.h"

int countLines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return -1;
    }

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++count;
    }

    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    int numLines = countLines(inputFileName);
    if (numLines == -1) {
        return 1;
    }

    std::cout << "Number of lines in the input file: " << numLines << std::endl;

    std::ifstream input_file(inputFileName);
    if (!input_file.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    GridInfo gridInfo;
    gridInfo.n = numLines;
    gridInfo.grid.resize(gridInfo.n);

    for (int i = 0; i < gridInfo.n; i++) {
        if (!(input_file >> gridInfo.grid[i])) {
            std::cerr << "Error: Unable to read data from the input file." << std::endl;
            return 1;
        }
    }

    gridInfo.m = gridInfo.grid[0].size();
    std::vector<std::vector<bool>> vis(gridInfo.n, std::vector<bool>(gridInfo.m, false));

    std::cout << findMaxSteps(0, 1, gridInfo, vis) << std::endl;
    std::cout << findMaxStepsNoDirection(0, 1, gridInfo, vis) << std::endl; // It may take some time

    return 0;
}
