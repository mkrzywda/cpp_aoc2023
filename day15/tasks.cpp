#include "tasks.h"
#include <algorithm>

int calculateStringHash(std::string &input) {
    int hashValue = 0;
    for (auto &c : input) {
        hashValue += c;
        hashValue *= 17;
        hashValue %= 256;
    }
    return hashValue;
}

void updateOrInsertKeyValue(std::vector<std::pair<std::string, int>> &box, std::string &key, int value) {
    bool replaced = false;
    for (auto &it : box) {
        if (it.first == key) {
            it.second = value;
            replaced = true;
            break;
        }
    }
    if (!replaced) {
        box.emplace_back(key, value);
    }
}

void removeKeyValuePair(std::vector<std::pair<std::string, int>> &box, std::string &key) {
    box.erase(std::remove_if(box.begin(), box.end(), [&key](const auto &pair) {
        return pair.first == key;
    }), box.end());
}

int calculateFocusingPower(const std::vector<std::vector<std::pair<std::string, int>>> &boxes) {
    int focusingPower = 0;
    for (int box = 0; box < boxes.size(); ++box) {
        if (boxes[box].empty()) continue;
        for (int i = 0; i < boxes[box].size(); ++i) {
            focusingPower += (box + 1) * (i + 1) * boxes[box][i].second;
        }
    }
    return focusingPower;
}
