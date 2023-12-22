#include "tasks.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    std::ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<Brick> bricks;

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> parts = split(line, "~");
        std::vector<std::string> startVec = split(parts[0], ",");
        std::vector<std::string> endVec = split(parts[1], ",");
        Cube start = {std::stoi(startVec[0]), std::stoi(startVec[1]), std::stoi(startVec[2])};
        Cube end = {std::stoi(endVec[0]), std::stoi(endVec[1]), std::stoi(endVec[2])};
        std::vector<Cube> cubes;

        cubes.push_back(start);

        for (int i = 0; i < 3; i++)
        {
            if (start.coords[i] != end.coords[i])
            {
                for (int j = start.coords[i] + 1; j < end.coords[i]; j++)
                {
                    Cube cube = start;
                    cube.coords[i] = j;
                    cubes.push_back(cube);
                }
            }
        }

        cubes.push_back(end);

        bricks.push_back({cubes});
    }

    std::vector<Brick> dropped = dropBricks(bricks).first;

    int p1 = 0;
    int p2 = 0;

    for (int i = 0; i < dropped.size(); i++)
    {
        std::vector<Brick> without = dropped;
        without.erase(without.begin() + i);
        int num_fell = dropBricks(without).second;
        if (num_fell == 0)
        {
            p1++;
        }
        p2 += num_fell;
    }

    std::cout << "Part A: " << p1 << std::endl;
    std::cout << "Part B: " << p2 << std::endl;

    return 0;
}
