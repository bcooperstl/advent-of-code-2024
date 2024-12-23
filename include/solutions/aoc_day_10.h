#ifndef __AOC_DAY_10__
#define __AOC_DAY_10__

#include "aoc_day.h"

#define DAY_10_MAX_EDGE 64

namespace Day10
{
    struct ReachableHighPoint
    {
        int row;
        int col;
    };
    
    struct Location
    {
        int height;
        vector<ReachableHighPoint> reachable_high_points;
    };
    
    class Map
    {
        private:
            Location m_map[DAY_10_MAX_EDGE][DAY_10_MAX_EDGE];
            int m_rows;
            int m_cols;
            void add_high_points(Location * destination, Location * source);
        public:
            Map();
            ~Map();
            void load_map(vector<string> data);
            void find_paths_to_high_points(int height);
            int get_total_score();
    };
}

using namespace Day10;

class AocDay10 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay10();
        ~AocDay10();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
