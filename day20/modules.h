#ifndef MODULES_H
#define MODULES_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

std::vector<std::string> readFile(std::string_view filename);
std::vector<std::string> split(std::string_view line, std::string_view delimiter);

struct Module {
protected:
    explicit Module(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue);
    virtual ~Module() = default;

public:
    virtual void trigger(std::string_view sender, int signal) = 0;
    void registerSender(std::string_view sender);

protected:
    void sendSignal(int signal) const;

public:
    void addLink(std::string_view link);

protected:
    const std::string name_;
    std::queue<std::tuple<std::string, int, std::string>>& queue_;

public:
    std::vector<std::string> links_;
    std::map<std::string, int> senders_;
};

struct BroadcasterModule : public Module {
    explicit BroadcasterModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue);
    void trigger(std::string_view, int signal) override;
};

struct FlipFlopModule : public Module {
    explicit FlipFlopModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue);
    void trigger(std::string_view, int signal) override;
    int state_{0};
};

struct ConjunctionModule : public Module {
    explicit ConjunctionModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue);
    void trigger(std::string_view sender, int signal) override;
};

struct OutputModule : public Module {
    explicit OutputModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue);
    void trigger(std::string_view, int) override;
};

void part1(std::string_view filename);
void part2(std::string_view filename);

#endif // MODULES_H
