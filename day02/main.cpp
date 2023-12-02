#include "tasks.h"
#include <iostream>
#include <fstream>
#include <string> 

int part_b(const std::vector<Game>& games) {
    std::size_t total = 0;

    for (const auto& game : games) {
        std::array<int, 3> min_cubes{{0, 0, 0}};

        for (const auto& round : game.rounds) {
            for (int i = 0; i < 3; i++) {
                min_cubes[i] = std::max(min_cubes[i], round[i]);
            }
        }

        total += min_cubes[0] * min_cubes[1] * min_cubes[2];
    }

    return total;
}

int part_a(const std::vector<Game>& games) {
    int count = 0;

    for (const auto& game : games) {
        bool playable = true;

        for (const auto& round : game.rounds) {
            if (round[0] > 12 || round[1] > 13 || round[2] > 14) {
                playable = false;
                break;
            }
        }

        if (playable) {
            count += game.id;
        }
    }

    return count;
}

int main(int argc, char* argv[]) {
    std::string input;
    if (argc > 1) {
        input = argv[1];
    }

    std::string line;
    std::ifstream file(input); 

    std::vector<Game> games;
    while (std::getline(file, line)) {
        games.emplace_back(parse_game(line));
    }

    std::cout << "Part A: " << part_a(games) << '\n';
    std::cout << "Part B: " << part_b(games) << '\n';

    return 0;
}

