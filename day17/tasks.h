#pragma once

#include <vector>
#include <string>

struct Point {
    int x, y;

    Point operator+(const Point& other) const;
};

extern const Point directions[4];

struct State {
    Point position;
    int dir, steps, heat;

    State(Point pos, int d, int s, int h);

    bool operator>(const State& other) const;
};

bool inBounds(const Point& point, int rows, int cols);

int findMinHeatLoss(const std::vector<std::string>& grid);
int findMinHeatLossWithStepsLimit(const std::vector<std::string>& grid);
