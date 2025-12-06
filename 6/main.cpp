#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>
#include <queue>

#include "fmt/core.h"
#include "fmt/ranges.h"
#include "fmt/ostream.h"

auto doOperation(long a, long b, char op) -> long;

auto partOne(const std::string& filename) -> void {
    auto allData = std::vector<std::vector<int>>();
    auto total = 0l;

    auto input = std::ifstream(filename);

    for (auto line = std::string(); std::getline(input, line);) {
        auto stream = std::stringstream(line);

        auto addRowOfNumbers =
            std::ranges::find_if(line, [](char c) {return c == '+' or c == '*';}) == line.end();

        if (addRowOfNumbers) {
            auto v =
                std::ranges::istream_view<int>(stream) |
                std::ranges::to<std::vector<int>>();

            if (allData.empty())
                for (int & i : v)
                    allData.push_back({i});
            else
                for (int i = 0; i < allData.size(); ++i)
                    allData[i].push_back(v[i]);

        } else {
            auto op = ' ';
            for (auto & vec : allData) {
                stream >> op;
                long sum = vec[0];
                for (auto i = 1; i < vec.size(); ++i) {
                    sum = doOperation(sum, vec[i], op);
                }
                fmt::println("{}",sum);
                total += sum;
            }
        }
    }
    fmt::println("result: {}", total);
}

auto partTwoCursedWay(const std::string& filename) -> void {
    auto total = 0l;
    auto input = std::ifstream(filename);

    size_t maxSize = 0;
    for (auto line = std::string(); std::getline(input, line);) {
        if (maxSize < line.size())
            maxSize = line.size();
    }
    input = std::ifstream(filename);
    auto transposed = std::string(maxSize, '\n');

    for (auto line = std::string(); std::getline(input, line);) {

        auto addRowOfNumbers =
            std::ranges::find_if(line, [](char c) {return c == '+' or c == '*';}) == line.end();

        if (addRowOfNumbers) {
            size_t start = 0;
            for (auto c: line) {
                auto idx = transposed.find('\n', start);
                transposed.insert(idx, std::format("{}", c));
                start = idx+2;
            }
        } else {
            auto opStream = std::stringstream(line);
            auto numStream = std::stringstream(transposed);
            auto op = ' ';
            auto sum = 0l;

            opStream >> op;
            for (auto stringNum = std::string(); std::getline(numStream, stringNum);) {
                bool only_spaces = std::ranges::all_of(stringNum, [](char c) {
                    return std::iswspace(c);
                });

                if (!only_spaces) {
                    auto num = std::atoi(stringNum.c_str());
                    if (sum == 0)
                        sum = num;
                    else
                        sum = doOperation(sum, num, op);
                } else {
                    opStream >> op;
                    total += sum;
                    sum = 0;
                }
            }
            if (sum > 0)
                total += sum;
        }
    }
    fmt::println("result: {}", total);
}

auto partTwo(const std::string& filename) -> void {
    auto total = 0l;
    auto input = std::ifstream(filename);

    size_t maxSize = 0;
    auto context = std::vector<std::string>();
    auto ops = std::queue<char>();

    for (auto line = std::string(); std::getline(input, line);) {
        bool lastLine = std::ranges::find_if(line, [](char c){return c == '+' or c == '*';}) != line.end();

        if (lastLine) {
            std::ranges::remove(line, ' ');
            ops = std::string_view(line) | std::ranges::to<std::queue<char>>();
            break;
        }
        context.push_back(line);
        if (maxSize < line.size())
            maxSize = line.size();
    }

    auto transposed = std::vector(maxSize, std::string());
    for (int i = 0; i < context.size(); ++i) {
        for (int j = 0; j < context[i].size(); ++j) {
            if (context[i][j] != '+' and context[i][j] != '*')
                transposed[j] += context[i][j];
            else
                ops.push(context[i][j]);
        }
    }

    auto sum = 0l;
    auto op = ops.front();
    ops.pop();

    for (auto const& stringNum : transposed) {
        bool only_spaces = std::ranges::all_of(stringNum, [](char c) {
            return std::iswspace(c);
        });

        if (!only_spaces) {
            auto num = std::atoi(stringNum.c_str());
            sum = doOperation(sum, num, op);
        } else {
            op = ops.front();
            ops.pop();
            total += sum;
            sum = 0;
        }
    }
    if (sum > 0)
        total += sum;
    fmt::println("result: {}", total);
}

auto doOperation(long a, long b, char op) -> long{
    switch (op) {
        case '+':
            return a + b;
        case '*':
            if (a == 0)
                return b;
            return a * b;
        default:
            fmt::println(std::cerr, "This shouldn't happen operation not recognised: {}", op);
            return 0;
    }
}
auto main() -> int {
    // partOne("../6/data.txt");
    partTwo("../6/data.txt");
}
