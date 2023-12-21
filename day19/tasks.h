#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

std::string readFile(const std::string& filename);
std::vector<std::string> split(std::string_view line, std::string_view delimiter);

void resultPartA(std::map<std::string, std::tuple<std::vector<std::tuple<std::string, std::string, long, std::string>>, std::string>> rules, const std::vector<std::string>& parts);

void resultPartB(std::map<std::string, std::tuple<std::vector<std::tuple<std::string, std::string, long, std::string>>, std::string>> rules);
