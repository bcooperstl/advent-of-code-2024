#ifndef __AOC_DAY_15__
#define __AOC_DAY_15__

#include "aoc_day.h"

#define FISH_MAP_MAX_LENGTH 50

namespace Day15
{
    class FishMap
    {
        private:
            char m_data[FISH_MAP_MAX_LENGTH][FISH_MAP_MAX_LENGTH+1];
            int m_rows;
            int m_cols;
            int m_robot_row;
            int m_robot_col;
        public:
            FishMap();
            ~FishMap();
            void load_map(vector<string> data, int num_rows);
            void display_map();
    };
}

using namespace Day15;    

class AocDay15 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay15();
        ~AocDay15();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
