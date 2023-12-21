#include "GeometryFunctions.h"
#include <cmath>

template <typename T>
std::vector<Point<T>> processInstructions_partA(const std::vector<std::pair<char, T>> &instructions) {
    Point<T> current = {0, 0};
    std::vector<Point<T>> vertices;
    vertices.push_back(current);

    for (const auto &instruction : instructions) {
        if (instruction.first == 'U') current.y += instruction.second;
        else if (instruction.first == 'D') current.y -= instruction.second;
        else if (instruction.first == 'L') current.x -= instruction.second;
        else if (instruction.first == 'R') current.x += instruction.second;

        vertices.push_back(current);
    }

    return vertices;
}

template <typename T>
std::vector<Point<T>> processInstructions_partB(const std::vector<std::pair<int, T>> &instructions) {
    Point<T> current = {0, 0};
    std::vector<Point<T>> vertices;
    vertices.push_back(current);

    for (const auto &instruction : instructions) {
        if (instruction.first == 3) current.y += instruction.second;
        else if (instruction.first == 1) current.y -= instruction.second;
        else if (instruction.first == 2) current.x -= instruction.second;
        else if (instruction.first == 0) current.x += instruction.second;

        vertices.push_back(current);
    }

    return vertices;
}

template <typename T>
T manhattanDistance(const Point<T> &a, const Point<T> &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

template <typename T>
T area_partA(const std::vector<Point<T>> &vertices) {
    T i = 0, b = 0;

    for (size_t v = 0; v < vertices.size(); v++) {
        size_t j = (v + 1) % vertices.size();
        i += (vertices[v].x * vertices[j].y) - (vertices[j].x * vertices[v].y);
        b += manhattanDistance(vertices[v], vertices[j]);
    }

    i = std::abs(i / 2);
    return i + (b / 2) + 1;
}

template <typename T>
T area_partB(const std::vector<Point<T>> &vertices) {
    T i = 0, b = 0;

    for (size_t v = 0; v < vertices.size(); v++) {
        size_t j = (v + 1) % vertices.size();
        i += (vertices[v].x * vertices[j].y) - (vertices[j].x * vertices[v].y);
        b += manhattanDistance(vertices[v], vertices[j]);
    }

    i = std::abs(i / 2);
    return i + (b / 2) + 1;
}

// Explicit instantiation
template std::vector<Point<int>> processInstructions_partA(const std::vector<std::pair<char, int>> &);
template std::vector<Point<long long>> processInstructions_partA(const std::vector<std::pair<char, long long>> &);
template std::vector<Point<int>> processInstructions_partB(const std::vector<std::pair<int, int>> &);
template std::vector<Point<long long>> processInstructions_partB(const std::vector<std::pair<int, long long>> &);



// Explicit instantiation for int
template int area_partA<int>(const std::vector<Point<int>> &);
template int area_partB<int>(const std::vector<Point<int>> &);

// Explicit instantiation for long long
template long long area_partA<long long>(const std::vector<Point<long long>> &);
template long long area_partB<long long>(const std::vector<Point<long long>> &);