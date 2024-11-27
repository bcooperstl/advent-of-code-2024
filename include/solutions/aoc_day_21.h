#ifndef __AOC_DAY_21__
#define __AOC_DAY_21__

#include "aoc_day.h"

class AocDay21 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay21();
        ~AocDay21();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
