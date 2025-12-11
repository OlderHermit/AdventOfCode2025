#include <algorithm>
#include <array>
#include <bitset>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <vector>

auto add(const std::vector<int>& first, const std::vector<int>& second) -> std::vector<int>;
auto isIndexValid(const std::vector<int>& jolts, const std::vector<int>& test)-> bool;

auto partOne(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    long sum = 0l;

    for (auto line = std::string(); std::getline(input, line);) {
        auto lightsString = std::string(line.begin()+1, std::ranges::find(line,']'));
        auto lightsSize = lightsString.size();
        // fmt::println("{} ", lightsString);

        auto stringButtons =
            std::string(
                std::ranges::find(line, '('),
                std::ranges::find_last(line, ')').begin()+1
            ) | std::views::split(' ') | std::ranges::to<std::vector<std::string>>();

        auto buttons = std::vector<int>();
        for (auto s: stringButtons) {
            auto stream = std::stringstream(s.substr(1, s.size()-2));
            char c;
            int v;
            int mask = 0;
            while (stream.good()) {
                stream >> v >> c;
                mask |= 1 << (lightsString.size()-1-v);
            }
            // fmt::println("{} -> {:b}", s, mask);
            buttons.push_back(mask);
        }

        int lights = 0;
        for (auto [i, c] : lightsString | std::views::enumerate) {
            if (c == '#')
                lights |= 1 << (lightsString.size()-1-i);
        }
        // fmt::println("{:b}", lights);

        //solution
        auto lookup = std::vector<int>(1 << lightsSize, INT32_MAX);
        for (int button: buttons) {
            lookup[button] = 1;
        }
        lookup[0] = 0;
        while (lookup[lights] == INT32_MAX) {
            auto states = std::vector<int>(lookup);
            for (int button: buttons) {
                for (auto [ind, val]: lookup | std::views::enumerate) {
                    if (val == INT32_MAX)
                        continue;
                    auto index = ind ^ button;
                    if (states[index] > val+1)
                        states[index] = val+1;
                }
            }
            lookup = states;
        }
        fmt::println("{} took: {}", lightsString, lookup[lights]);
        sum += lookup[lights];
    }
    fmt::println("final number of presses: {}", sum);

}
auto partTwo(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    long sum = 0l;

    for (auto line = std::string(); std::getline(input, line);) {
        size_t lightsSize = std::distance(line.begin()+1, std::ranges::find(line,']'));
        auto joltsString = std::string(std::ranges::find(line,'{')+1, std::ranges::find(line,'}'));

        auto stringButtons =
            std::string(
                std::ranges::find(line, '('),
                std::ranges::find_last(line, ')').begin()+1
            ) | std::views::split(' ') | std::ranges::to<std::vector<std::string>>();

        auto buttons = std::vector<std::vector<int>>();
        for (auto s: stringButtons) {
            auto stream = std::stringstream(s.substr(1, s.size()-2));
            char c;
            int v;
            int mask = 0;
            buttons.emplace_back(lightsSize);
            while (stream.good()) {
                stream >> v >> c;
                buttons.back()[v] = 1;
            }
        }

        auto jolts = std::vector<int>();
        auto stream = std::stringstream(joltsString);
        char c;
        int v;
        while (stream.good()) {
            stream >> v >> c;
            jolts.push_back(v);
        }
        // fmt::println("{}", jolts);

        //solution
        auto matrix = std::vector<std::vector<int>>();
        for (const auto& button: buttons) {
            matrix.push_back(button);
        }
        matrix.emplace_back(lightsSize, 1);

        for (int i = 0; i < lightsSize; ++i) {

        }

        while (!lookup.contains(jolts)) {
            auto states = std::map(lookup);
            for (const auto& button: buttons) {
                for (const auto& [ind, val]: lookup) {
                    auto index = add(ind,  button);
                    if (!isIndexValid(jolts, index))
                        continue;
                    if (!states.contains(index))
                        states[index] = val + 1;
                    else if (states[index] > val+1)
                        states[index] = val+1;
                }
            }
            lookup = states;
            fmt::println("size: {}, last: {}", lookup.size(), *(--lookup.end()));
        }
        fmt::println("size: {}, last: {}, took: {}", lookup.size(), *(--lookup.end()), lookup[jolts]);
        sum += lookup[jolts];
    }
    fmt::println("final number of presses: {}", sum);

}

auto isIndexValid(const std::vector<int>& jolts, const std::vector<int>& test)-> bool {
    for (int i = 0; i < jolts.size(); ++i) {
        if (test[i] > jolts[i])
            return false;
    }
    return true;
}

auto add(const std::vector<int>& first, const std::vector<int>& second) -> std::vector<int> {
    auto result = std::vector<int>(first.size());
    for (int i = 0; i < first.size(); ++i) {
        result[i] = first[i] + second[i];
    }
    return result;
}

auto main() -> int {
    // partOne("../10/data.txt");
    partTwo("../10/data.txt");
}