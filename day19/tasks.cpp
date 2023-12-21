#include "tasks.h"
#include <iostream>
#include <functional>
#include <regex>
#include <fstream>
#include <sstream>
#include <stdexcept> // Include this header for std::runtime_error

std::string readFile(const std::string& filename) {
    std::ifstream input(filename);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::stringstream buffer;
    buffer << input.rdbuf();
    return buffer.str();
}

std::vector<std::string> split(std::string_view line, std::string_view delimiter) {
    size_t pos_start = 0;
    size_t pos_end = 0;

    std::vector<std::string> res;

    while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos) {
        auto token = line.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delimiter.length();

        res.emplace_back(token);
    }

    if (pos_start != line.size()) {
        res.emplace_back(line.substr(pos_start));
    }
    return res;
}

void resultPartA(std::map<std::string, std::tuple<std::vector<std::tuple<std::string, std::string, long, std::string>>, std::string>> rules, const std::vector<std::string>& parts) {
    long sum = 0;
    for (const auto& part : parts) {
        static const std::regex partsPattern{R"(\{x=(\d*),m=(\d*),a=(\d*),s=(\d*)\})"};

        std::smatch smatch;
        if (!std::regex_search(part, smatch, partsPattern)) {
            continue;
        }

        std::map<std::string, long> values = {
            {"x", std::stol(smatch[1])},
            {"m", std::stol(smatch[2])},
            {"a", std::stol(smatch[3])},
            {"s", std::stol(smatch[4])},
        };

        std::string rule = "in";
        while (rule != "A" && rule != "R") {
            auto [subRules, nextRule] = rules[rule];

            for (const auto& subRule : split(smatch[2].str(), ",")) {
                static const std::regex subRulesPattern{R"((.)(.)(\d*):(.*))"};

                std::smatch smatch2;
                if (std::regex_search(subRule, smatch2, subRulesPattern)) {
                    subRules.emplace_back(smatch2[1], smatch2[2], std::stol(smatch2[3]), smatch2[4]);
                }
            }

            for (const auto& subRule : subRules) {
                const auto [field, cmp, value, dest] = subRule;

                auto it = values.find(field);
                if (it != values.end() && ((cmp == ">" && it->second > value) || (cmp == "<" && it->second < value))) {
                    nextRule = dest;
                    break;
                }
            }

            rule = nextRule;
        }

        if (rule == "A") {
            sum += values["x"];
            sum += values["m"];
            sum += values["a"];
            sum += values["s"];
        }
    }
    std::cout << "Result Part A: " << sum << std::endl;
}

void resultPartB(std::map<std::string, std::tuple<std::vector<std::tuple<std::string, std::string, long, std::string>>, std::string>> rules) {
    std::function<long(std::map<std::string, std::tuple<long, long>>, std::string)> count = [&](std::map<std::string, std::tuple<long, long>> ranges, const std::string& name) -> long {
        if (name == "R") {
            return 0;
        }

        if (name == "A") {
            long result = 1;
            for (const auto& range : ranges) {
                const auto [lo, hi] = range.second;
                result *= hi - lo + 1;
            }
            return result;
        }

        const auto [subRules, fallback] = rules[name];

        long result = 0;

        bool runThrough = true;
        for (const auto& [key, cmp, value, target] : subRules) {
            const auto [lo, hi] = ranges[key];
            std::pair<long, long> T;
            std::pair<long, long> F;
            if (cmp == "<") {
                T = {lo, std::min(value - 1, hi)};
                F = {std::max(value, lo), hi};
            } else {
                T = {std::max(value + 1, lo), hi};
                F = {lo, std::min(value, hi)};
            }
            if (T.first <= T.second) {
                auto copy = ranges;
                copy[key] = T;
                result += count(copy, target);
            }
            if (F.first <= F.second) {
                ranges[key] = F;
            } else {
                runThrough = false;
                break;
            }
        }
        if (runThrough) {
            result += count(ranges, fallback);
        }

        return result;
    };

    std::cout << "Result Part B: " << count({
        {"x", {1, 4000}},
        {"m", {1, 4000}},
        {"a", {1, 4000}},
        {"s", {1, 4000}},
    },
        "in")
        << std::endl;
}
