/**
 * Author: Connor Billings
 * Date  : 4 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 2 - part 1
 **/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

using std::cout;

std::string solve(std::ifstream &in);

int main()
{
    std::ifstream in{"data"};

    cout << solve(in) << std::endl;

    return EXIT_SUCCESS;
}

std::string solve(std::ifstream &in)
{
    std::vector<std::string> data{
        std::istream_iterator<std::string>{in},
        std::istream_iterator<std::string>{}};

    for (auto it1 = begin(data); it1 != end(data) - 1; ++it1)
    {
        auto s1 = *it1;
        auto it2 = std::find_if(it1 + 1, end(data), [&s1](const auto &s2) {
            auto diffs = std::inner_product(begin(s1), end(s1),
                                            begin(s2),
                                            0ul,
                                            std::plus<>{}, std::not_equal_to<>{});

            return diffs == 1;
        });
        auto s2 = *it2;

        if (it2 != end(data))
        {
            s1.erase(std::mismatch(begin(s1), end(s1), begin(s2)).first);
            return s1;
        }
    }

    // Will never be reached
    return std::string{};
}