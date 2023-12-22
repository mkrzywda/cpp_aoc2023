#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <string>
#include <set>
#include <queue>

extern const std::vector<std::vector<int>> shifts;

std::vector<int> addVectors(const std::vector<int>& first, const std::vector<int>& second);
void drawVector(const std::vector<std::string>& input);
bool inBounds(const std::vector<int>& coords, int vectorXSize, int vectorYSize);
bool isANumber(char c);
std::vector<int> numsFromString(const std::string& line, int pos);
std::queue<std::vector<int>> setToQueue(const std::set<std::vector<int>>& input);
int sumGrid(const std::vector<std::string>& grid, char toCount);
std::vector<std::string> makeBigGrid(const std::vector<std::string>& grid, int scaleFactor);
long long lagrange(int in, const std::vector<int>& lagrangeCoeffs);

#endif
