#ifndef __AOC_DAY_6__
#define __AOC_DAY_6__

#include "aoc_day.h"

#define DAY_6_NUM_DIRECTIONS 4
#define DAY_6_MAX_LENGTH 140

namespace Day6
{
    struct Cell
    {
        char symbol;
        char visited_part1;
        char visited_part2;
    };
    
    struct Direction
    {
        int move_x;
        int move_y;
        char symbol;
        char visited_mask;
    };
    
    struct Directions
    {
        Direction directions[DAY_6_NUM_DIRECTIONS];
    };
        
    class Map
    {
        private:
            Cell m_map[DAY_6_MAX_LENGTH][DAY_6_MAX_LENGTH];
            Directions m_directions;
            void init_directions();
            bool run_one_step();
            int m_rows;
            int m_cols;
            int m_location_x;
            int m_location_y;
            int m_start_x;
            int m_start_y;
            int m_current_direction_index;
            //bool does_new_obstruction_loop(int col, int row);
            void display();
            void load_data(vector<string> data);
            void reset();
        public:
            Map(vector<string> data);
            ~Map();
            void run_to_end();
            int get_num_visited();
            //int get_num_obstruction_loop_positions();
    };
}

using namespace Day6;

class AocDay6 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay6();
        ~AocDay6();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
