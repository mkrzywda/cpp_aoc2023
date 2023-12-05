#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include "tasks.h"

using namespace std;

int main(int argc, char *argv[]) {
    string input;

    if (argc > 1) {
        input = argv[1];
    } else {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream file;
    file.open(input);
    if (!file.is_open()) {
        cerr << "Could not open input file." << endl;
        return 1;
    }

    string line;
    getline(file, line);
    size_t colon = line.find_first_of(":");
    vector<long> seeds = longsInString(line.substr(colon + 2));

    vector<vector<Mapper>> pipeline;
    pipeline.push_back(mappersAfterLinePrefix("seed-to-soil map:", file));
    pipeline.push_back(mappersAfterLinePrefix("soil-to-fertilizer map:", file));
    pipeline.push_back(mappersAfterLinePrefix("fertilizer-to-water map:", file));
    pipeline.push_back(mappersAfterLinePrefix("water-to-light map:", file));
    pipeline.push_back(mappersAfterLinePrefix("light-to-temperature map:", file));
    pipeline.push_back(mappersAfterLinePrefix("temperature-to-humidity map:", file));
    pipeline.push_back(mappersAfterLinePrefix("humidity-to-location map:", file));

    file.close();

    //long result_part_a = part_a(seeds, pipeline);

    //cout << "Lowest location (part_a) = " << result_part_a << endl;
    long result_part_b = part_b(seeds, pipeline);
    cout << "Lowest location (part_b) = " << result_part_b << endl;



    return 0;
}
