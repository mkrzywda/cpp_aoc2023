#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tasks.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::string input;
    std::ifstream inputFile(argv[1]);
    std::getline(inputFile, input);
    inputFile.close();

    int currentValue = 0, sum = 0;
    for (auto &c : input) {
        if (c == ',') {
            sum += currentValue;
            currentValue = 0;
            continue;
        }

        currentValue += c;
        currentValue *= 17;
        currentValue %= 256;
    }
    sum += currentValue;

    std::cout << "Part A Result: " << sum << std::endl;

    std::string current;
    std::vector<std::vector<std::pair<std::string, int>>> boxes(256);
    for (int c = 0; c < input.size(); ++c) {
        if (input[c] == ',') {
            current = "";
            continue;
        } else if (input[c] == '=') {
            updateOrInsertKeyValue(boxes[calculateStringHash(current)], current, input[c + 1] - '0');
        } else if (input[c] == '-') {
            removeKeyValuePair(boxes[calculateStringHash(current)], current);
        }
        current += input[c];
    }

    std::cout << "Part B Result: " << calculateFocusingPower(boxes) << std::endl;

    return 0;
}
