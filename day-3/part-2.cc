/**
 * Author: Connor Billings
 * Date  : 18 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 3 - part 2
 **/

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

#include "CC-Utilities/line.hpp"
#include "CC-Utilities/pair-hash.hpp"

using std::cout;

int main()
{
    std::ifstream in{"data"};

    std::unordered_map<std::pair<int, int>, int, pair_hash<int, int>> fabric{};
    std::unordered_set<int> nonoverlapping_ids{};
    std::for_each(std::istream_iterator<line>{in}, {}, [&](const std::string &line) {
        int id, left, top, width, height;
        std::sscanf(data(line), "#%i @%i, %i : %ix%i", &id, &left, &top, &width, &height);

        nonoverlapping_ids.insert(id);
        for (int row = top; row < top + height; ++row)
            for (int col = left; col < left + width; ++col)
                if (auto [it, inserted] = fabric.emplace(std::pair{row, col}, id); !inserted)
                {
                    nonoverlapping_ids.erase(it->second);
                    nonoverlapping_ids.erase(id);
                }
    });

    cout << *nonoverlapping_ids.begin() << std::endl;

    return EXIT_SUCCESS;
}