#include "InputProcessing.h"
#include "Point.h"
#include <fstream>
#include <regex>

template <typename T>
void processInput_partA(const std::string &inputPath, std::vector<std::pair<char, T>> &instructions) {
    std::ifstream fIn(inputPath);
    std::string temp;

    while (getline(fIn, temp)) {
        if (temp.empty()) continue;
        instructions.emplace_back(temp[0], std::stoi(temp.substr(1)));
    }

    fIn.close();
}

template <typename T>
void processInput_partB(const std::string &inputPath, std::vector<std::pair<int, T>> &instructions) {
    std::ifstream fIn(inputPath);
    std::regex reg("#([0-9a-fA-F]{6})");
    std::smatch match;
    std::string temp;

    while (getline(fIn, temp)) {
        if (temp.empty()) continue;
        if (std::regex_search(temp, match, reg)) {
            temp = match[1];
            instructions.emplace_back(std::stoi(temp.substr(temp.size() - 1, temp.size())),
                                      std::stoll(temp.substr(0, temp.size() - 1), nullptr, 16));
        }
    }

    fIn.close();
}

// Explicit instantiation
template void processInput_partA(const std::string &inputPath, std::vector<std::pair<char, int>> &);
template void processInput_partA(const std::string &inputPath, std::vector<std::pair<char, long long>> &);
template void processInput_partB(const std::string &inputPath, std::vector<std::pair<int, int>> &);
template void processInput_partB(const std::string &inputPath, std::vector<std::pair<int, long long>> &);

