#include "tasks.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int totalCount = 0;
    std::string lineN;
    std::vector<std::string> grid;
    std::queue<std::vector<int>> positions;
    std::set<std::vector<int>> nextPositions;
    std::vector<int> nums;
    int lineNum = 0;

    while (getline(file, lineN)) {
        grid.push_back(lineN);
        int s = lineN.find('S');
        if (s != -1) {
            positions.push({s, lineNum});
            grid[lineNum][s] = '.';
        }
        lineNum++;
    }

    int totalSteps = 64;
    int ySize = grid.size();
    int xSize = grid[0].size();

    std::vector<int> startPoint = positions.front();
    std::vector<std::string> startGrid = grid;

    for (int i = 0; i < totalSteps; i++) {
        while (positions.size() > 0) {
            std::vector<int> currPos = positions.front();
            positions.pop();
            int x = currPos[0], y = currPos[1];
            grid[y][x] = '.';
            for (int j = 0; j < 4; j++) {
                std::vector<int> nextPos = addVectors(currPos, shifts[j]);
                if (inBounds(nextPos, xSize, ySize) && grid[nextPos[1]][nextPos[0]] != '#') {
                    nextPositions.insert(nextPos);
                    grid[nextPos[1]][nextPos[0]] = 'O';
                }
            }
        }
        positions = setToQueue(nextPositions);
        nextPositions.clear();
    }

    totalCount = sumGrid(grid, 'O');
    std::cout << "Part A: " << totalCount << std::endl;

    positions = std::queue<std::vector<int>>();
    positions.push(startPoint);
    std::vector<int> lagrangeCoeffs;

    totalSteps = xSize * 3;
    for (int i = 0; i < totalSteps; i++) {
        while (positions.size() > 0) {
            std::vector<int> currPos = positions.front();
            positions.pop();
            for (int j = 0; j < 4; j++) {
                std::vector<int> nextPos = addVectors(currPos, shifts[j]);
                int x = nextPos[0] % xSize, y = nextPos[1] % ySize;
                if (x < 0) { x += xSize; }
                if (y < 0) { y += ySize; }
                if (grid[y][x] != '#') {
                    nextPositions.insert(nextPos);
                }
            }
        }
        positions = setToQueue(nextPositions);
        nextPositions.clear();

        int iter = i - (xSize / 2 - 1);
        if (iter % xSize == 0) {
            lagrangeCoeffs.push_back(positions.size());
        }
    }

    int TotalIterations = 26501365;
    int xToFind = (TotalIterations - (xSize / 2)) / xSize;

    long long total = lagrange(xToFind + 1, lagrangeCoeffs);
    std::cout << "Part B: " << total << std::endl;

    return 0;
}
