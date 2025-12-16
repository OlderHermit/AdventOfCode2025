#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <sstream>
#include <vector>

/*
#####.
#####.
#####.#
....###
#####.#
#####.
#####.



0:
###
##.
##.

1:
###
##.
.##

2:
.##
###
##.

3:
##.
###
##.

4:
###
#..
###

5:
###
.#.
###
*/

auto partOne(const std::string& filename) -> void {
    auto input = std::ifstream(filename);

    auto data = std::vector<std::pair<std::pair<int,int>, std::vector<int>>>();
    int x,y,v;
    char c;
    for (std::string line; std::getline(input, line);) {
        auto stream = std::stringstream(line);
        stream >> x >> c >> y;
        data.push_back({{x,y},{}});

        stream >> c;
        while (stream.good()) {
            stream >> v;
            data.back().second.push_back(v);
        }
    }

    int results = 0;
    for (auto& [sizePair, boxes]: data) {
        //outdated
        //0 & 2 | 3 & 1 => if 0 & 1 | if 2 - | if 3 0 then 4
        // 5
        // each pair 0 & 2 1 & 3 -> 2 corners for 5 (H)

        // auto tmp = *(std::ranges::min(boxes.begin(), boxes.end()+4))/2;
        // auto formation1 = std::ranges::min(tmp, boxes[5]);
        int count = 0;
        std::ranges::for_each(boxes, [&count](int i) {count+=i;});
        fmt::println("{}", count);
        fmt::println("{}", boxes);

        if (sizePair.first/3 * (sizePair.second/3) >= count)
            results++;
    }

    fmt::println("{}", results);
}

auto main() -> int {
    //317 too low
    partOne("../12/data.txt");
}
