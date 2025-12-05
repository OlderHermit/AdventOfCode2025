#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <ranges>

#include "fmt/core.h"

auto adjectentCount(const std::vector<std::vector<bool>>& vec, int row, int col) -> int;
auto adjectentCount(const std::vector<std::vector<char>>& vec, int row, int col) -> int;

auto partTwo(const std::string &fileName) -> void {
    auto input = std::ifstream(fileName);
    auto isRoll = std::vector<std::vector<char>>();
    auto counter = 0;
    auto removed = 0;

    for (std::string line; std::getline(input, line);) {
        auto stream = std::stringstream(line);
        auto lineVector =
            std::ranges::istream_view<char>(stream) |
            std::ranges::to<std::vector<char>>();
        isRoll.push_back(lineVector);
    }

    auto shouldContinue = true;
    while (shouldContinue) {
        for (int i = 0; i < isRoll.size(); ++i) {
            for (int j = 0; j < isRoll[i].size(); ++j) {
                if (isRoll[i][j] == '@' && adjectentCount(isRoll, i, j) < 4) {
                    isRoll[i][j] = 'x';
                    counter++;
                }
            }
        }
        for (auto& v: isRoll) {
            std::ranges::transform(v.begin(), v.end(), v.begin(), [](const char c) {if (c == 'x') return '.'; return c;});
        }
        shouldContinue = counter != 0;
        removed += counter;
        counter = 0;
    }
    fmt::println("{}", removed);
}

auto partOne(const std::string &fileName) -> void {
    auto input = std::ifstream(fileName);
    auto isRoll = std::vector<std::vector<bool>>();
    auto counter = 0;

    for (std::string line; std::getline(input, line);) {
        auto stream = std::stringstream(line);
        auto lineVector =
            std::ranges::istream_view<char>(stream) |
            std::views::transform([](const char c) { return c == '@'; }) |
            std::ranges::to<std::vector<bool>>();
        isRoll.push_back(lineVector);
    }

    for (int i = 0; i < isRoll.size(); ++i) {
        for (int j = 0; j < isRoll[i].size(); ++j) {
            if (isRoll[i][j] && adjectentCount(isRoll, i, j) < 4) {
                counter++;
            }
        }
    }
    fmt::println("{}", counter);
}

auto adjectentCount(const std::vector<std::vector<char>>& vec, int row, int col) -> int {
    int row_start = std::max(row-1, 0);
    int row_end = std::min(row+1, static_cast<int>(vec.size())-1);
    int col_start = std::max(col-1, 0);
    int col_end = std::min(col+1, static_cast<int>(vec[row].size())-1);
    int counter = 0;

    for (int i = row_start; i <= row_end; ++i) {
        for (int j = col_start; j <= col_end; ++j) {
            if (vec[i][j] != '.')
                counter++;
        }
    }
    return counter-1;
}

auto adjectentCount(const std::vector<std::vector<bool>>& vec, int row, int col) -> int {
    int row_start = std::max(row-1, 0);
    int row_end = std::min(row+1, static_cast<int>(vec.size())-1);
    int col_start = std::max(col-1, 0);
    int col_end = std::min(col+1, static_cast<int>(vec[row].size())-1);
    int counter = 0;

    for (int i = row_start; i <= row_end; ++i) {
        for (int j = col_start; j <= col_end; ++j) {
            if (vec[i][j])
                counter++;
        }
    }
    return counter-1;
}

auto main() -> int {
    // partOne("../4/data.txt");
    partTwo("../4/data.txt");
}
