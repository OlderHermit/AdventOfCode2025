#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

long COUNTER = 0;
int FFT_COUNTER = 0;
int FFT_COUNT = 0;
int DAC_COUNTER = 0;
int DAC_COUNT = 0;
auto USED = std::vector<std::string>();

auto partOne(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    auto data = std::map<std::string, std::vector<std::string>>();

    for (std::string line; std::getline(input, line);) {
        auto key = line.substr(0,3);
        auto stream = std::stringstream(line.substr(5));
        auto node = std::string();

        data[key].emplace_back();
        while (stream.good()) {
            stream >> node;
            data[key].push_back(node);
        }
    }

    auto counter = 0;
    auto backlog = std::queue<std::string>({"you"});
    while (!backlog.empty()) {
        const auto& key = backlog.front();
        for (const auto& k: data[key]) {
            if (k == "out")
                counter++;
            else
                backlog.push(k);
        }
        backlog.pop();
    }
    fmt::println("{}", counter);
}

auto magicFold(std::map<std::string, std::vector<std::pair<std::string,long>>>& data, const std::string& elem) {
    while (true) {
        auto tmp = std::vector<std::pair<std::string, long>>();
        for (const auto& [key, vec]: data) {
            if (vec.size() == 1 and vec[0].first == elem and key != "dac" and key != "fft" and key != "svr") {
                tmp.emplace_back(key, vec[0].second);
            }
        }
        if (tmp.empty())
            break;
        for (const auto & [removeKey, count] : tmp) {
            data.erase(removeKey);
            for (auto &vec: data | std::views::values) {
                auto idx = std::ranges::find(vec, removeKey, [](const std::pair<std::string,long> e){return e.first;});
                if (idx != vec.end()) {
                    vec.erase(idx);
                    idx = std::ranges::find(vec, elem, [](const std::pair<std::string,long> e){return e.first;});
                    if (idx != vec.end())
                        idx->second += count;
                    else
                        vec.emplace_back(elem, count);
                }
            }
        }
    }
}

auto removeDeadPaths(std::map<std::string, std::vector<std::pair<std::string,long>>>& data, const std::string& elem) {
    for (auto &[key, vec]: data) {
        auto contains = std::ranges::contains(vec, elem, [](const std::pair<std::string, long> p){return p.first;});
        if (contains and key != "dac" and key != "fft") {
            auto range = std::ranges::remove(vec, elem, [](const std::pair<std::string, long> p){return p.first;});
            vec.erase(range.begin(), range.end());
        }
    }
}

auto partTwo(const std::string& filename) ->  void {
    auto input = std::ifstream(filename);
    auto data = std::map<std::string, std::vector<std::pair<std::string, long>>>();

    for (std::string line; std::getline(input, line);) {
        auto key = line.substr(0,3);
        auto stream = std::stringstream(line.substr(5));
        auto node = std::string();

        data[key].emplace_back();
        data[key].clear();
        while (stream.good()) {
            stream >> node;
            data[key].emplace_back(node, 1);
        }
    }

    magicFold(data, "out");
    fmt::println("{}", data.size());
    removeDeadPaths(data, "out");

    magicFold(data, "dac");
    fmt::println("{}", data.size());
    removeDeadPaths(data, "dac");

    magicFold(data, "fft");
    fmt::println("{}", data.size());
    // removeDeadPaths(data, "fft");

    fmt::println("{}", data);
    fmt::println("{}", data["svr"].front().second * data["fft"].front().second * data["dac"].front().second);
}

auto main() -> int {
    // partOne("../11/data.txt");
    // partTwo("../11/example2.txt");
    partTwo("../11/data.txt");
}

