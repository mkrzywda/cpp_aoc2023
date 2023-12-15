#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>
#include <utility>

int calculateStringHash(std::string &input);
void updateOrInsertKeyValue(std::vector<std::pair<std::string, int>> &box, std::string &key, int value);
void removeKeyValuePair(std::vector<std::pair<std::string, int>> &box, std::string &key);
int calculateFocusingPower(const std::vector<std::vector<std::pair<std::string, int>>> &boxes);

#endif