#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>

std::vector<int> extract_numbers(const std::string& s);

struct Card {
  int id;
  std::vector<int> winning_numbers;
  std::vector<int> numbers_on_card;
  std::size_t copies;
};

std::size_t part_a(const std::string& input);

std::size_t part_b(const std::string& input);

#endif
