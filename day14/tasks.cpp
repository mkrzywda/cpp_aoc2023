#include "tasks.h"
#include <algorithm>

int part_a(std::vector<std::string> input) {
    std::vector<Stone> stones;
    size_t load = 0;

    for (size_t y = 0; y < input.size(); ++y) {
        for (size_t x = 0; x < input[y].size(); ++x) {
            if (input[y][x] == 'O') {
                stones.push_back({x, y});
                input[y][x] = '.';
            }
        }
    }

    for (auto& stone : stones) {
        while (stone.y > 0 && input[stone.y - 1][stone.x] == '.') --stone.y;

        input[stone.y][stone.x] = 'O';
        load += input.size() - stone.y;
    }

    return load;
}

int part_b(const std::vector<std::string>& input, size_t cycles) {
    std::vector<std::string> copy = input; 
    std::vector<Stone> stones;
    for (size_t y = 0; y < input.size(); ++y) {
        for (size_t x = 0; x < input[y].size(); ++x) {
            if (input[y][x] == 'O') {
                stones.push_back({x, y});
                copy[y][x] = '.';
            }
        }
    }

    std::vector<int> cyclesList;
    bool cycleFound = false;
    size_t cycleLength = 0;

    for (size_t i = 0; i < cycles; ++i) {
        if (!cycleFound) {
            int currentCycle = cycle(stones);
            if (std::find(cyclesList.begin(), cyclesList.end(), currentCycle) != cyclesList.end()) {
                auto it = std::find(cyclesList.begin(), cyclesList.end(), currentCycle);
                size_t startOfCycle = std::distance(cyclesList.begin(), it);

                if (i - startOfCycle == cycleLength) {
                    cycleFound = true;
                    i += (cycles - i) / cycleLength * cycleLength;
                } else {
                    cycleLength = i - startOfCycle;
                }
            }
            cyclesList.push_back(cycle(stones));
        }

        north(stones, copy);
        west(stones, copy);
        south(stones, copy);
        east(stones, copy);
    }

    int load = 0;
    for (auto& stone : stones) {
        load += input.size() - stone.y;
    }
    return load;
}

int cycle(const std::vector<Stone>& stones) {
    int sumX = 0, sumY = 0;
    for (const auto& stone : stones) {
        sumX += stone.x;
        sumY += stone.y;
    }
    return sumX + sumY;
}

void north(std::vector<Stone>& stones, const std::vector<std::string>& input) {
    std::sort(stones.begin(), stones.end(), [](const Stone& a, const Stone& b) { return a.y < b.y; });
    std::vector<std::string> copy = input;
    for (auto& stone : stones) {
        while (stone.y > 0 && copy[stone.y - 1][stone.x] == '.') --stone.y;
        copy[stone.y][stone.x] = 'O';
    }
}

void west(std::vector<Stone>& stones, const std::vector<std::string>& input) {
    std::sort(stones.begin(), stones.end(), [](const Stone& a, const Stone& b) { return a.x < b.x; });
    std::vector<std::string> copy = input;
    for (auto& stone : stones) {
        while (stone.x > 0 && copy[stone.y][stone.x - 1] == '.') --stone.x;
        copy[stone.y][stone.x] = 'O';
    }
}

void south(std::vector<Stone>& stones, const std::vector<std::string>& input) {
    std::sort(stones.begin(), stones.end(), [](const Stone& a, const Stone& b) { return a.y > b.y; });
    std::vector<std::string> copy = input;
    for (auto& stone : stones) {
        while (stone.y < input.size() - 1 && copy[stone.y + 1][stone.x] == '.') ++stone.y;
        copy[stone.y][stone.x] = 'O';
    }
}

void east(std::vector<Stone>& stones, const std::vector<std::string>& input) {
    std::sort(stones.begin(), stones.end(), [](const Stone& a, const Stone& b) { return a.x > b.x; });
    std::vector<std::string> copy = input;
    for (auto& stone : stones) {
        while (stone.x < input[0].size() - 1 && copy[stone.y][stone.x + 1] == '.') ++stone.x;
        copy[stone.y][stone.x] = 'O';
    }
}
