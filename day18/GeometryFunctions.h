#pragma once
#include "Point.h"
#include <vector>

template <typename T>
std::vector<Point<T>> processInstructions_partA(const std::vector<std::pair<char, T>> &instructions);

template <typename T>
std::vector<Point<T>> processInstructions_partB(const std::vector<std::pair<int, T>> &instructions);

template <typename T>
T manhattanDistance(const Point<T> &a, const Point<T> &b);

template <typename T>
T area_partA(const std::vector<Point<T>> &vertices);

template <typename T>
T area_partB(const std::vector<Point<T>> &vertices);
