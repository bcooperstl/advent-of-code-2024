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

#define SCORE_FORWARD 1
#define SCORE_TURN 1000

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
                        m_maze[row][col].processed = false;
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
    
    bool Maze::find_next_cell(int & next_row, int & next_col)
    {
        int min_unprocessed_value = m_maze[m_end_row][m_end_col].best_score_value;
#ifdef DEBUG_DAY_16
        cout << "Finding next cell. End cell has value " << min_unprocessed_value << endl;
#endif        
        bool cell_found = false;
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                if ((m_maze[row][col].processed == false) && (m_maze[row][col].best_score_value < min_unprocessed_value))
                {
                    cell_found = true;
                    next_row = row;
                    next_col = col;
                    min_unprocessed_value = m_maze[row][col].best_score_value;
#ifdef DEBUG_DAY_16
                    cout << " Better cell found at row=" << row <<  " col=" << col << " with best score " << min_unprocessed_value << endl;
#endif        
                }
            }
        }
        return cell_found;
    }
    
    void Maze::process_cell(int row, int col)
    {
        // Test and input mazes have walls around the edges; can eliminate out of bounds checks when processing a cell
#ifdef DEBUG_DAY_16
        cout << "Processing cell row=" << row << " col=" << col 
             << " with value " << m_maze[row][col].best_score_value << " facing: "
             << (m_maze[row][col].best_score_direction[DIRECTION_UP] ? "up " : "")
             << (m_maze[row][col].best_score_direction[DIRECTION_DOWN] ? "down " : "")
             << (m_maze[row][col].best_score_direction[DIRECTION_LEFT] ? "left " : "")
             << (m_maze[row][col].best_score_direction[DIRECTION_RIGHT] ? "right " : "")
             << endl;
#endif
        int calculated_score;
        
        // check up
        if (m_maze[row-1][col].processed == false)
        {
#ifdef DEBUG_DAY_16
            cout << " Cell above at row=" << row-1 << " col=" << col << " is not processed and has best score " << m_maze[row][col-1].best_score_value << endl;
#endif
            if (m_maze[row][col].best_score_direction[DIRECTION_UP] == true)
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_FORWARD;
            }
            else if ((m_maze[row][col].best_score_direction[DIRECTION_LEFT] == true) ||
                     (m_maze[row][col].best_score_direction[DIRECTION_RIGHT] == true))
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_TURN + SCORE_FORWARD;
            }
            else
            {
                cerr << "U-TURN DETECTED...Figure out your bug!!" << endl;
                calculated_score = INT_MAX;
            }
            
#ifdef DEBUG_DAY_16
            cout << "  Calculated score is " << calculated_score << ". ";
#endif
            if (m_maze[row-1][col].best_score_value < calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This is worse than the existing best score. Not using" << endl;
#endif                
            }
            else if (m_maze[row-1][col].best_score_value == calculated_score)
            {
                m_maze[row-1][col].best_score_direction[DIRECTION_UP] = true;
#ifdef DEBUG_DAY_16
                cout << "This matches the existing best score. Adding up as a direction" << endl;
#endif
            }
            else
            {
                m_maze[row-1][col].best_score_direction[DIRECTION_UP] = true;
                m_maze[row-1][col].best_score_direction[DIRECTION_DOWN] = false;
                m_maze[row-1][col].best_score_direction[DIRECTION_LEFT] = false;
                m_maze[row-1][col].best_score_direction[DIRECTION_RIGHT] = false;
                m_maze[row-1][col].best_score_value = calculated_score;
#ifdef DEBUG_DAY_16
                cout << "This beats the existing best score. Setting new best score and only direction as up" << endl;
#endif                
            }
        }

        // check down
        if (m_maze[row+1][col].processed == false)
        {
#ifdef DEBUG_DAY_16
            cout << " Cell below at row=" << row+1 << " col=" << col << " is not processed and has best score " << m_maze[row][col-1].best_score_value << endl;
#endif
            if (m_maze[row][col].best_score_direction[DIRECTION_DOWN] == true)
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_FORWARD;
            }
            else if ((m_maze[row][col].best_score_direction[DIRECTION_LEFT] == true) ||
                     (m_maze[row][col].best_score_direction[DIRECTION_RIGHT] == true))
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_TURN + SCORE_FORWARD;
            }
            else
            {
                cerr << "U-TURN DETECTED...Figure out your bug!!" << endl;
                calculated_score = INT_MAX;
            }
            
#ifdef DEBUG_DAY_16
            cout << "  Calculated score is " << calculated_score << ". ";
#endif
            if (m_maze[row+1][col].best_score_value < calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This is worse than the existing best score. Not using" << endl;
#endif                
            }
            else if (m_maze[row+1][col].best_score_value == calculated_score)
            {
                m_maze[row+1][col].best_score_direction[DIRECTION_DOWN] = true;
#ifdef DEBUG_DAY_16
                cout << "This matches the existing best score. Adding down as a direction" << endl;
#endif
            }
            else
            {
                m_maze[row+1][col].best_score_direction[DIRECTION_UP] = false;
                m_maze[row+1][col].best_score_direction[DIRECTION_DOWN] = true;
                m_maze[row+1][col].best_score_direction[DIRECTION_LEFT] = false;
                m_maze[row+1][col].best_score_direction[DIRECTION_RIGHT] = false;
                m_maze[row+1][col].best_score_value = calculated_score;
#ifdef DEBUG_DAY_16
                cout << "This beats the existing best score. Setting new best score and only direction as down" << endl;
#endif                
            }
        }

        // check left
        if (m_maze[row][col-1].processed == false)
        {
#ifdef DEBUG_DAY_16
            cout << " Cell left at row=" << row << " col=" << col-1 << " is not processed and has best score " << m_maze[row][col-1].best_score_value << endl;
#endif
            if (m_maze[row][col].best_score_direction[DIRECTION_LEFT] == true)
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_FORWARD;
            }
            else if ((m_maze[row][col].best_score_direction[DIRECTION_UP] == true) ||
                     (m_maze[row][col].best_score_direction[DIRECTION_DOWN] == true))
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_TURN + SCORE_FORWARD;
            }
            else
            {
                cerr << "U-TURN DETECTED...Figure out your bug!!" << endl;
                calculated_score = INT_MAX;
            }
            
#ifdef DEBUG_DAY_16
            cout << "  Calculated score is " << calculated_score << ". ";
#endif
            if (m_maze[row][col-1].best_score_value < calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This is worse than the existing best score. Not using" << endl;
#endif                
            }
            else if (m_maze[row][col-1].best_score_value == calculated_score)
            {
                m_maze[row][col-1].best_score_direction[DIRECTION_LEFT] = true;
#ifdef DEBUG_DAY_16
                cout << "This matches the existing best score. Adding left as a direction" << endl;
#endif
            }
            else
            {
                m_maze[row][col-1].best_score_direction[DIRECTION_UP] = false;
                m_maze[row][col-1].best_score_direction[DIRECTION_DOWN] = false;
                m_maze[row][col-1].best_score_direction[DIRECTION_LEFT] = true;
                m_maze[row][col-1].best_score_direction[DIRECTION_RIGHT] = false;
                m_maze[row][col-1].best_score_value = calculated_score;
#ifdef DEBUG_DAY_16
                cout << "This beats the existing best score. Setting new best score and only direction as left" << endl;
#endif                
            }
        }

        // check right
        if (m_maze[row][col+1].processed == false)
        {
#ifdef DEBUG_DAY_16
            cout << " Cell right at row=" << row << " col=" << col+1 << " is not processed and has best score " << m_maze[row][col-1].best_score_value << endl;
#endif
            if (m_maze[row][col].best_score_direction[DIRECTION_RIGHT] == true)
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_FORWARD;
            }
            else if ((m_maze[row][col].best_score_direction[DIRECTION_UP] == true) ||
                     (m_maze[row][col].best_score_direction[DIRECTION_DOWN] == true))
            {
                calculated_score = m_maze[row][col].best_score_value + SCORE_TURN + SCORE_FORWARD;
            }
            else
            {
                cerr << "U-TURN DETECTED...Figure out your bug!!" << endl;
                calculated_score = INT_MAX;
            }
            
#ifdef DEBUG_DAY_16
            cout << "  Calculated score is " << calculated_score << ". ";
#endif
            if (m_maze[row][col+1].best_score_value < calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This is worse than the existing best score. Not using" << endl;
#endif                
            }
            else if (m_maze[row][col+1].best_score_value == calculated_score)
            {
                m_maze[row][col+1].best_score_direction[DIRECTION_RIGHT] = true;
#ifdef DEBUG_DAY_16
                cout << "This matches the existing best score. Adding right as a direction" << endl;
#endif
            }
            else
            {
                m_maze[row][col+1].best_score_direction[DIRECTION_UP] = false;
                m_maze[row][col+1].best_score_direction[DIRECTION_DOWN] = false;
                m_maze[row][col+1].best_score_direction[DIRECTION_LEFT] = false;
                m_maze[row][col+1].best_score_direction[DIRECTION_RIGHT] = true;
                m_maze[row][col+1].best_score_value = calculated_score;
#ifdef DEBUG_DAY_16
                cout << "This beats the existing best score. Setting new best score and only direction as right" << endl;
#endif                
            }
        }
        m_maze[row][col].processed = true;
        return;
    }
    
    bool Maze::process_maze()
    {
        int row, col;
        while (find_next_cell(row, col) == true)
        {
            process_cell(row, col);
        }
        return m_maze[m_end_row][m_end_col].processed;
    }
    
    int Maze::get_end_score()
    {
        return m_maze[m_end_row][m_end_col].best_score_value;
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
    
    Maze maze;
    
    maze.load_maze(data);
    maze.display_maze();
    maze.process_maze();
    maze.display_maze();
    ostringstream out;
    out << maze.get_end_score();
    return out.str();
}

string AocDay16::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 16 - Part 2 not implemented";
    return out.str();
}
