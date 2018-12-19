/**
 * Author: Connor Billings
 * Date  : 19 December 2018
 *
 * Description:
 *  Solution for Advent of Code: Day 4 - part 1
 **/

/*****************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

/*****************************************************************************/

#include "CC-Utilities/line.hpp"
#include "record.hpp"

/*****************************************************************************/

using std::cout;

/*****************************************************************************/

std::set<record>
get_records(std::ifstream &in);

template <class RecordIt>
std::unordered_map<int, std::unordered_multiset<int>>
get_sleeptimes(RecordIt first, RecordIt last);

template <class SleepIt>
std::pair<int, int>
find_max(SleepIt first, SleepIt last);

/*****************************************************************************/

int main()
{
    std::ifstream in{"data"};

    auto records = get_records(in);
    auto sleeptimes = get_sleeptimes(begin(records), end(records));
    auto [id, minute] = find_max(begin(sleeptimes), end(sleeptimes));

    cout << id * minute << std::endl;

    return EXIT_SUCCESS;
}

/*****************************************************************************/
// Reads in and parses the data into a set of 'record' objects

std::set<record>
get_records(std::ifstream &in)
{
    std::set<record> records{};
    std::for_each(std::istream_iterator<line>{in}, {}, [&](const std::string &line) {
        static std::regex rgx{"^\\[\\d{4}-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2})\\] ([a-zA-Z]+) (?:#(\\d+))?"};

        std::smatch matches{};
        std::regex_search(line, matches, rgx);

        records.emplace(matches[1], matches[2], matches[3], matches[4], matches[5], matches[6]);
    });
    return records;
}

/*****************************************************************************/
// Returns an unordered_map of each guard's ID to an unordered_multiset counting the minutes each guard slept

template <class RecordIt>
std::unordered_map<int, std::unordered_multiset<int>>
get_sleeptimes(RecordIt first, RecordIt last)
{
    std::unordered_map<int, std::unordered_multiset<int>> sleeptimes{};

    int curr_id{};
    for (auto it1 = first, it2 = next(first);
         it2 != last;
         advance(it1, 1), advance(it2, 1))
    {
        if (auto inst = it1->instruction; inst == "Guard")
            curr_id = stoi(it1->id);
        else if (inst == "falls")
        {
            int start = stoi(it1->minute), end = stoi(it2->minute);
            for (int min = start; min < end; ++min)
                sleeptimes[curr_id].insert(min);
        }
    }
    return sleeptimes;
}

/*****************************************************************************/
// Returns a pair of the ID (.first) of the guard who slept the most minutes and the minute (.second) that the guard slept the most during.

template <class SleepIt>
std::pair<int, int>
find_max(SleepIt first, SleepIt last)
{
    // Find guard with most minutes
    auto [id, minutes] = *std::max_element(first, last, [](const auto &lhs, const auto &rhs) {
        return size(lhs.second) < size(rhs.second);
    });

    // Find the most common minute of the max guard
    std::pair<int, int> max_minute = {*begin(minutes), minutes.count(*begin(minutes))};
    for (auto it = std::next(begin(minutes), max_minute.second); it != end(minutes);)
    {
        std::pair<int, int> minute = {*it, minutes.count(*it)};
        max_minute = std::max(minute, max_minute, [&](const auto &lhs, const auto &rhs) {
            return lhs.second < rhs.second;
        });

        std::advance(it, minute.second);
    }

    return {id, max_minute.first};
}