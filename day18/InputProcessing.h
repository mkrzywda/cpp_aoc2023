#pragma once
#include <vector>
#include <string>

template <typename T>
void processInput_partA(const std::string &inputPath, std::vector<std::pair<char, T>> &instructions);

template <typename T>
void processInput_partB(const std::string &inputPath, std::vector<std::pair<int, T>> &instructions);

