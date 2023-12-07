#ifndef TASKS_H
#define TASKS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <map>
#include <algorithm>

enum class HandStrength {
    HIGHCARD,
    ONEPAIR,
    TWOPAIR,
    THREEOFAKIND,
    FULLHOUSE,
    FOUROFAKIND,
    FIVEOFAKIND
};

int cardStrength_part_a(char card);
int cardStrength_part_b(char card);

HandStrength evaluateHand_part_a(const std::string& cards, int* result);
void part_a(std::vector<std::tuple<std::string, int, HandStrength>>* hands);

HandStrength evaluateHand_part_b(const std::string& cards, int* result);
void part_b(std::vector<std::tuple<std::string, int, HandStrength>>* hands);

#endif
