#include <iostream>
#include <string>
#include "modules.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);

    part1(filename);
    part2(filename);

    return 0;
}
