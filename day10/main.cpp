#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static std::vector<std::string> S, X;

enum directions { d_down, d_right, d_up, d_left };

int main(int argc, char* argv[]) {
    try {
        std::string input;
        if (argc > 1) {
            input = argv[1];
        } else {
            std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
            return 1;
        }

        std::ifstream file(input);
        std::string line;
        int start_x, start_y, x, y = 0;
        while (std::getline(file, line)) {
            std::string s;
            x = 0;
            for (auto c : line) {
                if (c == 'S') {
                    start_x = x;
                    start_y = y;
                }
                x++;
                s += '.';
            }
            y++;
            S.push_back(line);
            X.push_back(s);
        }

        unsigned part1 = 0, part2 = 0, steps = 0;
        directions direction = d_down;
        x = start_x;
        y = start_y;
        X[y][x] = 'S';

        if (x < S[0].size() - 1 && (S[y][x + 1] == '-' || S[y][x + 1] == 'J' || S[y][x + 1] == '7'))
            direction = d_right;
        else if (y > 0 && (S[y - 1][x] == '|' || S[y - 1][x] == '7' || S[y - 1][x] == 'F'))
            direction = d_up;
        else if (x > 0 && (S[y][x - 1] == '-' || S[y][x - 1] == 'F' || S[y][x - 1] == 'L'))
            direction = d_left;

        bool ready = false;
        char c = '.';

        // Move in the selected direction until 'S' is reached
        while (c != 'S') {
            c = '.';
            switch (direction) {
                case d_down:
                    c = S[y + 1][x];
                    if (c == 'J')
                        direction = d_left;
                    else if (c == 'L')
                        direction = d_right;
                    y++;
                    break;
                case d_right:
                    c = S[y][x + 1];
                    if (c == 'J')
                        direction = d_up;
                    else if (c == '7')
                        direction = d_down;
                    x++;
                    break;
                case d_up:
                    c = S[y - 1][x];
                    if (c == 'F')
                        direction = d_right;
                    else if (c == '7')
                        direction = d_left;
                    y--;
                    break;
                case d_left:
                    c = S[y][x - 1];
                    if (c == 'F')
                        direction = d_down;
                    else if (c == 'L')
                        direction = d_up;
                    x--;
                    break;
            }
            X[y][x] = c;
            steps++;
        }

        std::cout << "Part A Result: " << steps/2 << std::endl;
        
        for (int i = 0; i < X.size(); i++) {
            bool inside = false;
            char online = '.';
            for (int j = 0; j < X[0].size(); j++) {
                char cx = X[i][j];
                if (cx == '|' || cx == 'J' || cx == 'L' || cx == 'F' || cx == '7') {
                    switch (cx) {
                        case '|':
                            inside = !inside;
                            break;
                        case 'F':
                            online = 'F';
                            break;
                        case 'L':
                            online = 'L';
                            break;
                        case '7':
                            if (online == 'L') inside = !inside;
                            break;
                        case 'J':
                            if (online == 'F') inside = !inside;
                            break;
                    }
                } else if (cx == '.' && inside) {
                    part2++;
                }
            }
        }
        std::cout << "Part B Result: " << part2 << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
