#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <string>

struct Stone {
    size_t x, y;
};

// Function declarations
int part_a(std::vector<std::string> input);
int part_b(const std::vector<std::string>& input, size_t cycles);
int cycle(const std::vector<Stone>& stones);
void north(std::vector<Stone>& stones, const std::vector<std::string>& input);
void west(std::vector<Stone>& stones, const std::vector<std::string>& input);
void south(std::vector<Stone>& stones, const std::vector<std::string>& input);
void east(std::vector<Stone>& stones, const std::vector<std::string>& input);

#endif