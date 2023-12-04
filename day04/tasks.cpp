#include "tasks.h"
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <cmath>

std::vector<int> extract_numbers(const std::string& s) {
  std::vector<int> numbers;
  std::size_t start = 0;
  std::size_t end = s.find(' ');
  for (int i = 0; i < s.size(); i += 3) {
    if (s[i] == ' ') {  
      numbers.push_back(std::stoi(s.substr(i+1, i+2)));
    } else {
      numbers.push_back(std::stoi(s.substr(i, i+2)));
    }
  }
  return numbers;
}

std::size_t part_a(const std::string& input) {
  std::string line;
  std::fstream file(input);

  std::size_t total_points = 0;
  while(std::getline(file, line)) {
    std::size_t start = 0;
    std::size_t end = line.find(':');
    const int card_id = std::stoi(line.substr(5, end - 5));
    start = end + 2;
    end = line.find('|', start);
    const auto winning_numbers = extract_numbers(line.substr(start, end - start));
    const auto card_numbers = extract_numbers(line.substr(end + 2, line.size() - end));
    int count = 0;
    for (const auto& card_number : card_numbers) {
      if (std::find(std::begin(winning_numbers), std::end(winning_numbers), card_number) !=  std::end(winning_numbers)) {
        count++;
      }
    }
    if (count > 0) {
      total_points += std::pow(2, count - 1);
    }
  }
  return total_points;
}

std::size_t part_b(const std::string& input) {
  std::string line;
  std::fstream file(input);

  std::size_t total_points = 0;
  std::vector<Card> cards;
  while(std::getline(file, line)) {
    Card c;
    std::size_t start = 0;
    std::size_t end = line.find(':');
    c.id = std::stoi(line.substr(5, end - 5));
    start = end + 2;
    end = line.find('|', start);
    
    c.winning_numbers = extract_numbers(line.substr(start, end - start));
    c.numbers_on_card = extract_numbers(line.substr(end + 2, line.size() - end));
    c.copies = 1;
    cards.push_back(c);
  }

  for (const auto& card : cards) {
    int count = 0;
    for (const auto& number_on_card : card.numbers_on_card) {
      if (std::find(std::begin(card.winning_numbers), std::end(card.winning_numbers), number_on_card) !=  std::end(card.winning_numbers)) {
        count++;
      }
    }
    for (int i = card.id + 1 - 1; i < std::min(cards.size(), std::size_t(card.id + count)); i++) {
      cards[i].copies += card.copies;
    }
  }
  return std::accumulate(std::begin(cards), std::end(cards), 0, [](std::size_t total, const Card& card) {return total + card.copies;});
}
