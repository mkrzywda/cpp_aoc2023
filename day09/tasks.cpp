#include "tasks.h"
#include <algorithm>

int extrapolate(std::vector<int>& history) {
    std::vector<int> numbers;
    numbers.reserve(history.size() - 1);

    bool allZero = true;
    for (int i = 0; i < history.size() - 1; ++i) {
        numbers.push_back(history[i + 1] - history[i]);
        if (numbers[i] != 0)
            allZero = false;
    }

    if (allZero)
        return 0;
    else
        return numbers[numbers.size() - 1] + extrapolate(numbers);
}

int part_a(const std::vector<std::vector<int>>& history) {
    int result = 0;

    for (const auto& numbers : history) {
        std::vector<int> numbersCopy = numbers;
        result += numbersCopy[numbersCopy.size() - 1] + extrapolate(numbersCopy);
    }

    return result;
}

int part_b(const std::string& input) {
    try {
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

            std::reverse(numbers.begin(), numbers.end());
            history.push_back(numbers);
        }
        fIn.close();

        int result = 0;

        for (auto& numbers : history) {
            result += numbers[numbers.size() - 1] + extrapolate(numbers);
        }

        return result;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}
