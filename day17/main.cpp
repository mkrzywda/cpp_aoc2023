#include "tasks.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string temp;
    std::ifstream fIn(argv[1]);
    while (std::getline(fIn, temp)) {
        if (!temp.empty()) {
            grid.push_back(temp);
        }
    }
    fIn.close();

    std::cout << "Part A: " << findMinHeatLoss(grid) << std::endl;
    std::cout << "Part B: " << findMinHeatLossWithStepsLimit(grid) << std::endl;

    return 0;
}
