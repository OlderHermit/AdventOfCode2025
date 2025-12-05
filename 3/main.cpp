#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <vector>

#include "fmt/core.h"
#include "fmt/ranges.h"

auto removeDigit(std::vector<int> &v) -> void;

auto partOne(const std::string &fileName) -> void {
  auto input = std::ifstream(fileName);
  auto sum = 0;

  for (std::string line; std::getline(input, line);) {
    auto stream = std::stringstream(line);

    auto v = std::ranges::istream_view<char>(stream) |
             std::views::transform(
                 [](const char c) { return static_cast<int>(c - '0'); }) |
             std::ranges::to<std::vector>();

    auto first = std::ranges::max_element(v);

    if (first == --v.end()) {
      auto second = std::ranges::max_element(v.begin(), first);
      sum += 10 * (*second) + *first;
    } else {
      auto second = std::ranges::max_element(first + 1, v.end());
      sum += 10 * (*first) + *second;
    }
  }
  fmt::println("{}", sum);
}

auto partTwo(const std::string &fileName) -> void {
  auto input = std::ifstream(fileName);
  auto sum = 0l;

  for (std::string line; std::getline(input, line);) {
    auto stream = std::stringstream(line);

    auto v = std::ranges::istream_view<char>(stream) |
             std::views::transform(
                 [](const char c) { return static_cast<int>(c - '0'); }) |
             std::ranges::to<std::vector>();

    while (v.size() > 12) {
      const auto it = std::ranges::adjacent_find(
      v, [](const int current, const int next) {
        return current < next;
      });
      if (it != v.end())
        v.erase(it);
      else
        v.pop_back();
    }

    auto current = 0l;
    for (int i : v) {
      current *= 10;
      current += i;
    }
    // fmt::println("{}", v);
    sum += current;
  }
  fmt::println("{}", sum);
}

auto main() -> int {
  // partOne("../data.txt");
  partTwo("../3/data.txt");
}