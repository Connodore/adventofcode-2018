/**
 * Author: Connor Billings
 * Date  : 1 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 1 - part 1
 *
 * Notes:
 *  I learned that I could create iterators from streams
 *  from: https://www.linuxtopia.org/online_books/programming_books/c++_practical_programming/c++_practical_programming_142.html
 **/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>

using std::cout;

int main()
{
    std::ifstream in{"data"};

    cout << std::accumulate(std::istream_iterator<long>{in},
                            std::istream_iterator<long>{},
                            0l);

    return EXIT_SUCCESS;
}