#include "tasks.h"
#include <fstream>
#include <iostream>
#include <regex>


std::unordered_map<std::string, std::pair<std::string, std::string>> readNodes_partB(const std::string& filename, std::vector<std::string>& startingNodes) {
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    std::ifstream fIn(filename);
    if (!fIn.is_open()) {
        throw std::runtime_error("Error opening input file: " + filename);
    }

    std::string temp;
    std::regex r("[A-Z0-9]{3}");
    std::smatch match;
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;

        std::vector<std::string> matches;
        while (std::regex_search(temp, match, r)) {
            for (auto m : match) matches.push_back(m);
            temp = match.suffix().str();
        }

        if (matches[0][2] == 'A') startingNodes.push_back(matches[0]);
        nodes[matches[0]] = std::make_pair(matches[1], matches[2]);
    }

    fIn.close();
    return nodes;
}

// Function to navigate and return the number of steps for each starting node
std::vector<int> navigate_part_B(const std::unordered_map<std::string, std::pair<std::string, std::string>>& nodes, const std::vector<std::string>& startingNodes, const std::string& instructions) {
    std::vector<int> steps(startingNodes.size(), 0);

    for (int j = 0; j < startingNodes.size(); ++j) {
        std::string currentNode = startingNodes[j];
        for (int i = 0; i < instructions.size(); ++i) {
            auto it = nodes.find(currentNode);
            if (it == nodes.end()) {
                throw std::runtime_error("Invalid node: " + currentNode);
            }

            if (instructions[i] == 'L') {
                currentNode = it->second.first;
            } else {
                currentNode = it->second.second;
            }

            ++steps[j];
            if (i == instructions.size() - 1) {
                i = -1;
            }
            if (currentNode[2] == 'Z') {
                break;
            }
        }
    }

    return steps;
}



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <regex>
#include <stdexcept>

// Function to read nodes from the input file
std::unordered_map<std::string, std::pair<std::string, std::string>> readNodes(const std::string& filename) {
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening input file: " + filename);
    }

    std::string temp;
    std::regex r("[A-Z]{3}");
    std::smatch match;
    while (std::getline(inputFile, temp)) {
        if (temp.empty()) continue;

        std::vector<std::string> matches;
        while (std::regex_search(temp, match, r)) {
            for (auto m : match) matches.push_back(m);
            temp = match.suffix().str();
        }
        nodes[matches[0]] = std::make_pair(matches[1], matches[2]);
    }

    inputFile.close();
    return nodes;
}

// Function to perform the navigation and return the number of steps
int navigate(const std::unordered_map<std::string, std::pair<std::string, std::string>>& nodes, const std::string& instructions) {
    int steps = 0;
    std::string currentNode = "AAA";

    for (int i = 0; i < instructions.size(); ++i) {
        auto it = nodes.find(currentNode);
        if (it == nodes.end()) {
            throw std::runtime_error("Invalid node: " + currentNode);
        }

        if (instructions[i] == 'L') {
            currentNode = it->second.first;
        } else {
            currentNode = it->second.second;
        }

        ++steps;

        if (currentNode == "ZZZ") {
            break;
        } else if (i == instructions.size() - 1) {
            i = -1;
        }
    }

    return steps;
}
