// tasks.h
#pragma once

#include <vector>
#include <string>

std::vector<std::string> readInputFromFile(const char* filePath);
int solveMaze(int startX, int startY, int startDir, const std::vector<std::string>& maze);
