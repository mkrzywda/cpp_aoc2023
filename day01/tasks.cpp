#include "tasks.h"
#include <numeric>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Function to extract digits and words from a line
std::vector<int> extractDigitsAndWords(const std::string& line, const std::vector<std::string>& words) {
    std::vector<int> result;
    
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        
        // Extract digits
        if (c >= '0' && c <= '9') {
            result.push_back(c - '0');
        }
        
        // Extract words
        for (size_t j = 0; j < words.size(); ++j) {
            const std::string& word = words[j];
            
            if (line.size() >= i + word.size()) {
                if (line.substr(i, word.size()) == word) {
                    result.push_back(j + 1);
                }
            }
        }
    }
    
    return result;
}

// Function for Part A of the task
int part_a(const std::string& input) {
    std::vector<int> calibration_values;
    std::string line;
    
    // Open file
    std::ifstream file(input);
    
    // Read lines from the file
    while (std::getline(file, line)) {
        std::vector<int> digits = extractDigitsAndWords(line, {});
        
        // Process extracted values
        if (!digits.empty()) {
            calibration_values.push_back(digits[0] * 10 + digits.back());
        }
    }
    
    // Calculate and return the sum
    int sum = 0;
    for (size_t i = 0; i < calibration_values.size(); ++i) {
        sum += calibration_values[i];
    }
    return sum;
}

// Function for Part B of the task
int part_b(const std::string& input) {
    std::vector<int> calibration_values;
    std::string line;
    
    // Open file
    std::ifstream file(input);
    
    // Words to be matched
    std::vector<std::string> numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    // Read lines from the file
    while (std::getline(file, line)) {
        std::vector<int> digits = extractDigitsAndWords(line, numbers);
        
        // Process extracted values
        if (!digits.empty()) {
            calibration_values.push_back(digits[0] * 10 + digits.back());
        }
    }
    
    // Calculate and return the sum
    int sum = 0;
    for (size_t i = 0; i < calibration_values.size(); ++i) {
        sum += calibration_values[i];
    }
    return sum;
}
