/**
 * Author: Connor Billings
 * Date  : 19 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 5 - part 2
 **/

/*****************************************************************************/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stack>
#include <string>
#include <unordered_set>

/*****************************************************************************/

using std::cout;

/*****************************************************************************/

std::unordered_set<std::string>
get_reduced_polymers(const std::string &polymer);

unsigned long
react(const std::string &polymer);

/*****************************************************************************/

int main()
{
    std::ifstream in{"data"};

    std::string polymer{std::istream_iterator<char>{in}, {}};

    auto reduced_polymers = get_reduced_polymers(polymer);

    auto min_units = std::accumulate(begin(reduced_polymers), end(reduced_polymers), size(polymer),
                                     [](auto min_units, const auto &r_polymer) {
                                         return std::min(react(r_polymer), min_units);
                                     });

    cout << min_units << std::endl;

    return EXIT_SUCCESS;
}

/*****************************************************************************/
// Returns an unordered_set of all unique reduced polymers (polymers with a given letter removed)

std::unordered_set<std::string>
get_reduced_polymers(const std::string &polymer)
{
    std::unordered_set<std::string> reduced_polymers{};
    for (char r_unit = 'a'; r_unit <= 'z'; ++r_unit)
    {
        std::string r_polymer{};
        r_polymer.reserve(size(polymer));

        std::remove_copy_if(begin(polymer), end(polymer), std::back_inserter(r_polymer), [=](auto u) {
            return std::tolower(u) == r_unit;
        });

        reduced_polymers.insert(r_polymer);
    }
    return reduced_polymers;
}

/*****************************************************************************/
// Returns the number of units left in a polymer after it reacts

unsigned long
react(const std::string &polymer)
{
    std::stack<char> units{};
    std::for_each(begin(polymer), end(polymer), [&](auto u) {
        if (size(units) == 0)
            units.push(u);
        else
        {
            // The units must be opposite cases, using a difference will accomplish this
            static const int char_diff = 'a' - 'A';
            if (std::abs(u - units.top()) == char_diff)
                units.pop();
            else
                units.push(u);
        }
    });
    return size(units);
}
