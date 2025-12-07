#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <map>

#include "fmt/core.h"
#include "fmt/ranges.h"

auto partOne(const std::string& filename) -> void {
    auto nodes = std::set<int>();
    auto input = std::ifstream(filename);
    auto line = std::string();
    auto counter = 0;
    std::getline(input, line);

    nodes.insert(line.find('S'));

    while (std::getline(input, line)) {
        if (!line.contains('^'))
            continue;

        auto newNodes = std::set<int>();

        for (auto [i, c] : line | std::views::enumerate) {
            if (c == '^' and nodes.contains(i)) {
                newNodes.insert(i-1);
                newNodes.insert(i+1);
                nodes.erase(i);
                counter++;
            }
        }
        nodes.merge(newNodes);
    }
    fmt::println("{}", counter);
}

auto partTwo(const std::string& filename) -> void {
    auto nodes = std::map<size_t, long>();
    auto input = std::ifstream(filename);
    auto line = std::string();
    long counter = 0;
    std::getline(input, line);

    nodes.insert({line.find('S'), 1});

    while (std::getline(input, line)) {
        if (!line.contains('^'))
            continue;

        auto newNodes = std::map<size_t, long>();

        for (auto [i, c] : line | std::views::enumerate) {
            if (c == '^' and nodes.contains(i)) {
                newNodes[i+1] += nodes[i];
                newNodes[i-1] += nodes[i];
                nodes.erase(i);
            } else if (nodes.contains(i)) {
                newNodes[i] += nodes[i];
                nodes.erase(i);
            }
        }
        nodes = newNodes;
        // fmt::println("{}", nodes | std::views::values);
    }
    for (auto v: nodes | std::views::values) {
        counter += v;
    }
    fmt::println("{}", counter);
}

auto main() -> int {
    // partOne("../7/data.txt");
    partTwo("../7/data.txt");
}
/*
123456789012345  012345678901234
.......S.......         1
.......|.......         1
......|^|......        1^1
......|.|......        1 1
.....|^|^|.....       1^2^1
.....|.|.|.....       1 2 1
....|^|^|^|....      1^3 3^1
....|.|.|.|....      1 3 3 1
...|^|^|||^|...     1^4^331^1
...|.|.|||.|...     1 4 331 1
..|^|^|||^|^|..    1^5^434^2^1
..|.|.|||.|.|..    1 5 434 2 1
.|^|||^||.||^|.   1^154^74 21^1
.|.|||.||.||.|.   1 154 74 21 1
|^|^|^|^|^|||^|  1^2^0^!^!^211^1 = 1 + 2 + 10 + 11 + 11 + 2 + 1 + 1 + 1 = 3 + 10 + 11 + 11 + 5 = 3 + 32 + 5 = 40
|.|.|.|.|.|||.|

*/