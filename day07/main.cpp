#include "tasks.h"

int main(int argc, char* argv[]) {
    std::string input;

    if (argc > 1) {
        input = argv[1];
    }
    else {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(input);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file: " << input << std::endl;
        return 1;
    }

    std::vector<std::tuple<std::string, int, HandStrength>> hands;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int value;
        ss >> line >> value;
        hands.emplace_back(line, value, HandStrength::HIGHCARD);
    }
    inputFile.close();

    part_a(&hands);
    part_b(&hands);

    return 0;
}
