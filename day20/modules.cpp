#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

std::vector<std::string>
readFile(std::string_view filename)
{
    std::ifstream input{std::string(filename)};
    std::vector<std::string> data;

    for (std::string line; getline(input, line);) {
        data.emplace_back(line);
    }

    return data;
}

std::vector<std::string>
split(std::string_view line, std::string_view delimiter)
{
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

struct Module {
protected:
    explicit Module(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue)
        : name_(name)
        , queue_(queue)
    {
    }
    virtual ~Module() = default;

public:
    virtual void trigger(std::string_view sender, int signal) = 0;

    void registerSender(std::string_view sender) { senders_.emplace(sender, 0); }

protected:
    void sendSignal(int signal) const
    {
        for (const auto& link : links_) {
            queue_.emplace(name_, signal, link);
        }
    }

public:
    void addLink(std::string_view link) { links_.emplace_back(link); }

protected:
    const std::string name_;
    std::queue<std::tuple<std::string, int, std::string>>& queue_;

public:
    std::vector<std::string> links_;
    std::map<std::string, int> senders_;
};

struct BroadcasterModule : public Module {
    explicit BroadcasterModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue)
        : Module(name, queue)
    {
    }
    void trigger(std::string_view, int signal) override
    {
        sendSignal(signal);
    }
};

struct FlipFlopModule : public Module {
    explicit FlipFlopModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue)
        : Module(name, queue)
    {
    }
    void trigger(std::string_view, int signal) override
    {
        if (signal == 1) {
            return;
        }
        state_ = (state_ + 1) % 2;
        sendSignal(state_);
    }
    int state_{0};
};

struct ConjunctionModule : public Module {
    explicit ConjunctionModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue)
        : Module(name, queue)
    {
    }
    void trigger(std::string_view sender, int signal) override
    {
        senders_[std::string(sender)] = signal;
        if (std::all_of(senders_.begin(), senders_.end(), [](const auto& link) { return link.second == 1; })) {
            sendSignal(0);
        } else {
            sendSignal(1);
        }
    }
};

struct OutputModule : public Module {
    explicit OutputModule(std::string_view name, std::queue<std::tuple<std::string, int, std::string>>& queue)
        : Module(name, queue)
    {
    }
    void trigger(std::string_view, int) override
    {
    }
};

void part1(std::string_view filename)
{
    std::queue<std::tuple<std::string, int, std::string>> queue;
    std::map<std::string, std::shared_ptr<Module>> modules;

    modules["output"] = std::make_shared<OutputModule>("output", queue);

    const auto input = readFile(filename);
    for (const auto& line : input) {
        const auto parts = split(line, " -> ");
        auto module = parts[0];
        const auto dests = split(parts[1], ", ");

        std::shared_ptr<Module> ptr;
        if (module == "broadcaster") {
            ptr = std::make_shared<BroadcasterModule>(module, queue);
        } else if (std::equal(module.begin(), module.begin() + 1, "%")) {
            module.erase(0, 1);
            ptr = std::make_shared<FlipFlopModule>(module, queue);
        } else if (std::equal(module.begin(), module.begin() + 1, "&")) {
            module.erase(0, 1);
            ptr = std::make_shared<ConjunctionModule>(module, queue);
        } else {
            std::cerr << "unknown module type: " << module << std::endl;
            return;
        }

        for (const auto& dest : dests) {
            ptr->addLink(dest);
        }

        modules[module] = ptr;
    }

    for (auto& module : modules) {
        auto [name, ptr] = module;

        for (const auto& link : ptr->links_) {
            if (modules.find(link) != modules.end()) {
                modules[link]->registerSender(name);
            }
        }
    }

    long sums[2] = {0, 0};
    for (int i = 0; i != 1000; ++i) {
        queue.emplace("button", 0, "broadcaster");
        while (!queue.empty()) {
            const auto [sender, signal, receiver] = queue.front();
            queue.pop();

            sums[signal]++;

            if (modules.find(receiver) != modules.end()) {
                modules[receiver]->trigger(sender, signal);
            }
        }
    }
    std::cout << sums[0] * sums[1] << std::endl;
}

void part2(std::string_view filename)
{
    std::queue<std::tuple<std::string, int, std::string>> queue;
    std::map<std::string, std::shared_ptr<Module>> modules;

    modules["output"] = std::make_shared<OutputModule>("output", queue);

    const auto input = readFile(filename);
    for (const auto& line : input) {
        const auto parts = split(line, " -> ");
        auto module = parts[0];
        const auto dests = split(parts[1], ", ");

        std::shared_ptr<Module> ptr;
        if (module == "broadcaster") {
            ptr = std::make_shared<BroadcasterModule>(module, queue);
        } else if (std::equal(module.begin(), module.begin() + 1, "%")) {
            module.erase(0, 1);
            ptr = std::make_shared<FlipFlopModule>(module, queue);
        } else if (std::equal(module.begin(), module.begin() + 1, "&")) {
            module.erase(0, 1);
            ptr = std::make_shared<ConjunctionModule>(module, queue);
        } else {
            std::cerr << "unknown module type: " << module << std::endl;
            return;
        }

        for (const auto& dest : dests) {
            ptr->addLink(dest);
        }

        modules[module] = ptr;
    }

    std::string toRx;
    for (auto& module : modules) {
        auto [name, ptr] = module;

        for (const auto& link : ptr->links_) {
            if (modules.find(link) != modules.end()) {
                modules[link]->registerSender(name);
            } else {
                toRx = name;
            }
        }
    }

    std::map<std::string, long> cycleModules;
    for (auto& module : modules) {
        auto [name, ptr] = module;
        const auto links = ptr->links_;

        if (std::find(links.begin(), links.end(), toRx) != links.end()) {
            cycleModules[name] = 0;
        }
    }

    for (long i = 1;; ++i) {
        queue.emplace("button", 0, "broadcaster");
        while (!queue.empty()) {
            const auto [sender, signal, receiver] = queue.front();
            queue.pop();

            if (signal == 1 && cycleModules.find(sender) != cycleModules.end()) {
                cycleModules[sender] = i;
            }

            if (modules.find(receiver) != modules.end()) {
                modules[receiver]->trigger(sender, signal);
            }
        }
        if (std::all_of(cycleModules.begin(), cycleModules.end(), [](const auto& module) { return module.second != 0; })) {
            long result = 1;
            for (const auto& module : cycleModules) {
                result = std::lcm(result, module.second);
            }
            std::cout << result << std::endl;
            break;
        }
    }
}