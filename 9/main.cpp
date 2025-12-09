#include <algorithm>
#include <cmath>
#include <fmt/base.h>
#include <fstream>
#include <vector>
#include <queue>


struct Point {
    long x,y;

    [[nodiscard]] auto box(const Point &other) const -> ulong {
        return static_cast<ulong>(std::abs(x - other.x)+1) * (std::abs(y - other.y)+1);
    }

    auto operator==(const Point &other) const -> bool {
        return x == other.x and y == other.y;
    }
};

auto contains(const std::pair<Point, Point>& pair, Point test) -> bool;
auto insideShape(const Point& start, const Point& mid, const Point& stop, const Point& next) -> bool;
auto containsOrEqual(const std::pair<Point, Point>& pair, Point test)-> bool;
auto sameSymbol(long first, long second) -> bool;
auto worksCase1(const Point& a, const Point& b) -> bool;

auto partOne(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    auto points = std::vector<Point>();
    auto pairs = std::vector<std::pair<Point,Point>>();

    while (input.good()) {
        int x,y;
        char c;
        input >> x >> c >> y;
        points.emplace_back(x,y);
    }

    for (int i = 0; i < points.size(); ++i) {
        for (int j = i+1; j < points.size(); ++j) {
            pairs.emplace_back(points[i], points[j]);
        }
    }
    std::ranges::sort(pairs, {}, [](const std::pair<Point, Point>& p){return p.first.box(p.second);});

    auto pair = pairs.back();
    fmt::println("box: {}", pair.first.box(pair.second));
    fmt::println("{}, {} - {}, {}", pair.first.x, pair.first.y, pair.second.x, pair.second.y);
}

auto partTwo(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    ulong biggest = 0;
    auto points = std::vector<Point>();
    auto pairs = std::vector<std::pair<Point,Point>>();

    while (input.good()) {
        int x,y;
        char c;
        input >> x >> c >> y;
        points.emplace_back(x,y);
    }

    for (int i = 0; i < points.size(); ++i) {
        for (int j = i+1; j < points.size(); ++j) {
            pairs.emplace_back(points[i], points[j]);
        }
    }

    std::ranges::sort(pairs, {}, [](const std::pair<Point, Point>& p){return p.first.box(p.second);});
    std::ranges::reverse(pairs);

    auto maxY = std::ranges::max(points,{},[](const Point& p){return p.y;}).y;
    auto minY = std::ranges::min(points,{},[](const Point& p){return p.y;}).y;
    auto rows = std::vector<std::pair<long,long>>(maxY-minY+1);
    points.push_back(points.front());
    for (int i = 0; i < points.size()-1; ++i) {
        const auto& start = points[i];
        const auto& stop = points[i+1];

        long low = std::min(start.y, stop.y);
        long high = std::max(start.y, stop.y);

        for (long j = low; j <= high; j++) {
            auto& [min, max] = rows[j - minY];
            if (min == 0 and max == 0) {
                min = max = start.x;
            }
            min = std::min(start.x, min);
            max = std::max(start.x, max);
        }
    }
    points.pop_back();

    for (const auto& [start, stop]: pairs) {
        long low = std::min(start.y, stop.y);
        long high = std::max(start.y, stop.y);

        long min = std::min(start.x, stop.x);
        long max = std::max(start.x, stop.x);

        bool correct = true;
        for (long i = low; i <= high; i++) {
            auto [testMin, testMax] = rows[i - minY];
            if(min < testMin or max > testMax) {
                correct = false;
                break;
            }
        }
        if (correct) {
            fmt::println("{}", start.box(stop));
            fmt::println("{}, {} - {}, {}", start.x, start.y, stop.x, stop.y);
            break;
        }
    }
}

auto main() -> int {
    // partOne("../9/data.txt");
    partTwo("../9/example.txt");
    partTwo("../9/data.txt");
}
