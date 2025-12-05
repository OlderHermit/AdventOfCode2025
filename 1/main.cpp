#include <iostream>
#include <fstream>
#include <fmt/core.h>

auto main() -> int {

    auto input = std::fstream("../1/data.txt");
    auto val = 0;
    auto c = ' ';
    auto sum = 50;
    auto result = 0;

    while (input.good()) {
        input >> c;
        input >> val;

        if (c == 'L' and sum == 0)
            sum = 100;

        if (c == 'R')
            sum += val;
        else
            sum -= val;

        if (sum > 99) {
            result += sum/100;
            sum = sum % 100;
        } else if (sum <= 0) {
            result += 1 + sum/-100;

            sum = sum % 100;
            if (sum < 0)
                sum += 100;
        }

        // std::cout << sum << '\n';
        // std::cout << c << " " << val << '\n';
        // std::cout << result << '\n';
    }
    std::cout << result << '\n';
    // fmt::println("result is {}", 2);
}