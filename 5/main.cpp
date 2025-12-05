#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

auto partOne(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    auto init = true;
    auto data = std::vector<std::pair<long, long>>();
    auto counter = 0;

    while (input.good()) {
        auto line = std::string();
        std::getline(input, line);

        if (line.empty()) {
            init = false;
            continue;
        }

        if (init) {
            auto first = std::stol(line.substr(0, line.find('-')));
            auto last = std::stol(line.substr(line.find('-')+1));
            data.emplace_back(first, last);
        } else {
            auto check = std::stol(line);
            for (auto [min, max] : data) {
                if (check >= min and check <= max) {
                    counter++;
                    break;
                }
            }
        }
    }
    std::cout << counter << std::endl;

}

auto partTwo(const std::string& filename) -> void {
    auto input = std::ifstream(filename);
    auto data = std::vector<std::pair<long, long>>();
    auto lastInscribed = 0l;
    auto counter = 0l;

    while (input.good()) {
        auto line = std::string();
        std::getline(input, line);

        if (line.empty()) {
            break;
        }

        auto first = std::stol(line.substr(0, line.find('-')));
        auto last = std::stol(line.substr(line.find('-')+1));
        data.emplace_back(first, last);

    }
    std::ranges::sort(data, {}, [](std::pair<long,long> p) {return p.first;});

    for (auto [min, max] : data) {
        //zakresy nie połączone
        if (min > lastInscribed) {
            counter += max - min + 1;
            lastInscribed = max;
        } else if (max > lastInscribed) {
            counter += max - lastInscribed;
            lastInscribed = max;
        }
    }

    std::cout << counter << std::endl;

}

auto main() -> int {
    //too low 320373444626457
    //        344813017450467
    // partTwo("../example.txt");
    partTwo("../5/data.txt");
}