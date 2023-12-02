#ifndef TASKS_H
#define TASKS_H

#include <array>
#include <string_view>
#include <vector>

void update_colour(std::array<int, 3>& round, const std::string_view colour_data);
std::array<int, 3> parse_round(const std::string_view round_str);

struct Game {
    int id;
    std::vector<std::array<int, 3>> rounds;
};

Game parse_game(const std::string_view game_str);

#endif
