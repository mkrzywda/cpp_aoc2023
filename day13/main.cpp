#include "tasks.h"
#include <iostream>
#include <fstream>

int main() {
    std::vector<std::vector<std::string>> input(1);
    std::string temp;
    std::ifstream fIn("/home/mkrzywda/cpp_aoc2023/day13/input_day13.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) {
            input.resize(input.size() + 1);
            continue;
        }
        input[input.size() - 1].push_back(temp);
    }
    fIn.close();

    int result_a = solver_part_a(input);

    std::cout << "Part A Result: " << result_a << std::endl;

    int result_b = solver_part_b();

    std::cout << "Part B Result: " << result_b << std::endl;

    return 0;
}
