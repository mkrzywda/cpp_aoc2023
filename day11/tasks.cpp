#include "tasks.h"
#include <algorithm>
#include <unordered_set>

const int EXPANSION_A = 1;
const int EXPANSION_B = 1000000 - 1;

int manhattanDistance(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void processInput(const std::vector<std::string>& input, int expansion, std::vector<Point>& galaxies) {
    std::vector<bool> columnEmpty(input[0].size(), true);
    std::unordered_set<int> emptyRows, emptyColumns;

    for (int i = 0; i < input.size(); i++) {
        if (std::all_of(input[i].begin(), input[i].end(), [](char c) { return c == '.'; }))
            emptyRows.insert(i);

        for (int j = 0; j < input[i].size(); j++)
            if (input[i][j] == '#')
                columnEmpty[j] = false;
    }

    for (int i = 0; i < columnEmpty.size(); i++)
        if (columnEmpty[i]) emptyColumns.insert(i);

    int yOffset = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (emptyRows.find(i) != emptyRows.end()) yOffset += expansion;

        int xOffset = 0;
        for (int j = 0; j < input[i].size(); ++j) {
            if (emptyColumns.find(j) != emptyColumns.end()) xOffset += expansion;

            if (input[i][j] == '#') {
                galaxies.push_back({j + xOffset, i + yOffset});
            }
        }
    }
}

long long int calculateTotalDistance(const std::vector<std::string>& input, int expansion) {
    std::vector<Point> galaxies;
    processInput(input, expansion, galaxies);

    unsigned long long sum = 0;
    for (int i = 0; i < galaxies.size() - 1; ++i)
        for (int j = i + 1; j < galaxies.size(); ++j)
            sum += manhattanDistance(galaxies[i], galaxies[j]);

    return sum;
}
