#include "tasks.h"
#include <iostream>
#include <fstream>

void update_colour(std::array<int, 3>& round, const std::string_view colour_data) {
    auto i = colour_data.find(' ');
    auto colour = colour_data.substr(i + 1);
    int n = 0;

    for (auto ele : colour_data.substr(0, i)) {
        n = n * 10 + (ele - '0');
    }

    if (colour == "red") {
        round[0] = n;
    } else if (colour == "green") {
        round[1] = n;
    } else if (colour == "blue") {
        round[2] = n;
    } else {
        std::cout << "This should not happen" << __LINE__ << '\n';
        exit(0);
    }
}

std::array<int, 3> parse_round(const std::string_view round_str) {
    std::size_t start = 0;
    std::size_t end = round_str.find(',');
    std::array<int, 3> round{{0, 0, 0}};

    while (end != std::string::npos) {
        auto colour_data = round_str.substr(start, end - start);
        update_colour(round, colour_data);
        start = end + 2;
        end = round_str.find(',', start);
    }

    auto colour_data = round_str.substr(start);
    update_colour(round, colour_data);
    return round;
}

Game parse_game(const std::string_view game_str) {
    std::size_t start = 0;
    std::size_t end = game_str.find(':');
    int game_number = std::stoi(std::string(game_str.substr(5, end - 5)));
    start = end + 1;
    end = game_str.find(';', start);
    Game game;
    game.id = game_number;

    while (end != std::string::npos) {
        auto round_data = game_str.substr(start + 1, end - start - 1);
        game.rounds.push_back(parse_round(round_data));
        start = end + 1;
        end = game_str.find(';', start);
    }

    auto round_data = game_str.substr(start + 1);
    game.rounds.push_back(parse_round(round_data));
    return game;
}
