#include "tasks.h"
#include <iostream>
#include <fstream>

bool isPattern(const std::vector<std::string>& pattern, int index) {
    for (int i = 0; i < pattern.size(); ++i) {
        if (i + index < pattern.size() && index - i - 1 >= 0 && pattern[i + index] != pattern[index - i - 1]) {
            return false;
        }
    }
    return true;
}

int findPatternStartIndex(const std::vector<std::string>& pattern) {
    for (int i = 1; i < pattern.size(); ++i) {
        if (pattern[i] == pattern[i - 1]) {
            if (isPattern(pattern, i)) {
                return i;
            }
        }
    }
    return -1;
}

std::vector<std::string> rotateRight(const std::vector<std::string>& original) {
    int rows = original.size();
    int cols = original[0].size();
    std::vector<std::string> rotated(cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j] = original[i][j] + rotated[j];
        }
    }

    return rotated;
}

int solver_part_a(const std::vector<std::vector<std::string>>& input) {
    int total = 0;
    for (const auto& pattern : input) {
        int result = findPatternStartIndex(pattern);

        if (result == -1) {
            auto rotatedPattern = rotateRight(pattern);
            total += findPatternStartIndex(rotatedPattern);
        } else {
            total += result * 100;
        }
    }

    return total;
}

bool compareRowsWithSmudge(std::vector<std::string>& grid, int r1, int r2, bool& smudge) {
    for (int i = 0; i < grid[r1].length(); i++) {
        if (grid[r1][i] != grid[r2][i]) {
            if (!smudge) {
                smudge = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool compareColumnsWithSmudge(std::vector<std::string>& grid, int c1, int c2, bool& smudge) {
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i][c1] != grid[i][c2]) {
            if (!smudge) {
                smudge = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

int solver_part_b() {
    std::string line;
    int total = 0;

    std::ifstream inputFile("/home/mkrzywda/cpp_aoc2023/day13/input_day13.txt");

    while (!inputFile.eof()) {
        std::vector<std::string> grid;
        while (getline(inputFile, line) && !line.empty()) {
            grid.push_back(line);
        }

        bool foundReflection = false;

        for (int i = 0; i < grid.size() - 1; i++) {
            bool smudge = false;
            if (compareRowsWithSmudge(grid, i, i + 1, smudge)) {
                int up = i - 1, down = i + 2;
                bool reflection = true;
                while (up >= 0 && down < grid.size()) {
                    if (!compareRowsWithSmudge(grid, up, down, smudge)) {
                        reflection = false;
                        break;
                    }
                    up--;
                    down++;
                }
                if (reflection && smudge) {
                    foundReflection = true;
                    total += (100 * (i + 1));
                    break;
                }
            }
        }

        if (foundReflection) {
            continue;
        }

        for (int i = 0; i < grid[0].length() - 1; i++) {
            bool smudge = false;
            if (compareColumnsWithSmudge(grid, i, i + 1, smudge)) {
                int leftIndex = i - 1, rightIndex = i + 2;
                bool reflection = true;
                while (leftIndex >= 0 && rightIndex < grid[0].length()) {
                    if (!compareColumnsWithSmudge(grid, leftIndex, rightIndex, smudge)) {
                        reflection = false;
                        break;
                    }
                    leftIndex--;
                    rightIndex++;
                }
                if (reflection && smudge) {
                    foundReflection = true;
                    total += (i + 1);
                    break;
                }
            }
        }
    }

    inputFile.close();

    return total;
}
