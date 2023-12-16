#include "tasks.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <functional>

const int directionX[] = {0, 0, 1, -1};
const int directionY[] = {1, -1, 0, 0};

std::vector<std::string> readInputFromFile(const char* filePath) {
    freopen(filePath, "r", stdin);
    std::vector<std::string> grid;
    std::string line;
    while (getline(std::cin, line)) {
        grid.push_back(line);
    }
    return grid;
}

int solveMaze(int startX, int startY, int startDir, const std::vector<std::string>& maze) {
    int rows = maze.size();
    int cols = maze[0].size();

    std::vector<std::vector<int>> visited(rows, std::vector<int>(cols));
    std::queue<std::tuple<int, int, int>> q;
    q.push({startX, startY, startDir});

    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop();

        if (visited[x][y] & (1 << d))
            continue;

        visited[x][y] |= (1 << d);

        std::vector<int> dirs;

        if (maze[x][y] == '/')
            dirs = {3 - d};
        else if (maze[x][y] == '\\')
            dirs = {(d + 2) % 4};
        else if (maze[x][y] == '-' && (d == 2 || d == 3))
            dirs = {0, 1};
        else if (maze[x][y] == '|' && (d == 0 || d == 1))
            dirs = {2, 3};
        else
            dirs = {d};

        for (auto dir : dirs) {
            int nx = x + directionX[dir];
            int ny = y + directionY[dir];

            if (nx < 0 || ny < 0 || nx >= rows || ny >= cols)
                continue;

            q.push({nx, ny, dir});
        }
    }

    int count = 0;

    for (const auto& row : visited) {
        for_each(row.begin(), row.end(), [&count](int cell) {
            count += (cell > 0);
        });
    }

    return count;
}
