#include "tasks.h"
#include <iostream>
#include <regex>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    const auto input = split(readFile(argv[1]), "\n\n");
    const auto rulesString = split(input[0], "\n");
    const auto parts = split(input[1], "\n");

    std::map<std::string, std::tuple<std::vector<std::tuple<std::string, std::string, long, std::string>>, std::string>> rules;

    for (const auto& rule : rulesString) {
        static const std::regex rulesPattern{R"((.*)\{(.*),(.*)\})"};

        std::smatch smatch;
        if (!std::regex_search(rule, smatch, rulesPattern)) {
            continue;
        }

        std::string name = smatch[1];
        std::string defaultRule = smatch[3];

        std::vector<std::tuple<std::string, std::string, long, std::string>> subRules;

        for (const auto& subRule : split(smatch[2].str(), ",")) {
            static const std::regex subRulesPattern{R"((.)(.)(\d*):(.*))"};

            std::smatch smatch2;
            if (std::regex_search(subRule, smatch2, subRulesPattern)) {
                subRules.emplace_back(smatch2[1], smatch2[2], std::stol(smatch2[3]), smatch2[4]);
            }
        }

        rules[name] = std::make_tuple(subRules, defaultRule);
    }

    resultPartA(rules, parts);
    resultPartB(rules);

    return 0;
}
