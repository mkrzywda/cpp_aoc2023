#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <map>
#include <string>

std::vector<std::string> file2Vec(const std::string& fileName);
int part_a(const std::vector<std::string>& fileVec);
int part_b(const std::vector<std::string>& fileVec);

#endif
