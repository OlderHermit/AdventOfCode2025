#include <algorithm>
#include <array>
#include <bitset>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <map>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <vector>

auto solveCaseFromPartTwo(std::vector<int> jolts, const std::vector<std::vector<int>>& buttons) -> long;
auto divVectorBy2(std::vector<int>& vec1) -> void;
auto subVectors(std::vector<int>& vec1, const std::vector<int>& vec2) -> void;
auto findSolutionsToFirst(const std::vector<int>& patern, const std::vector<std::vector<int>>& buttons) -> std::vector<std::vector<int>>;
auto xorVectors(std::vector<int>& vec1, const std::vector<int>& vec2) -> void;

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

        auto cur = solveCaseFromPartTwo(jolts, buttons);
        fmt::println("solitions: {}", cur);
        sum += cur;
    }
    fmt::println("final number of presses: {}", sum);

}

auto recursive(std::vector<int> patern, std::vector<int> jolts, const std::vector<std::vector<int>>& buttons) -> long {
    if (std::ranges::all_of(jolts, [](int e){return e == 0;}))
        return 0;

    if (std::ranges::all_of(jolts, [](int e){return e <= 0;}))
        return 1000000l;

    auto solutions = findSolutionsToFirst(patern, buttons);
    auto counts = std::vector<long>(solutions.size(), 0);
    for (auto [id, solution] : solutions | std::views::enumerate) {
        auto tmpJolts = jolts;
        for (int i = 0; i < solution.size(); ++i) {
            if (solution[i] == 1) {
                subVectors(tmpJolts, buttons[i]);
                counts[id]++;
            }
        }
        divVectorBy2(tmpJolts);
        std::ranges::transform(tmpJolts, patern.begin(), [](int e){return e % 2;});
        counts[id] += 2 * recursive(patern, tmpJolts, buttons);
    }
    if (counts.empty())
        return 1000000l;
    return std::ranges::min(counts);
}

auto solveCaseFromPartTwo(std::vector<int> jolts, const std::vector<std::vector<int>>& buttons) -> long {
    auto patern = std::vector<int>(jolts.size());

    std::ranges::transform(jolts, patern.begin(), [](int e){return e % 2;});

    fmt::print("Patern {}\t", patern);
    auto res = recursive(patern,jolts, buttons);
    return res;
}

auto findSolutionsToFirst(const std::vector<int>& patern, const std::vector<std::vector<int>>& buttons) -> std::vector<std::vector<int>>{
    long max = 1 << buttons.size();
    auto results = std::vector<std::vector<int>>();
    for (long i = 0; i < max; i++) {
        auto testPatern = std::vector<int>(buttons.front().size(), 0);
        for (int j = 0; j < buttons.size(); j++) {
            if (i >> j & 1) {
                xorVectors(testPatern, buttons[j]);
            }
        }

        if (testPatern == patern) {
            auto tmp = std::vector(buttons.size(),0);
            for (int k = i, j = 0; k > 0; k >>= 1, j++) {
                if (k & 1)
                    tmp[j] = 1;
            }
            results.emplace_back(tmp);
            // fmt::println("{:0{}b}", test, buttons.size());
            // fmt::println("{}", tmp);
        }
    }
    return results;
}
// auto tmp(const std::vector<int>& patern, const std::vector<std::vector<int>>& buttons) {
//     auto lookup = std::vector(1 << patern.size(), INT32_MAX);
//     auto save = std::vector(1 << patern.size(), std::vector(buttons.size(), 0));
//     for (int button: buttons) {
//         lookup[button] = 1;
//     }
//     lookup[0] = 0;
//     while (lookup[lights] == INT32_MAX) {
//         auto states = std::vector<int>(lookup);
//         for (int button: buttons) {
//             for (auto [ind, val]: lookup | std::views::enumerate) {
//                 if (val == INT32_MAX)
//                     continue;
//                 auto index = ind ^ button;
//                 if (states[index] > val+1)
//                     states[index] = val+1;
//             }
//         }
//         lookup = states;
//     }
//     fmt::println("{} took: {}", lightsString, lookup[lights]);
//     sum += lookup[lights];
// }

auto xorVectors(std::vector<int>& vec1, const std::vector<int>& vec2) -> void {
    for (int i = 0; i < vec1.size(); ++i) {
        vec1[i] ^= vec2[i];
    }
}

auto subVectors(std::vector<int>& vec1, const std::vector<int>& vec2) -> void {
    for (int i = 0; i < vec1.size(); ++i) {
        vec1[i] -= vec2[i];
    }
}

auto divVectorBy2(std::vector<int>& vec1) -> void {
    for (int i = 0; i < vec1.size(); ++i) {
        vec1[i] /= 2;
    }
}

auto main() -> int {
    // partOne("../10/data.txt");
    // partTwo("../10/example.txt");
    //34_016_159 too much
    //16394 too low
    //16632 too high
    //VERY SLOW ~ 15 min (due to brute force for paterns)
    partTwo("../10/data.txt");
}