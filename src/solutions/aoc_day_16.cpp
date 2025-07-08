#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>

#include "aoc_day_16.h"
#include "file_utils.h"

using namespace std;
using namespace Day16;

#define MAZE_WALL '#'
#define MAZE_START 'S'
#define MAZE_END 'E'
#define MAZE_OPEN '.'

#define MAZE_UP '^'
#define MAZE_DOWN 'v'
#define MAZE_RIGHT '>'
#define MAZE_LEFT '<'
#define MAZE_MULTI '?'

#define DIRECTION_UP 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3

namespace Day16
{
    Maze::Maze()
    {
        m_rows = 0;
        m_cols = 0;
    }
    
    Maze::~Maze()
    {
    }
    
    void Maze::load_maze(vector<string> data)
    {
        m_rows = data.size();
        m_cols = data[0].length();
        m_end_row = 0;
        m_end_col = 0;
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                m_maze[row][col].symbol = data[row][col];
                switch (m_maze[row][col].symbol)
                {
                    case MAZE_WALL:
                        m_maze[row][col].processed = true;
                        m_maze[row][col].best_score_value = INT_MAX;
                        break;
                    case MAZE_START:
                        m_maze[row][col].processed = true;
                        m_maze[row][col].best_score_value = 0;
                        m_maze[row][col].best_score_direction[DIRECTION_UP] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_DOWN] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_LEFT] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_RIGHT] = true;
#ifdef DEBUG_DAY_16
                        cout << "Start found at row=" << row << " col=" << col << endl;
#endif                        
                        break;
                    case MAZE_END:
                        m_maze[row][col].processed = false;
                        m_maze[row][col].best_score_value = INT_MAX;
                        m_maze[row][col].best_score_direction[DIRECTION_UP] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_DOWN] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_LEFT] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_RIGHT] = false;
                        m_end_row = row;
                        m_end_col = col;
#ifdef DEBUG_DAY_16
                        cout << "End found at row=" << row << " col=" << col << endl;
#endif                        
                        break;
                    case MAZE_OPEN:
                        m_maze[row][col].processed = false;
                        m_maze[row][col].best_score_value = INT_MAX;
                        m_maze[row][col].best_score_direction[DIRECTION_UP] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_DOWN] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_LEFT] = false;
                        m_maze[row][col].best_score_direction[DIRECTION_RIGHT] = false;
                        break;
                }
            }
        }
        return;
    }
    
    void Maze::display_maze()
    {
        char ch;
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                switch (m_maze[row][col].symbol)
                {
                    case MAZE_WALL:
                    case MAZE_START:
                    case MAZE_END:
                        cout << m_maze[row][col].symbol;
                        break;
                    case MAZE_OPEN:
                        ch = MAZE_OPEN;
                        if (m_maze[row][col].best_score_direction[DIRECTION_UP] == true)
                        {
                            ch = MAZE_UP;
                        }
                        if (m_maze[row][col].best_score_direction[DIRECTION_DOWN] == true)
                        {
                            ch = (ch == MAZE_OPEN ? MAZE_DOWN : MAZE_MULTI);
                        }
                        if (m_maze[row][col].best_score_direction[DIRECTION_LEFT] == true)
                        {
                            ch = (ch == MAZE_OPEN ? MAZE_LEFT : MAZE_MULTI);
                        }
                        if (m_maze[row][col].best_score_direction[DIRECTION_RIGHT] == true)
                        {
                            ch = (ch == MAZE_OPEN ? MAZE_RIGHT : MAZE_MULTI);
                        }
                        cout << ch;
                        break;
                }
            }
            cout << endl;
        }
        cout << endl;
    }
        
}

AocDay16::AocDay16():AocDay(16)
{
}

AocDay16::~AocDay16()
{
}

vector<string> AocDay16::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> data;
    if (!fileutils.read_as_list_of_strings(filename, data))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    return data;
}

string AocDay16::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    out << "Day 16 - Part 1 not implemented";
    return out.str();
}

string AocDay16::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 16 - Part 2 not implemented";
    return out.str();
}
