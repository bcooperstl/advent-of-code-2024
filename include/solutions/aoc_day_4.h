#ifndef __AOC_DAY_4__
#define __AOC_DAY_4__

#include "aoc_day.h"
#include "screen.h"

class AocDay4 : public AocDay
{
    private:
        vector<string> read_input(string filename);
        int find_xmas_as_line(Screen & screen);
        int find_xmas_as_x(Screen & screen);
    public:
        AocDay4();
        ~AocDay4();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
