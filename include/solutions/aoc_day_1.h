#ifndef __AOC_DAY_1__
#define __AOC_DAY_1__

#include "aoc_day.h"

class AocDay1 : public AocDay
{
    private:
        void parse_input(string filename, vector<long> & left_list, vector<long> & right_list);
    public:
        AocDay1();
        ~AocDay1();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
