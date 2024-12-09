#ifndef __AOC_DAY_6__
#define __AOC_DAY_6__

#include "aoc_day.h"

#include "screen.h"
#include "overlay.h"

#define DAY_6_NUM_DIRECTIONS 4

namespace Day6
{
    struct Direction
    {
        int move_x;
        int move_y;
        char symbol;
    };
    
    struct Directions
    {
        Direction directions[DAY_6_NUM_DIRECTIONS];
    };
    
    class Map
    {
        private:
            Screen * m_screen;
            Overlay * m_visited;
            Directions m_directions;
            void init_directions();
            bool run_one_step();
            int m_location_x;
            int m_location_y;
            int m_current_direction_index;
            
        public:
            Map(vector<string> data);
            ~Map();
            void run_to_end();
            int get_num_visited();
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
