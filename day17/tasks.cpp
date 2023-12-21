#include "tasks.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <climits>

Point Point::operator+(const Point& other) const {
    return {x + other.x, y + other.y};
}

const Point directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

State::State(Point pos, int d, int s, int h) : position(pos), dir(d), steps(s), heat(h) {}

bool State::operator>(const State& other) const {
    return heat > other.heat;
}

bool inBounds(const Point& point, int rows, int cols) {
    return point.x >= 0 && point.x < rows && point.y >= 0 && point.y < cols;
}

int findMinHeatLoss(const std::vector<std::string>& grid) {
    std::vector<std::vector<std::vector<std::vector<bool>>>> visited(
        (int)grid.size(), std::vector<std::vector<std::vector<bool>>>(
            (int)grid[0].size(), std::vector<std::vector<bool>>(
                4, std::vector<bool>(4, false))));

    std::priority_queue<State, std::vector<State>, std::greater<>> frontier;
    frontier.push(State{{0, 0}, -1, 0, 0});

    int heatLoss = INT_MAX;
    while (!frontier.empty()) {
        auto current = frontier.top();
        frontier.pop();

        if (current.position.x == (int)grid.size() - 1 && current.position.y == (int)grid[0].size() - 1) {
            heatLoss = std::min(heatLoss, current.heat);
            break;
        }

        for (int i = 0; i < 4; ++i) {
            if (current.dir != -1 && (i == (current.dir + 2) % 4)) continue;

            Point next = current.position + directions[i];
            int totalSteps = (i == current.dir) ? current.steps + 1 : 1;
            if (inBounds(next, (int)grid.size(), (int)grid[0].size()) && totalSteps <= 3 && !visited[next.y][next.x][i][totalSteps]) {
                int newHeat = current.heat + (next.y == 0 && next.x == 0 ? 0 : grid[next.y][next.x] - '0');
                visited[next.y][next.x][i][totalSteps] = true;
                frontier.emplace(next, i, totalSteps, newHeat);
            }
        }
    }

    return heatLoss;
}

int findMinHeatLossWithStepsLimit(const std::vector<std::string>& grid) {
    std::vector<std::vector<std::vector<std::vector<bool>>>> visited(
        (int)grid.size(), std::vector<std::vector<std::vector<bool>>>(
            (int)grid[0].size(), std::vector<std::vector<bool>>(
                4, std::vector<bool>(11, false))));
    std::priority_queue<State, std::vector<State>, std::greater<>> frontier;
    frontier.push(State({0, 0}, -1, 0, 0));

    int heatLoss = INT_MAX;
    while (!frontier.empty()) {
        State current = frontier.top();
        frontier.pop();

        if (current.position.x == (int)grid.size() - 1 && current.position.y == (int)grid[0].size() - 1) {
            heatLoss = std::min(heatLoss, current.heat);
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            if (current.dir != -1 && (i == (current.dir + 2) % 4)) continue;

            int newHeat = current.heat;
            bool validMove = true;
            int stepsToMove = (current.dir == i) ? 1 : 4;

            Point next = current.position;
            for (int step = 1; step <= stepsToMove; ++step) {
                next = next + directions[i];
                if (!inBounds(next, (int)grid.size(), (int)grid[0].size())) {
                    validMove = false;
                    break;
                }
                newHeat += grid[next.x][next.y] - '0';
            }

            int totalSteps = current.dir == i ? current.steps + stepsToMove : stepsToMove;
            if (validMove && totalSteps <= 10 && !visited[next.x][next.y][i][totalSteps]) {
                visited[next.x][next.y][i][totalSteps] = true;
                frontier.emplace(next, i, totalSteps, newHeat);
            }
        }
    }

    return heatLoss;
}
