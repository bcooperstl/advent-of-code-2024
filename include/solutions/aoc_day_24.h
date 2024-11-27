#ifndef __AOC_DAY_24__
#define __AOC_DAY_24__

#include "aoc_day.h"

class AocDay24 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay24();
        ~AocDay24();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
