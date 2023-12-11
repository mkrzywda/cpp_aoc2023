#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tasks.h"

const int EXPANSION_A = 1;
const int EXPANSION_B = 1000000 - 1;

int main(int argc, char* argv[]) {
    std::vector<std::string> input;

    if (argc > 1) {
        std::string temp;
        std::ifstream fIn(argv[1]);
        while (std::getline(fIn, temp)) {
            if (temp.empty()) continue;
            input.push_back(temp);
        }
        fIn.close();
    } else {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    int result_a = calculateTotalDistance(input, EXPANSION_A);
    long long int result_b = calculateTotalDistance(input, EXPANSION_B);

    std::cout << "Part A Result: " << result_a << std::endl;
    std::cout << "Part B Result: " << result_b << std::endl;
    return 0;
}
