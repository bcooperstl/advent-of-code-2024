#ifndef __AOC_DAY_8__
#define __AOC_DAY_8__

#include <vector>
#include <map>

#include "aoc_day.h"

namespace Day8
{
    struct Location
    {
        int row;
        int col;
        bool operator == (const Location & other);
    };
    
    class Frequency
    {
        private:
            vector<Location> m_nodes;
            char m_symbol;
        public:
            Frequency();
            Frequency(char symbol);
            ~Frequency();
            void add_node(Location location);
            vector<Location> get_antinodes();
            vector<Location> get_harmonic_antinodes(int min_row, int max_row, int min_col, int max_col);
    };
    
    class City
    {
        private:
            map<char, Frequency> m_frequencies;
            int m_min_row;
            int m_max_row;
            int m_min_col;
            int m_max_col;
        public:
            City();
            ~City();
            void add_node(char symbol, Location location);
            vector<Location> get_all_antinodes_in_city();
            vector<Location> get_all_harmonic_antinodes_in_city();
            void map_city(vector<string> data);
    };
}

using namespace Day8;

class AocDay8 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay8();
        ~AocDay8();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
