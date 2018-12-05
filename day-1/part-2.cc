/**
 * Author: Connor Billings
 * Date  : 3 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 1 - part 2
 **/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

using std::cin;
using std::cout;

long solve(std::ifstream &in);

int main()
{
    std::ifstream in{"data"};
    cout << solve(in) << std::endl;

    return EXIT_SUCCESS;
}

long solve(std::ifstream &in)
{
    std::vector<long> seq{
        std::istream_iterator<long>{in},
        std::istream_iterator<long>{}};

    long curr_freq = 0;
    std::unordered_set<long> freqs = {0};
    do
    {
        for (auto change : seq)
        {
            curr_freq += change;
            if (auto [_, inserted] = freqs.insert(curr_freq); !inserted)
                return curr_freq;
        }
    } while (true);
}