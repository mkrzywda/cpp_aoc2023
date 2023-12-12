#include "tasks.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool isValidArrangement(const std::string &row, const std::vector<int> &arrangement) {
    int index = 0;

    for (const auto &groupSize : arrangement) {
        int count = 0;

        while (index < row.length() && row[index] == '.') {
            index++;
        }

        while (index < row.length() && row[index] == '#') {
            count++;
            index++;
        }

        if (count != groupSize) {
            return false;
        }

        while (index < row.length() && row[index] == '.') {
            index++;
        }
    }

    while (index < row.length()) {
        if (row[index] == '#') {
            return false;
        }
        index++;
    }

    return true;
}

void solveRow(std::string &row, int index, const std::vector<int> &groupSizes, int &validCount) {
    if (index == row.length()) {
        if (isValidArrangement(row, groupSizes)) {
            validCount++;
        }
        return;
    }

    if (row[index] == '?') {
        row[index] = '.';
        solveRow(row, index + 1, groupSizes, validCount);

        row[index] = '#';
        solveRow(row, index + 1, groupSizes, validCount);
        row[index] = '?';
    } else {
        solveRow(row, index + 1, groupSizes, validCount);
    }
}

int part_a() {
    std::vector<std::string> input;
    std::vector<std::vector<int>> arrangements;
    std::string temp;
    std::ifstream fIn("/home/mkrzywda/cpp_aoc2023/day12/intput_day12.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty())
            continue;
        std::istringstream iss(temp);
        std::string word;
        std::getline(iss, word, ' ');
        input.push_back(word);

        std::string numbers;
        std::getline(iss, numbers);
        std::istringstream iss2(numbers);
        std::string num;
        std::vector<int> arr;
        while (std::getline(iss2, num, ',')) {
            arr.push_back(std::stoi(num));
        }
        arrangements.push_back(arr);
    }
    fIn.close();

    int validCount = 0;

    for (size_t i = 0; i < input.size(); ++i) {
        solveRow(input[i], 0, arrangements[i], validCount);
    }

    std::cout << "Part A Result: " << validCount << std::endl;

    return 0;
}

std::string createKey(int pos, const std::vector<int> &s, int h) {
    std::string key = std::to_string(pos) + "-";
    for (auto num : s) {
        key += std::to_string(num) + ",";
    }
    key += "k" + std::to_string(h);
    return key;
}

unsigned long long count(const std::string &p, std::vector<int> s, int h, std::unordered_map<std::string, unsigned long long> &memo) {
    if (p.empty()) {
        return s.empty() && h == 0;
    }
    std::string key = createKey(p.size(), s, h);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    unsigned long long n = 0;
    if (p[0] == '#' || p[0] == '?') {
        n += count(p.substr(1), s, h + 1, memo);
    }
    if ((p[0] == '.' || p[0] == '?') && (!s.empty() && s[0] == h || h == 0)) {
        std::vector<int> newS = (h == 0) ? s : std::vector<int>(s.begin() + 1, s.end());
        n += count(p.substr(1), newS, 0, memo);
    }
    memo[key] = n;
    return n;
}

int part_b() {
    std::vector<std::string> input;
    std::vector<std::vector<int>> arrangements;
    std::string temp;
    std::ifstream fIn("/home/mkrzywda/cpp_aoc2023/day12/intput_day12.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty())
            continue;
        std::istringstream iss(temp);
        std::string word;
        std::getline(iss, word, ' ');
        word = word + "?" + word + "?" + word + "?" + word + "?" + word;
        input.push_back(word);

        std::string numbers;
        std::getline(iss, numbers);
        std::istringstream iss2(numbers);
        std::string num;
        std::vector<int> arr;
        while (std::getline(iss2, num, ',')) {
            arr.push_back(std::stoi(num));
        }
        std::vector<int> arr2;
        for (int i = 0; i < 5; ++i) {
            arr2.insert(arr2.end(), arr.begin(), arr.end());
        }
        arrangements.push_back(arr2);
    }
    fIn.close();

    unsigned long long total = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        std::unordered_map<std::string, unsigned long long> memo;
        total += count(input[i] + ".", arrangements[i], 0, memo);
    }

    std::cout << "Part B Result: " << total << std::endl;

    return 0;
}
