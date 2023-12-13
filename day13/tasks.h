#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <string>

bool isPattern(const std::vector<std::string>& pattern, int index);
int findPatternStartIndex(const std::vector<std::string>& pattern);
std::vector<std::string> rotateRight(const std::vector<std::string>& original);
int solver_part_a(const std::vector<std::vector<std::string>>& input);
bool compareRowsWithSmudge(std::vector<std::string>& grid, int r1, int r2, bool& smudge);
bool compareColumnsWithSmudge(std::vector<std::string>& grid, int c1, int c2, bool& smudge);
int solver_part_b();

#endif
