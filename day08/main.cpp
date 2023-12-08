#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <regex>
#include <numeric>
#include <stdexcept>
#include "tasks.h"

int main(int argc, char* argv[]) {
    try {
        std::string input;

        if (argc > 1) {
            input = argv[1];
        } else {
            std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
            return 1;
        }

        auto nodes_partA = readNodes(input);
        std::string instructions;
        std::ifstream inputFile(input);
        std::getline(inputFile, instructions);
        inputFile.close();

        int steps_partA = navigate(nodes_partA, instructions);
        std::cout << "Part A Result: " << steps_partA << std::endl;

        std::vector<std::string> startingNodes;
        auto nodes_partB = readNodes_partB(input, startingNodes);

        auto steps_partB = navigate_part_B(nodes_partB, startingNodes, instructions);

        long long lcm = steps_partB[0];
        for (int i = 1; i < steps_partB.size(); ++i) {
            lcm = std::lcm(lcm, static_cast<long long>(steps_partB[i]));
        }

        std::cout << "Part B Result: " << lcm << std::endl;

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
