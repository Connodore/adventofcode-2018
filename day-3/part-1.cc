/**
 * Author: Connor Billings
 * Date  : 18 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 3 - part 1
 **/

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_set>

#include "CC-Utilities/line.hpp"
#include "CC-Utilities/pair-hash.hpp"

using std::cout;

int main()
{
    std::ifstream in{"data"};

    std::unordered_multiset<std::pair<int, int>, pair_hash<int, int>> fabric{};
    std::for_each(std::istream_iterator<line>{in}, {}, [&](const std::string &line) {
        int left, top, width, height;
        std::sscanf(data(line), "#%*i @%i, %i : %ix%i", &left, &top, &width, &height);

        for (int row = top; row < top + height; ++row)
            for (int col = left; col < left + width; ++col)
                fabric.emplace(row, col);
    });

    unsigned long long total = 0;
    for (auto it = begin(fabric); it != end(fabric);)
    {
        auto count = fabric.count(*it);
        total += count > 1 ? 1 : 0;
        advance(it, count);
    }

    cout << total << std::endl;

    return EXIT_SUCCESS;
}