/**
 * Author: Connor Billings
 * Date  : 19 December 2018
 *
 * Description:
 *  A convenience container for data read from the input of Advent of Code 2018: Day 4
 *
 **/

#ifndef RECORD_HPP
#define RECORD_HPP

#include <string>

struct record
{
    std::string month{}, day{}, hour{}, minute{}, instruction{}, id{};

    record(const std::string &month,
           const std::string &day,
           const std::string &hour,
           const std::string &minute,
           const std::string &instruction,
           const std::string &id)
        : month(month), day(day), hour(hour), minute(minute), instruction(instruction), id(id)
    {
    }

    bool
    operator<(const record &other) const
    {
        if (month < other.month)
            return true;
        else if (month == other.month)
        {
            if (day < other.day)
                return true;
            else if (day == other.day)
            {
                if (hour < other.hour)
                    return true;
                else if (hour == other.hour)
                    if (minute < other.minute)
                        return true;
            }
        }
        return false;
    }
};

#endif