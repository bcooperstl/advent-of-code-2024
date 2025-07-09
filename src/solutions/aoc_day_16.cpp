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
#define MAZE_BEST 'O'

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
        m_start_row = 0;
        m_end_row = 0;
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                for (int dir=0; dir<NUM_DIRECTIONS; dir++)
                {
                    m_maze[dir][row][col].symbol = data[row][col];
                    m_maze[dir][row][col].processed_best_seats = false;
                    m_maze[dir][row][col].best_seat = false;
                    switch (m_maze[dir][row][col].symbol)
                    {
                        case MAZE_WALL:
                            m_maze[dir][row][col].processed = true;
                            m_maze[dir][row][col].best_score_value = INT_MAX;
                            break;
                        case MAZE_START:
                            m_maze[dir][row][col].processed = false;
                            if (dir == DIRECTION_RIGHT)
                            {
                                m_maze[dir][row][col].best_score_value = 0;
                            }
                            else
                            {
                                m_maze[dir][row][col].best_score_value = INT_MAX;
                            }
                            if (dir == 0)
                            {
                                m_start_row = row;
                                m_start_col = col;
#ifdef DEBUG_DAY_16
                                cout << "Start found at row=" << row << " col=" << col << endl;
#endif                        
                            }
                        break;
                    case MAZE_END:
                        m_maze[dir][row][col].processed = false;
                        m_maze[dir][row][col].best_score_value = INT_MAX;
                        if (dir==0)
                        {
                            m_end_row = row;
                            m_end_col = col;
#ifdef DEBUG_DAY_16
                            cout << "End found at row=" << row << " col=" << col << endl;
#endif                        
                        }
                        break;
                    case MAZE_OPEN:
                        m_maze[dir][row][col].processed = false;
                        m_maze[dir][row][col].best_score_value = INT_MAX;
                        break;
                    }
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
                if ((m_maze[0][row][col].best_seat == true) ||
                    (m_maze[1][row][col].best_seat == true) ||
                    (m_maze[2][row][col].best_seat == true) ||
                    (m_maze[3][row][col].best_seat == true))
                {
                    cout << MAZE_BEST;
                }
                else
                {
                    switch (m_maze[0][row][col].symbol)
                    {
                        case MAZE_WALL:
                        case MAZE_START:
                        case MAZE_END:
                            cout << m_maze[0][row][col].symbol;
                            break;
                        case MAZE_OPEN:
                            ch = MAZE_OPEN;
                            if (m_maze[DIRECTION_UP][row][col].best_score_value != INT_MAX)
                            {
                                ch = MAZE_UP;
                            }
                            if (m_maze[DIRECTION_DOWN][row][col].best_score_value != INT_MAX)
                            {
                                ch = (ch == MAZE_OPEN ? MAZE_DOWN : MAZE_MULTI);
                            }
                            if (m_maze[DIRECTION_LEFT][row][col].best_score_value != INT_MAX)
                            {
                                ch = (ch == MAZE_OPEN ? MAZE_LEFT : MAZE_MULTI);
                            }
                            if (m_maze[DIRECTION_RIGHT][row][col].best_score_value != INT_MAX)
                            {
                                ch = (ch == MAZE_OPEN ? MAZE_RIGHT : MAZE_MULTI);
                            }
                            cout << ch;
                            break;
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
    bool Maze::find_next_cell(int & direction, int & next_row, int & next_col)
    {
        int min_unprocessed_value = INT_MAX;
        for (int dir=0; dir<NUM_DIRECTIONS; dir++)
        {
            if (m_maze[dir][m_end_row][m_end_col].best_score_value < min_unprocessed_value)
            {
                min_unprocessed_value = m_maze[dir][m_end_row][m_end_col].best_score_value;
            }
        }
#ifdef DEBUG_DAY_16
        cout << "Finding next cell. End cell has value " << min_unprocessed_value << endl;
#endif        
        bool cell_found = false;
        for (int dir=0; dir<NUM_DIRECTIONS; dir++)
        {
            for (int row=0; row<m_rows; row++)
            {
                for (int col=0; col<m_cols; col++)
                {
                    if ((m_maze[dir][row][col].processed == false) && (m_maze[dir][row][col].best_score_value < min_unprocessed_value))
                    {
                        cell_found = true;
                        direction = dir;
                        next_row = row;
                        next_col = col;
                        min_unprocessed_value = m_maze[dir][row][col].best_score_value;
#ifdef DEBUG_DAY_16
                        cout << " Better cell found at dir=" << dir << " row=" << row <<  " col=" << col << " with best score " << min_unprocessed_value << endl;
#endif        
                    }
                }
            }
        }
        return cell_found;
    }
    
    void Maze::process_cell(int dir, int row, int col)
    {
        // Test and input mazes have walls around the edges; can eliminate out of bounds checks when processing a cell
#ifdef DEBUG_DAY_16
        cout << "Processing cell dir=" << dir << " row=" << row << " col=" << col 
             << " with value " << m_maze[dir][row][col].best_score_value << endl;
#endif
        int calculated_score;
        int own_direction;
        int ninety_directions[2];
        int opposite_direction;
        int own_row_offset = 0;
        int own_col_offset = 0;
        
        switch (dir)
        {
            case DIRECTION_UP:
                own_direction = DIRECTION_UP;
                ninety_directions[0] = DIRECTION_LEFT;
                ninety_directions[1] = DIRECTION_RIGHT;
                opposite_direction = DIRECTION_DOWN;
                own_row_offset = -1;
                break;
            case DIRECTION_DOWN:
                own_direction = DIRECTION_DOWN;
                ninety_directions[0] = DIRECTION_LEFT;
                ninety_directions[1] = DIRECTION_RIGHT;
                opposite_direction = DIRECTION_UP;
                own_row_offset = 1;
                break;
            case DIRECTION_LEFT:
                own_direction = DIRECTION_LEFT;
                ninety_directions[0] = DIRECTION_UP;
                ninety_directions[1] = DIRECTION_DOWN;
                opposite_direction = DIRECTION_RIGHT;
                own_col_offset = -1;
                break;
            case DIRECTION_RIGHT:
                own_direction = DIRECTION_RIGHT;
                ninety_directions[0] = DIRECTION_UP;
                ninety_directions[1] = DIRECTION_DOWN;
                opposite_direction = DIRECTION_LEFT;
                own_col_offset = 1;
                break;
        }

        // own direction
        if (m_maze[own_direction][row+own_row_offset][col+own_col_offset].processed == false)
        {
#ifdef DEBUG_DAY_16
            cout << " Cell at row=" << row+own_row_offset << " col=" << col+own_col_offset << " is not processed and has best score " << m_maze[dir][row+own_row_offset][col+own_col_offset].best_score_value << endl;
#endif
            calculated_score = m_maze[own_direction][row][col].best_score_value + SCORE_FORWARD;
            if (m_maze[own_direction][row+own_row_offset][col+own_col_offset].best_score_value < calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This is worse than the existing best score. Not using" << endl;
#endif                
            }
            else if (m_maze[own_direction][row+own_row_offset][col+own_col_offset].best_score_value == calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This matches the existing best score. No change" << endl;
#endif
            }
            else
            {
                m_maze[own_direction][row+own_row_offset][col+own_col_offset].best_score_value = calculated_score;
#ifdef DEBUG_DAY_16
                cout << "This beats the existing best score. Setting new best score." << endl;
#endif                
            }
        }
                
        // turn ninety degrees
        calculated_score = m_maze[dir][row][col].best_score_value + SCORE_TURN;
        for (int i=0; i<2; i++)
        {
            if (m_maze[ninety_directions[i]][row][col].processed == false)
            {
#ifdef DEBUG_DAY_16
                cout << " Turning ninety degrees to " << ninety_directions[i] << " at row=" << row << " col=" << col << " is not processed and has best score " << m_maze[ninety_directions[i]][row][col].best_score_value << endl;
#endif                
                if (m_maze[ninety_directions[i]][row][col].best_score_value < calculated_score)
                {
#ifdef DEBUG_DAY_16
                    cout << "This is worse than the existing best score. Not using" << endl;
#endif                
                }
                else if (m_maze[ninety_directions[i]][row][col].best_score_value == calculated_score)
                {
#ifdef DEBUG_DAY_16
                    cout << "This matches the existing best score. No change" << endl;
#endif
                }
                else
                {
                    m_maze[ninety_directions[i]][row][col].best_score_value = calculated_score;
#ifdef DEBUG_DAY_16
                    cout << "This beats the existing best score. Setting new best score." << endl;
#endif                
                }
            }
        }

        // turn opposite direction
        calculated_score = m_maze[dir][row][col].best_score_value + SCORE_TURN + SCORE_TURN;
        if (m_maze[opposite_direction][row][col].processed == false)
        {
#ifdef DEBUG_DAY_16
            cout << " Turning opposite to " << opposite_direction << " at row=" << row << " col=" << col << " is not processed and has best score " << m_maze[DIRECTION_LEFT][row][col].best_score_value << endl;
#endif                
            if (m_maze[opposite_direction][row][col].best_score_value < calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This is worse than the existing best score. Not using" << endl;
#endif                
            }
            else if (m_maze[opposite_direction][row][col].best_score_value == calculated_score)
            {
#ifdef DEBUG_DAY_16
                cout << "This matches the existing best score. No change" << endl;
#endif
            }
            else
            {
                m_maze[opposite_direction][row][col].best_score_value = calculated_score;
#ifdef DEBUG_DAY_16
                cout << "This beats the existing best score. Setting new best score." << endl;
#endif                
            }
        }
                
        m_maze[dir][row][col].processed = true;
        return;
    }
    
    bool Maze::process_maze()
    {
        int dir, row, col;
        while (find_next_cell(dir, row, col) == true)
        {
            process_cell(dir, row, col);
        }
        return (m_maze[0][m_end_row][m_end_col].processed || 
                m_maze[1][m_end_row][m_end_col].processed || 
                m_maze[2][m_end_row][m_end_col].processed || 
                m_maze[3][m_end_row][m_end_col].processed);
    }
    
    int Maze::get_end_score()
    {
        int best = INT_MAX;
        for (int dir=0; dir<NUM_DIRECTIONS; dir++)
        {
            if (m_maze[dir][m_end_row][m_end_col].best_score_value < best)
            {
                best = m_maze[dir][m_end_row][m_end_col].best_score_value;
            }
        }
        return best;
    }
    
    int Maze::get_best_seats_count()
    {
        int count=0;
        
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                if ((m_maze[0][row][col].best_seat == true) || 
                    (m_maze[1][row][col].best_seat == true) || 
                    (m_maze[2][row][col].best_seat == true) || 
                    (m_maze[3][row][col].best_seat == true))
                {
                    count++;
                }
            }
        }
        
        return count;
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

    Maze maze;
    
    maze.load_maze(data);
    maze.display_maze();
    maze.process_maze();
    maze.display_maze();
    ostringstream out;
    out << maze.get_best_seats_count();
    return out.str();
}
