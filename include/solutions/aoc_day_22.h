#ifndef __AOC_DAY_22__
#define __AOC_DAY_22__

#include "aoc_day.h"

class AocDay22 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay22();
        ~AocDay22();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
