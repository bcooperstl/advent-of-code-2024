#ifndef __AOC_DAY_14__
#define __AOC_DAY_14__

#include "aoc_day.h"

namespace Day14
{
    struct Robot
    {
        int pos_x;
        int pos_y;
        int vel_x;
        int vel_y;
    };
    
    class World
    {
        private:
            int m_width;
            int m_height;
            vector<Robot> m_robots;
        public:
            World(int width, int height);
            ~World();
            void load_robots(vector<vector<string>> data);
            void move_robots(int num_moves);
            int get_safety_factor();
            void display();
    };      
}

using namespace Day14;

class AocDay14 : public AocDay
{
    
    private:
        vector<vector<string>> read_input(string filename);
    public:
        AocDay14();
        ~AocDay14();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
