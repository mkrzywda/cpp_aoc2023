#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>
#include <unordered_map>

bool isValidArrangement(const std::string &row, const std::vector<int> &arrangement);
void solveRow(std::string &row, int index, const std::vector<int> &groupSizes, int &validCount);
int part_a();
std::string createKey(int pos, const std::vector<int> &s, int h);
unsigned long long count(const std::string &p, std::vector<int> s, int h, std::unordered_map<std::string, unsigned long long> &memo);
int part_b();

#endif 
