#include <algorithm>
#include <cmath>
#include <fmt/core.h>
#include <fstream>
#include <string>
#include <vector>
struct Box {
    int x,y,z;

    [[nodiscard]] auto difference(const Box& other) const -> double {
        return std::sqrt(
            pow(x + other.x, 2) + pow(y + other.y, 2) + pow(z + other.z, 2)
        );
    }
};

struct Circuit {
    std::vector<Box> boxes;

    [[nodiscard]] auto difference(const Circuit& other) const -> double {
        double min = boxes[0].difference(other.boxes[0]);
        for (const auto& box : other.boxes) {
            auto elem = std::ranges::min(boxes, {}, [box](const Box& elem){return box.difference(elem);});
            min = std::ranges::min(min, box.difference(elem));
        }
        return min;
    }

    Circuit(int x, int y, int z) : boxes(std::vector({Box(x,y,z)})) {}
};

auto partOne(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    auto circuits = std::vector<Circuit>();

    while (input.good()) {
        int x,y,z;
        char c;
        input >> x >> c >> y >> c >> z;
        circuits.emplace_back(x,y,z);
        // fmt::println("{},{},{}", x,y,z);
    }

    for (int i = 0; i < 10; ++i) {
        for (auto circuit: circuits) {

        }
    }
}

auto main() -> int {
    partOne("../8/example.txt");
}
