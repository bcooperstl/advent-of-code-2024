#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

#define DAY_2_MAX_LEVELS 8

namespace Day2
{
    enum Direction
    {
        increasing = 0,
        decreasing = 1
    };
    
    class Report
    {
        private:
            long m_levels[DAY_2_MAX_LEVELS];
            int m_num_levels;
        public:
            Report();
            ~Report();
            bool load_report(vector<long> raw_data);
            bool is_safe();
    };
}

using namespace Day2;

class AocDay2 : public AocDay
{
    private:
        bool parse_input (string filename, vector<Report> & reports);
    public:
        AocDay2();
        ~AocDay2();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
