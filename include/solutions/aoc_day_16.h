#ifndef __AOC_DAY_16__
#define __AOC_DAY_16__

#include "aoc_day.h"

#define MAZE_MAX_LENGTH 142

namespace Day16
{
    struct MazeCell
    {
        char symbol;
        int best_score_value;
        bool best_score_direction[4];
        bool processed;
        bool processed_best_seats;
        bool best_seat;
    };
    
    class Maze
    {
        private:
            MazeCell m_maze[MAZE_MAX_LENGTH][MAZE_MAX_LENGTH];
            int m_rows;
            int m_cols;
            int m_end_row;
            int m_end_col;
            int m_start_row;
            int m_start_col;
            bool find_next_cell(int & next_row, int & next_col);
            void process_cell(int row, int col);
        public:
            Maze();
            ~Maze();
            void load_maze(vector<string> data);
            void display_maze();
            bool process_maze();
            int get_end_score();
            //bool process_best_seats();
            int get_best_seats_count();
    };
}

class AocDay16 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay16();
        ~AocDay16();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
