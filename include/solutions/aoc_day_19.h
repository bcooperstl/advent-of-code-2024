#ifndef __AOC_DAY_19__
#define __AOC_DAY_19__

#include "aoc_day.h"

class AocDay19 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay19();
        ~AocDay19();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
