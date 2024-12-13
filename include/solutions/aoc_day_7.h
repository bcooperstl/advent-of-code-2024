#ifndef __AOC_DAY_7__
#define __AOC_DAY_7__

#include "aoc_day.h"

namespace Day7
{
    struct Calibration
    {
        unsigned long long int result;
        vector<unsigned long long int> numbers;
    };
}

using namespace Day7;

class AocDay7 : public AocDay
{
    private:
        void parse_input(string filename, vector<Calibration> & calibraitons);
        bool is_calibration_valid(Calibration calibration);
    public:
        AocDay7();
        ~AocDay7();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
