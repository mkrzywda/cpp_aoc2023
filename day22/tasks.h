#pragma once

#include <vector>
#include <string>

struct Cube
{
    union
    {
        struct
        {
            int x, y, z;
        };
        int coords[3];
    };

    bool operator==(const Cube &other) const;
};

struct Brick
{
    std::vector<Cube> cubes;
};

std::vector<std::string> split(std::string str, std::string delimiter);
std::pair<std::vector<Brick>, int> dropBricks(std::vector<Brick> &bricks);
