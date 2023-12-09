#include "tasks.h"

int main(int argc, char* argv[]) {
    try {
        std::string input;

        if (argc > 1) {
            input = argv[1];
        } else {
            std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
            return 1;
        }

        std::vector<std::vector<int>> history;
        std::string temp;
        std::ifstream fIn(input);

        while (std::getline(fIn, temp)) {
            if (temp.empty())
                continue;

            char* token = std::strtok(&temp[0], " ");
            std::vector<int> numbers;

            while (token != nullptr) {
                numbers.push_back(std::stoi(token));
                token = std::strtok(nullptr, " ");
            }

            history.push_back(numbers);
        }

        fIn.close();

        int result_a = part_a(history);

        std::cout << "Part A Result: " << result_a << std::endl;

        int result_b = part_b(input);

        std::cout << "Part B Result: " << result_b << std::endl;

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
