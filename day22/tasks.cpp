#include "tasks.h"
#include <algorithm>
#include <climits>

bool Cube::operator==(const Cube &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}

std::pair<std::vector<Brick>, int> dropBricks(std::vector<Brick> &bricks)
{
    std::sort(bricks.begin(), bricks.end(), [](const Brick &a, const Brick &b)
              {
                  int mina = INT_MAX;
                  for (const Cube &cube : a.cubes)
                  {
                      mina = std::min(mina, cube.z);
                  }
                  int minb = INT_MAX;
                  for (const Cube &cube : b.cubes)
                  {
                      minb = std::min(minb, cube.z);
                  }

                  return mina < minb;
              });

    std::vector<Cube> settled;
    std::vector<Brick> finalBricks;
    int numFell = 0;

    for (Brick &brick : bricks)
    {
        bool moved = false;
        while (true)
        {
            std::vector<Cube> next;
            for (const Cube &cube : brick.cubes)
            {
                next.push_back({cube.x, cube.y, cube.z - 1});
            }

            if (std::all_of(next.begin(), next.end(), [&settled](const Cube &cube)
                            { return cube.z != 0 && std::find(settled.begin(), settled.end(), cube) == settled.end(); }))
            {
                moved = true;
                brick.cubes = next;
            }
            else
            {
                break;
            }
        }

        for (const Cube &cube : brick.cubes)
        {
            settled.push_back(cube);
        }
        finalBricks.push_back(brick);
        if (moved)
        {
            numFell++;
        }
    }

    return {finalBricks, numFell};
}
