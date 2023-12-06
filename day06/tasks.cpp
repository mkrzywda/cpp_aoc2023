#include "tasks.h"
#include <iostream>
#include <sstream>
#include <cmath>

void part_a(const std::vector<std::string>& input) {
    std::string temp;
    std::stringstream ssTimes(input[0]); ssTimes >> temp;
    std::stringstream ssDistances(input[1]); ssDistances >> temp;

    std::vector<int> times, distances;
    int value;
    while (ssTimes >> value) times.push_back(value);
    while (ssDistances >> value) distances.push_back(value);

    int product = 1;

    for (int i = 0; i < times.size(); ++i) {
        double t = times[i];
        double d = distances[i] + 1;
        double dis = t * t - 4 * d;
        double h1 = (t + std::sqrt(dis)) / 2;
        double h2 = (t - std::sqrt(dis)) / 2;

        int lower_bound = std::max(0, (int)(std::ceil(h2)));
        int upper_bound = std::min(t, (std::floor(h1)));
        product *= (upper_bound - lower_bound + 1);
    }


    std::cout << "Part  A Result: " << product << std::endl;
}


void part_b(const std::vector<std::string>& input) {
    std::string temp;
    
    std::stringstream ssTimes(input[0]); ssTimes >> temp;
    std::stringstream ssDistances(input[1]); ssDistances >> temp;

    std::vector<double> times, distances;
    std::string value;
    while (ssTimes >> temp) value += temp;
    times.push_back(std::stod(value));
    value = "";
    while (ssDistances >> temp) value += temp;
    distances.push_back(std::stod(value));

    int product = 1;


    for (int i = 0; i < times.size(); ++i) {
        double t = times[i];
        double d = distances[i] + 1;
        double dis = t * t - 4 * d;
        double h1 = (t + std::sqrt(dis)) / 2;
        double h2 = (t - std::sqrt(dis)) / 2;

        int lower_bound = std::max(0, (int)(std::ceil(h2)));
        int upper_bound = std::min(t, (std::floor(h1)));
        product *= (upper_bound - lower_bound + 1);
    }
    
    std::cout << "Part  B Result: " << product << std::endl;
}
