/**
 * Author: Connor Billings
 * Date  : 19 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 5 - part 1
 **/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stack>

using std::cout;

int main()
{
    std::ifstream in{"data"};

    std::stack<char> units{};
    std::for_each(std::istream_iterator<char>{in}, {}, [&](auto u) {
        if (size(units) == 0)
            units.push(u);
        else
        {
            static const int char_diff = 'a' - 'A';
            if (std::abs(u - units.top()) == char_diff)
                units.pop();
            else
                units.push(u);
        }
    });

    cout << size(units) << std::endl;

    return EXIT_SUCCESS;
}
