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

using std::cout;

#include "~/Workspace/CC-Utilites"

class line
{
    std::string data;

  public:
    friend std::istream &operator>>(std::istream &in, line &l)
    {
        return std::getline(in, l.data);
    }

    operator std::string() const
    {
        return data;
    }
};

template <class T1, class T2>
struct pair_hash
{
    using pair_type = std::pair<T1, T2>;

    size_t
    operator()(const pair_type &p) const
    {
        size_t h1 = std::hash<T1>{}(p.first);
        size_t h2 = std::hash<T2>{}(p.second);

        return h1 ^ (h2 << 1);
    }
};

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