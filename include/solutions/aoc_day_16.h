#ifndef __AOC_DAY_16__
#define __AOC_DAY_16__

#include "aoc_day.h"

class AocDay16 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay16();
        ~AocDay16();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
