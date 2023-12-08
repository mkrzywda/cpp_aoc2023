#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::pair<std::string, std::string>> readNodes(const std::string& filename);

int navigate(const std::unordered_map<std::string, std::pair<std::string, std::string>>& nodes, const std::string& instructions);

std::unordered_map<std::string, std::pair<std::string, std::string>> readNodes_partB(const std::string& filename, std::vector<std::string>& startingNodes);

std::vector<int> navigate_part_B(const std::unordered_map<std::string, std::pair<std::string, std::string>>& nodes, const std::vector<std::string>& startingNodes, const std::string& instructions);

#endif
