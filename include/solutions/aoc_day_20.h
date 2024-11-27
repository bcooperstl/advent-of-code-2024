#ifndef __AOC_DAY_20__
#define __AOC_DAY_20__

#include "aoc_day.h"

class AocDay20 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay20();
        ~AocDay20();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
