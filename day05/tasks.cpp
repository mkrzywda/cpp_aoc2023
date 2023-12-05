#include "tasks.h"
#include <climits>
#include <omp.h>

long Mapper::map(long l)
{
    return (l >= from && l < from + range) ? (to + l - from) : -1;
}

vector<long> longsInString(string s)
{
    int offset = 0;
    vector<long> v;
    while (true)
    {
        size_t space = s.substr(offset).find_first_of(" ");
        string convertThis = s.substr(offset, space);
        v.push_back(stol(convertThis));
        if (space == string::npos) break;
        offset += space + 1;
    }
    return v;
}

vector<Mapper> mappersAfterLinePrefix(string prefix, ifstream& file)
{
    string line;

    // eat until we find the prefix line
    while (getline(file, line))
    {
        if (line == prefix) break;
    }

    vector<Mapper> mappers;
    while (getline(file, line))
    {
        if (line.length() == 0) break;

        vector<long> stuff = longsInString(line);
        // if we die, we die. not every man truly lives.
        Mapper m;
        m.to = stuff[0];
        m.from = stuff[1];
        m.range = stuff[2];
        mappers.push_back(m);
    }

    return mappers;
}

long throughMappers(long l, vector<Mapper> v)
{
    for (vector<Mapper>::iterator iter = v.begin(); iter != v.end(); iter++)
    {
        long to = iter->map(l);
        if (to != -1) return to;
    }
    return l;
}


long part_a(const std::vector<long>& seeds, const std::vector<std::vector<Mapper>>& pipeline) {
    long lowestLocation = LONG_MAX;

    for (std::vector<long>::const_iterator seedIter = seeds.cbegin(); seedIter != seeds.cend(); seedIter++) {
        long l = *seedIter;
        for (std::vector<std::vector<Mapper>>::const_iterator pipeIter = pipeline.cbegin(); pipeIter != pipeline.cend(); pipeIter++)
            l = throughMappers(l, *pipeIter);
        if (l < lowestLocation)
            lowestLocation = l;
    }

    return lowestLocation;
}

long part_b(const std::vector<long>& seeds, const std::vector<std::vector<Mapper>>& pipeline) {
    long _lowestLocation = LONG_MAX;

#pragma omp parallel for reduction(min : _lowestLocation)
    for (size_t i = 0; i < seeds.size(); i++) {
        long rangeStart = seeds[i];
        long rangeSize = seeds[++i]; // Use pre-increment here.

        for (long seed = rangeStart; seed < rangeStart + rangeSize; seed++) {
            long l = seed;
            for (const auto& mappers : pipeline)
                l = throughMappers(l, mappers);
            
            #pragma omp critical
            {
                _lowestLocation = std::min(_lowestLocation, l);
            }
        }
    }

    return _lowestLocation;
} 