#ifndef __AOC_DAY_23__
#define __AOC_DAY_23__

#include "aoc_day.h"

class AocDay23 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay23();
        ~AocDay23();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
