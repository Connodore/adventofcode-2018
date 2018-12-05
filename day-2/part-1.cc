/**
 * Author: Connor Billings
 * Date  : 4 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 2 - part 1
 **/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_set>
#include <utility>

using std::cout;

int main()
{
    std::ifstream in{"data"};

    auto [twos, threes] = std::accumulate(std::istream_iterator<std::string>{in},
                                          std::istream_iterator<std::string>{},
                                          std::pair{0ul, 0ul},
                                          [](const auto &accum, const auto &s) {
                                              std::unordered_multiset<char> letters{begin(s), end(s)};

                                              bool hasTwo = false, hasThree = false;
                                              for (auto it = begin(letters); it != end(letters);)
                                              {
                                                  auto count = letters.count(*it);
                                                  hasTwo = hasTwo ? hasTwo : count == 2;
                                                  hasThree = hasThree ? hasThree : count == 3;
                                                  std::advance(it, count);
                                              }

                                              return std::pair{accum.first + (hasTwo ? 1 : 0),
                                                               accum.second + (hasThree ? 1 : 0)};
                                          });

    cout << twos * threes << std::endl;

    return EXIT_SUCCESS;
}