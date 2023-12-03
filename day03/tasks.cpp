#include "tasks.h"
#include <fstream>

std::vector<std::string> file2Vec(const std::string& fileName) {
    std::fstream inputFile;
    inputFile.open(fileName, std::ios::in);
    std::vector<std::string> fileVec;

    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            line.insert(0, ".");
            line.insert(line.size(), ".");
            fileVec.push_back(line);
        }

        inputFile.close();
    } else {
        throw std::runtime_error("FILE DID NOT OPEN");
    }
    return fileVec;
}

int part_a(const std::vector<std::string>& fileVec) {
    int sum = 0;
    int lineNo = 0;

    for (std::string line : fileVec) {
        int lineLost = 0;
        while (true) {
            size_t intStart = line.find_first_of("1234567890");
            if (intStart == std::string::npos) break;
            size_t intEnd = line.substr(intStart, line.size() - intStart).find_first_not_of("1234567890");
            int num = std::stoi(line.substr(intStart, intEnd));

            std::string searchZone;
            if (lineNo > 0)
                searchZone.append(fileVec[lineNo - 1].substr(lineLost + intStart - 1, intEnd + 2));
            if (lineNo < fileVec.size() - 1)
                searchZone.append(fileVec[lineNo + 1].substr(lineLost + intStart - 1, intEnd + 2));
            searchZone.append(fileVec[lineNo].substr(lineLost + intStart - 1, intEnd + 2));
            if (searchZone.find_first_not_of("1234567890.") != std::string::npos) {
                sum += num;
            }

            line = line.substr(intStart + intEnd, line.size() - intEnd);
            lineLost += intStart + intEnd;
        }
        lineNo++;
    }
    return sum;
}

int part_b(const std::vector<std::string>& fileVec) {
    int sum = 0;
    unsigned int lineNo = 0;
    std::map<std::vector<size_t>, std::vector<int>> starMap;

    for (std::string line : fileVec) {
        int lineLost = 0;
        while (true) {
            size_t intStart = line.find_first_of("1234567890");
            if (intStart == std::string::npos) break;
            size_t intEnd = line.substr(intStart, line.size() - intStart).find_first_not_of("1234567890");
            int num = std::stoi(line.substr(intStart, intEnd));

            std::string searchZone;
            if (lineNo > 0) {
                searchZone = fileVec[lineNo - 1].substr(lineLost + intStart - 1, intEnd + 2);
                while (true) {
                    size_t starP = searchZone.find_first_of("*");
                    if (starP == std::string::npos) break;
                    std::vector<size_t> key = {lineNo - 1, lineLost + intStart - 1 + starP};
                    starMap[key].push_back(num);
                    searchZone = searchZone.substr(starP + 1, searchZone.size() - starP - 1);
                }
            }
            if (lineNo < fileVec.size() - 1) {
                searchZone = (fileVec[lineNo + 1].substr(lineLost + intStart - 1, intEnd + 2));
                while (true) {
                    size_t starP = searchZone.find_first_of("*");
                    if (starP == std::string::npos) break;
                    std::vector<size_t> key = {lineNo + 1, lineLost + intStart - 1 + starP};
                    starMap[key].push_back(num);
                    searchZone = searchZone.substr(starP + 1, searchZone.size() - starP - 1);
                }
            }
            searchZone = (fileVec[lineNo].substr(lineLost + intStart - 1, intEnd + 2));
            while (true) {
                size_t starP = searchZone.find_first_of("*");
                if (starP == std::string::npos) break;
                std::vector<size_t> key = {lineNo, lineLost + intStart - 1 + starP};
                starMap[key].push_back(num);
                searchZone = searchZone.substr(starP + 1, searchZone.size() - starP - 1);
            }

            line = line.substr(intStart + intEnd, line.size() - intEnd);
            lineLost += intStart + intEnd;
        }
        lineNo++;
    }

    for (auto [key, value] : starMap) {
        if (value.size() == 2) {
            sum += (value[0] * value[1]);
        }
    }

    return sum;
}