#include <algorithm>
#include <cmath>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Box {
    int x,y,z;

    [[nodiscard]] auto difference(const Box& other) const -> double {
        return std::sqrt(
            pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2)
        );
    }

    auto operator==(const Box& other) const -> bool {
        return x == other.x and y == other.y and z == other.z;
    }

    auto operator<(const Box& other) const -> bool {
        return (std::pow(x,2) + std::pow(y,2) + std::pow(z,2)) <
               (std::pow(other.x,2) + std::pow(other.y,2) + std::pow(other.z,2));
    }
};

auto partOne(const std::string& filename, int count) -> void {
    auto input = std::ifstream(filename);
    auto data = std::vector<std::pair<Box, Box>>();

    auto boxes = std::vector<Box>();
    while (input.good()) {
        int x,y,z;
        char c;
        input >> x >> c >> y >> c >> z;
        boxes.emplace_back(x,y,z);
        // fmt::println("{},{},{}", x,y,z);
    }

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i+1; j < boxes.size(); j++) {
            data.emplace_back(boxes[i],boxes[j]);
        }
    }

    std::ranges::sort(data,{}, [](const std::pair<Box,Box>& p){return p.first.difference(p.second);});
    auto result = std::vector<std::vector<Box>>();
    for (int i = 0; i < count; ++i) {
        auto found1 = result.end();
        auto found2 = result.end();
        for (auto idx = result.begin(); idx != result.end(); ++idx) {
            if (std::ranges::find(idx->begin(), idx->end(), data[i].first) != idx->end()) {
                found1 = idx;
            }
            if (std::ranges::find(idx->begin(), idx->end(), data[i].second) != idx->end()) {
                found2 = idx;
            }
        }
        if (found2 == result.end() and found1 == result.end()) {
            result.push_back({ data[i].first, data[i].second });
        } else if (found2 == result.end()) {
            found1->push_back(data[i].second);
        } else if (found1 == result.end()) {
            found2->push_back(data[i].first);
        } else if (found1 != found2) {
            found1->append_range(*found2);
            result.erase(found2);
        }
    }

    ulong sum = 1;
    for (int i = 0; i < 3; ++i) {
        auto idx = std::ranges::max_element(result,{},std::ranges::size);
        sum *= idx->size();
        result.erase(idx);
    }
    fmt::println("{}", sum);
}

auto partTwo(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    auto data = std::vector<std::pair<Box, Box>>();

    auto boxes = std::vector<Box>();
    while (input.good()) {
        int x,y,z;
        char c;
        input >> x >> c >> y >> c >> z;
        boxes.emplace_back(x,y,z);
        // fmt::println("{},{},{}", x,y,z);
    }

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i+1; j < boxes.size(); j++) {
            data.emplace_back(boxes[i],boxes[j]);
        }
    }

    std::ranges::sort(data,{}, [](const std::pair<Box,Box>& p){return p.first.difference(p.second);});
    auto result = std::vector<std::vector<Box>>();
    for (const auto &[first, second] : data) {
        auto found1 = result.end();
        auto found2 = result.end();
        for (auto idx = result.begin(); idx != result.end(); ++idx) {
            if (std::ranges::find(idx->begin(), idx->end(), first) != idx->end()) {
                found1 = idx;
            }
            if (std::ranges::find(idx->begin(), idx->end(), second) != idx->end()) {
                found2 = idx;
            }
        }
        if (found2 == result.end() and found1 == result.end()) {
            result.push_back({ first, second });
        } else if (found2 == result.end()) {
            found1->push_back(second);
        } else if (found1 == result.end()) {
            found2->push_back(first);
        } else if (found1 != found2) {
            if (found1->size() + found2->size() == boxes.size()) {
                long calculated = static_cast<long>(first.x) * second.x;
                fmt::println("{}", calculated);
                return;
            }
            found1->append_range(*found2);
            result.erase(found2);
        }

    }
}

auto main() -> int {
    // partOne("../8/data.txt",1000);
    partTwo("../8/data.txt");
}
