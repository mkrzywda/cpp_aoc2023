#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <string>

struct GridInfo {
    std::vector<std::string> grid;
    int n;
    int m;
};

const int INF = -1000000;

int findMaxSteps(int x, int y, const GridInfo& gridInfo, std::vector<std::vector<bool>>& vis);
int findMaxStepsNoDirection(int x, int y, const GridInfo& gridInfo, std::vector<std::vector<bool>>& vis);

#endif