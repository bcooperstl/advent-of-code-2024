#ifndef __AOC_DAY_12__
#define __AOC_DAY_12__

#include "aoc_day.h"

#define DAY_12_MAX_LENGTH 140

#define DAY_12_NORTH 0
#define DAY_12_SOUTH 1
#define DAY_12_WEST 2
#define DAY_12_EAST 3

#define DAY_12_YES 1
#define DAY_12_NO 0

namespace Day12
{
    struct Plot
    {
        char plant;
        int region;
        char is_perimeter[4];
        char is_side[4];
    };
    
    class Farm
    {
        private:
            Plot m_plots[DAY_12_MAX_LENGTH][DAY_12_MAX_LENGTH];
            int m_rows;
            int m_cols;
            int m_num_assigned_regions;
            vector<pair<int, int>> m_first_plots;
            void load_data(vector<string> data);
            void map_region(int start_row, int start_col, int region_number);
        public:
            Farm(vector<string> data);
            ~Farm();
            void display();
            void map_regions();
            void calculate_perimeters();
            void calculate_sides();
            int get_total_price();
            int get_total_discount_price();
    };
}

using namespace Day12;

class AocDay12 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay12();
        ~AocDay12();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
