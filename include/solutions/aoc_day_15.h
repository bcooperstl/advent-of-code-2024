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
            bool test_and_move(char direction, int row, int col);
        public:
            FishMap();
            ~FishMap();
            void load_map(vector<string> data, int num_rows);
            void display_map();
            void perform_robot_move(char direction);
            int get_gps_score_total();
    };

    class ExpandedFishMap
    {
        private:
            char m_data[FISH_MAP_MAX_LENGTH][(FISH_MAP_MAX_LENGTH*2)+1];
            int m_rows;
            int m_cols;
            int m_robot_row;
            int m_robot_col;
            bool test(char direction, int row, int col);
            void move(char direction, int row, int col);
        public:
            ExpandedFishMap();
            ~ExpandedFishMap();
            void load_map(vector<string> data, int num_rows);
            void display_map();
            void perform_robot_move(char direction);
            int get_gps_score_total();
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
