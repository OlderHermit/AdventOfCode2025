#include <iostream>
#include <fstream>

#include "fmt/core.h"

auto isSequentialForDiv(const std::string& str, size_t div) -> bool;
auto isSequential(const std::string& str) -> bool;

auto partOne(const std::string& fname) -> void{
    auto input = std::ifstream(fname);

    auto min = 0l;
    auto max = 0l;
    auto sum = 0l;

    while (input.good()) {
        input >> min;
        input.ignore();
        input >> max;
        input.ignore();

        for (long i = min; i <= max; i++) {
            auto size = fmt::format("{}", i).length();

            if (size % 2 != 0)
                continue;

            long divisor = pow(10, size/2);
            auto first = i / divisor;
            auto second = i % divisor;
            if (first == second) {
                sum += i;
                fmt::println("{}", i);
            }
        }
        // fmt::println("{} - {}", min, max);
    }
    fmt::println("final value of sum: {}!", sum);
}

auto partTwo(const std::string& fname) -> void{
    auto input = std::ifstream(fname);

    auto min = 0l;
    auto max = 0l;
    auto sum = 0l;

    while (input.good()) {
        input >> min;
        input.ignore();
        input >> max;
        input.ignore();

        for (long num = min; num <= max; num++) {
            auto str = fmt::format("{}", num);
            if (isSequential(str))
                sum += num;
        }
    }
    fmt::println("final value of sum: {}!", sum);
}

auto isSequential(const std::string& str) -> bool {
    for (auto i = str.size()/2; i >= 1; i--) {
        if (str.size() % i != 0)
            continue;
        if (isSequentialForDiv(str, i)) {
            // fmt::println("{} for div: {}", str, i);
            return true;
        }
    }
    return false;
}

auto isSequentialForDiv(const std::string& str, size_t div) -> bool{
    auto test = str.substr(0, div);
    for (auto j = div; j < str.size(); j += div) {
        if (test != str.substr(j, div)) {
            return false;
        }
    }
    return true;
}


int main() {
    // partOne("./data.txt");
    // fmt::println("{}", isSequencialForDiv("999", 1));
    partTwo("../2/data.txt");
}
