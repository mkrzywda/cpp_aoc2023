#include "tasks.h"
#include <iostream>
const std::vector<std::vector<int>> shifts = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

std::vector<int> addVectors(const std::vector<int>& first, const std::vector<int>& second) {
    std::vector<int> temp;
    for (int i = 0; i < first.size(); i++) {
        temp.push_back(first[i] + second[i]);
    }
    return temp;
}

void drawVector(const std::vector<std::string>& input) {
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            std::cout << input[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool inBounds(const std::vector<int>& coords, int vectorXSize, int vectorYSize) {
    int x = coords[0], y = coords[1];
    if (x >= 0 && x < vectorXSize && y >= 0 && y < vectorYSize) {
        return true;
    }
    return false;
}

bool isANumber(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

std::vector<int> numsFromString(const std::string& line, int pos) {
    std::vector<int> temp;
    int space = 0;
    while (space != -1) {
        space = line.find(' ', pos);
        temp.push_back(std::stoull(line.substr(pos, space - pos)));
        pos = space + 1;
    }
    return temp;
}

std::queue<std::vector<int>> setToQueue(const std::set<std::vector<int>>& input) {
    std::queue<std::vector<int>> temp;
    std::set<std::vector<int>>::iterator it;
    for (it = input.begin(); it != input.end(); ++it) {
        temp.push(*it);
    }
    return temp;
}

int sumGrid(const std::vector<std::string>& grid, char toCount) {
    int temp = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == toCount) {
                temp++;
            }
        }
    }
    return temp;
}

std::vector<std::string> makeBigGrid(const std::vector<std::string>& grid, int scaleFactor) {
    std::vector<std::string> bigGrid;
    int numIters = 2 * scaleFactor + 1;
    int ySize = grid.size();
    for (int i = 0; i < numIters; i++) {
        for (int j = 0; j < grid.size(); j++) {
            bigGrid.push_back(grid[j]);
            for (int k = 1; k < numIters; k++) {
                bigGrid[i * ySize + j] += grid[j];
            }
        }
    }
    return bigGrid;
}

long long lagrange(int in, const std::vector<int>& lagrangeCoeffs) {
    long long x = static_cast<long long>(in);
    long long total = 0;
    for (int i = 0; i < lagrangeCoeffs.size(); i++) {
        long long temp = lagrangeCoeffs[i];
        for (int j = 0; j < lagrangeCoeffs.size(); j++) {
            if (j != i) {
                temp *= (x - j - 1) / (i - j);
            }
        }
        total += temp;
    }
    return total;
}
