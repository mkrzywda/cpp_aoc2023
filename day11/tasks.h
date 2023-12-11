#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <string>

struct Point {
    int x, y;
};

int manhattanDistance(const Point& a, const Point& b);

void processInput(const std::vector<std::string>& input, int expansion, std::vector<Point>& galaxies);

long long int calculateTotalDistance(const std::vector<std::string>& input, int expansion);

#endif
