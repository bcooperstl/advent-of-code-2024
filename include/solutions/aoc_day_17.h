#ifndef __AOC_DAY_17__
#define __AOC_DAY_17__

#include "aoc_day.h"

class AocDay17 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay17();
        ~AocDay17();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
