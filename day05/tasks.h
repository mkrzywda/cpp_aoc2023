#ifndef TASKS_H
#define TASKS_H

#include <fstream>
#include <vector>
using namespace std;

struct Mapper
{
    long to;
    long from;
    long range;

    long map(long l);
};

vector<long> longsInString(string s);
vector<Mapper> mappersAfterLinePrefix(string prefix, ifstream& file);
long throughMappers(long l, vector<Mapper> v);
long part_a(const std::vector<long>& seeds, const std::vector<std::vector<Mapper>>& pipeline);
long part_b(const std::vector<long>& seeds, const std::vector<std::vector<Mapper>>& pipeline);


#endif // TASKS_H
