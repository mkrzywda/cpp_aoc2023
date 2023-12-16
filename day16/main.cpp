#include <iostream>
#include "tasks.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::vector<std::string> maze = readInputFromFile(argv[1]);

    int resultA = solveMaze(0, 0, 0, maze);
    std::cout << "Result Part A: " << resultA << std::endl;

    int resultB = 0;
    int rows = maze.size();
    int cols = maze[0].size();

    for (int i = 0; i < rows; ++i) {
        resultB = std::max(resultB, std::max(solveMaze(i, 0, 0, maze), solveMaze(i, cols - 1, 1, maze)));
    }

    for (int i = 0; i < cols; ++i) {
        resultB = std::max(resultB, std::max(solveMaze(0, i, 2, maze), solveMaze(rows - 1, i, 3, maze)));
    }

    std::cout << "Result Part B: " << resultB << std::endl;

    return 0;
}
