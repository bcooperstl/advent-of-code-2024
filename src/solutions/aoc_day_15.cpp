#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "aoc_day_15.h"
#include "file_utils.h"

using namespace std;
using namespace Day15;

#define MAP_ROBOT '@'
#define MAP_WALL '#'
#define MAP_BOX 'O'
#define MAP_OPEN '.'
#define MAP_BOX_LEFT '['
#define MAP_BOX_RIGHT ']'

#define DIRECTION_UP '^'
#define DIRECTION_DOWN 'v'
#define DIRECTION_RIGHT '>'
#define DIRECTION_LEFT '<'

namespace Day15
{
    FishMap::FishMap()
    {
        m_rows = 0;
        m_cols = 0;
        m_robot_row = 0;
        m_robot_col = 0;
        for (int i=0; i<FISH_MAP_MAX_LENGTH; i++)
        {
            m_data[i][0] = '\0';
        }
    }
    
    FishMap::~FishMap()
    {
    }
    
    void FishMap::display_map()
    {
        for (int i=0; i<m_rows; i++)
        {
            cout << m_data[i] << endl;
        }
        cout << endl;
    }
    
    void FishMap::load_map(vector<string> data, int num_rows)
    {
        m_rows = num_rows;
        m_cols = data[0].length();
        for (int i=0; i<num_rows; i++)
        {
            strncpy(m_data[i], data[i].c_str(), FISH_MAP_MAX_LENGTH+1);
            for (int j=0; j<m_cols; j++)
            {
                if (m_data[i][j]==MAP_ROBOT)
                {
                    m_robot_row = i;
                    m_robot_col = j;
#ifdef DEBUG_DAY_15
                    cout << "Robot is at row=" << i << " col=" << j << endl;
#endif
                }
            }
        }
    }
    
    bool FishMap::test_and_move(char direction, int row, int col)
    {
        int next_row;
        int next_col;
        switch (direction)
        {
            case DIRECTION_UP:
                next_row = row-1;
                next_col = col;
                break;
            case DIRECTION_DOWN:
                next_row = row+1;
                next_col = col;
                break;
            case DIRECTION_LEFT:
                next_row = row;
                next_col = col-1;
                break;
            case DIRECTION_RIGHT:
                next_row = row;
                next_col = col+1;
                break;
            default:
                cerr << "Invalid direction " << direction << " is not a valid direction" << endl;
                return false;
        }

        if (m_data[next_row][next_col] == MAP_OPEN)
        {
#ifdef DEBUG_DAY_15_EVERY_STEP
            cout << "Can move " << m_data[row][col] 
                 << " at row=" << row << " col=" << col
                 << " to " << m_data[next_row][next_col] 
                 << " at row=" << next_row << " col=" << next_col << endl;
#endif
            m_data[next_row][next_col] = m_data[row][col];
            m_data[row][col] = MAP_OPEN;
            return true;
        }
        else if (m_data[next_row][next_col] == MAP_WALL)
        {
#ifdef DEBUG_DAY_15_EVERY_STEP
            cout << "Cannot move " << m_data[row][col] 
                 << " at row=" << row << " col=" << col
                 << " to " << m_data[next_row][next_col] 
                 << " at row=" << next_row << " col=" << next_col << endl;
#endif
            return false;
        }
        
#ifdef DEBUG_DAY_15_EVERY_STEP
        cout << "Testing move " << m_data[row][col] 
             << " at row=" << row << " col=" << col
             << " to " << m_data[next_row][next_col] 
             << " at row=" << next_row << " col=" << next_col << endl;
#endif

        bool can_move = test_and_move(direction, next_row, next_col);

        if (can_move)
        {
#ifdef DEBUG_DAY_15_EVERY_STEP
            cout << "Moving " << m_data[row][col] 
                 << " at row=" << row << " col=" << col
                 << " to " << m_data[next_row][next_col] 
                 << " at row=" << next_row << " col=" << next_col << endl;
#endif
            m_data[next_row][next_col] = m_data[row][col];
            m_data[row][col] = MAP_OPEN;
        }
        else
        {
#ifdef DEBUG_DAY_15_EVERY_STEP
            cout << "Not moving " << m_data[row][col] 
                 << " at row=" << row << " col=" << col
                 << " to " << m_data[next_row][next_col] 
                 << " at row=" << next_row << " col=" << next_col << endl;
#endif
        }
        return can_move;
    }
    
    void FishMap::perform_robot_move(char direction)
    {
#ifdef DEBUG_DAY_15_EVERY_STEP
        cout << "Moving " << direction << endl;
#endif
        int result = test_and_move(direction, m_robot_row, m_robot_col);
        if (result == true)
        {
            switch (direction)
            {
                case DIRECTION_UP:
                    m_robot_row--;
                    break;
                case DIRECTION_DOWN:
                    m_robot_row++;
                    break;
                case DIRECTION_LEFT:
                    m_robot_col--;
                    break;
                case DIRECTION_RIGHT:
                    m_robot_col++;
                    break;
            }
        }   
#ifdef DEBUG_DAY_15_EVERY_STEP
        display_map();
#endif
    }
    
    int FishMap::get_gps_score_total()
    {
        int total = 0;
        for (int i=0; i<m_rows; i++)
        {
            for (int j=0; j<m_cols; j++)
            {
                if (m_data[i][j] == MAP_BOX)
                {
                    total += ((100 * i) + j);
                }
            }
        }
        return total;
    }
    
    ExpandedFishMap::ExpandedFishMap()
    {
        m_rows = 0;
        m_cols = 0;
        m_robot_row = 0;
        m_robot_col = 0;
        for (int i=0; i<FISH_MAP_MAX_LENGTH; i++)
        {
            m_data[i][0] = '\0';
        }
    }
    
    ExpandedFishMap::~ExpandedFishMap()
    {
    }
    
    void ExpandedFishMap::display_map()
    {
        for (int i=0; i<m_rows; i++)
        {
            cout << m_data[i] << endl;
        }
        cout << endl;
    }
    
    void ExpandedFishMap::load_map(vector<string> data, int num_rows)
    {
        m_rows = num_rows;
        int cols = data[0].length();
        m_cols = data[0].length()*2;
        for (int i=0; i<num_rows; i++)
        {
            for (int j=0; j<cols; j++)
            {
                switch (data[i][j])
                {
                    case MAP_WALL:
                        m_data[i][j*2]=MAP_WALL;
                        m_data[i][j*2+1]=MAP_WALL;
                        break;
                    case MAP_OPEN:
                        m_data[i][j*2]=MAP_OPEN;
                        m_data[i][j*2+1]=MAP_OPEN;
                        break;
                    case MAP_BOX:
                        m_data[i][j*2]=MAP_BOX_LEFT;
                        m_data[i][j*2+1]=MAP_BOX_RIGHT;
                        break;
                    case MAP_ROBOT:
                        m_data[i][j*2]=MAP_ROBOT;
                        m_data[i][j*2+1]=MAP_OPEN;
                        m_robot_row = i;
                        m_robot_col = j*2;
#ifdef DEBUG_DAY_15
                        cout << "Robot is at row=" << i << " col=" << j << endl;
#endif
                        break;
                }
            }
        }
    }
    
    bool ExpandedFishMap::test(char direction, int row, int col)
    {
        bool can_move = false;
        int next_row = row;
        int next_col = col;
        switch (direction)
        {
            case DIRECTION_LEFT:
                next_col = col-1;
                if (m_data[next_row][next_col] == MAP_OPEN)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Can move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = true;
                }
                else if (m_data[next_row][next_col] == MAP_WALL)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Cannot move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = false;
                }
                else if (m_data[next_row][next_col] == MAP_BOX_RIGHT)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Testing move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    next_col--;
                    can_move = test(direction, next_row, next_col);
                }
                else
                {
                    cerr << "Invalid item " << m_data[next_row][next_col] << endl;
                    can_move = false;
                }
                break;
            case DIRECTION_RIGHT:
                next_col = col+1;
                if (m_data[next_row][next_col] == MAP_OPEN)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Can move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = true;
                }
                else if (m_data[next_row][next_col] == MAP_WALL)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Cannot move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = false;
                }
                else if (m_data[next_row][next_col] == MAP_BOX_LEFT)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Testing move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    next_col++;
                    can_move = test(direction, next_row, next_col);
                }
                else
                {
                    cerr << "Invalid item " << m_data[next_row][next_col] << endl;
                    can_move = false;
                }
                break;
            case DIRECTION_UP:
                next_row = row-1;
                if (m_data[next_row][next_col] == MAP_OPEN)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Can move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = true;
                }
                else if (m_data[next_row][next_col] == MAP_WALL)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Cannot move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = false;
                }
                else if (m_data[next_row][next_col] == MAP_BOX_LEFT)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Testing move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = (test(direction, next_row, next_col) && test(direction, next_row, next_col+1));
                }
                else if (m_data[next_row][next_col] == MAP_BOX_RIGHT)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Testing move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = (test(direction, next_row, next_col-1) && test(direction, next_row, next_col));
                }                   
                else
                {
                    cerr << "Invalid item " << m_data[next_row][next_col] << endl;
                    can_move = false;
                }
                break;
            case DIRECTION_DOWN:
                next_row = row+1;
                if (m_data[next_row][next_col] == MAP_OPEN)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Can move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = true;
                }
                else if (m_data[next_row][next_col] == MAP_WALL)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Cannot move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = false;
                }
                else if (m_data[next_row][next_col] == MAP_BOX_LEFT)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Testing move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = (test(direction, next_row, next_col) && test(direction, next_row, next_col+1));
                }
                else if (m_data[next_row][next_col] == MAP_BOX_RIGHT)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Testing move " << m_data[row][col] << " at row=" << row << " col=" << col << " to " << m_data[next_row][next_col] << " at row=" << next_row << " col=" << next_col << endl;
#endif
                    can_move = (test(direction, next_row, next_col-1) && test(direction, next_row, next_col));
                }                   
                else
                {
                    cerr << "Invalid item " << m_data[next_row][next_col] << endl;
                    can_move = false;
                }
                break;
        }
            
        return can_move;
    }
        
    
    void ExpandedFishMap::move(char direction, int row, int col)
    {
        int first_open, current_row;
        bool work_added;
        bool items_to_move[50][100];
        for (int i=0; i<50; i++)
        {
            for (int j=0; j<100; j++)
            {
                items_to_move[i][j] = false;
            }
        }
        
        switch (direction)
        {
            case DIRECTION_LEFT:
                first_open = col - 1;
                while (m_data[row][first_open] != MAP_OPEN)
                {
                    first_open--;
                }
                
                for (int curr=first_open+1; curr<=col; curr++)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Moving " << m_data[row][curr] << " at row=" << row << " col=" << curr << " to " << m_data[row][curr-1] << " at row=" << row << " col=" << curr-1 << endl;
#endif
                    m_data[row][curr-1] = m_data[row][curr];
                }
                m_data[row][col] = MAP_OPEN;
                break;
            case DIRECTION_RIGHT:
                first_open = col + 1;
                while (m_data[row][first_open] != MAP_OPEN)
                {
                    first_open++;
                }
                
                for (int curr=first_open-1; curr>=col; curr--)
                {
#ifdef DEBUG_DAY_15_EVERY_STEP
                    cout << "Moving " << m_data[row][curr] << " at row=" << row << " col=" << curr << " to " << m_data[row][curr+1] << " at row=" << row << " col=" << curr+1 << endl;
#endif
                    m_data[row][curr+1] = m_data[row][curr];
                }
                m_data[row][col] = MAP_OPEN;
                break;
            case DIRECTION_UP:
                items_to_move[row][col] = true;
#ifdef DEBUG_DAY_15_EVERY_STEP
                cout << "Item to move " << m_data[row][col] << " at row=" << row << " col=" << col << endl;
#endif
                
                current_row = row;
                work_added = true;
                while (work_added == true)
                {
                    work_added = false;
                    for (int i=0; i<100; i++)
                    {
                        if (items_to_move[current_row][i] == true)
                        {
                            if (m_data[current_row-1][i] == MAP_BOX_LEFT)
                            {
                                work_added = true;
                                items_to_move[current_row-1][i] = true;
                                items_to_move[current_row-1][i+1] = true;
#ifdef DEBUG_DAY_15_EVERY_STEP
                                cout << "Item to move " << m_data[current_row-1][i] << " at row=" << current_row-1 << " col=" << i << endl;
                                cout << "Item to move " << m_data[current_row-1][i+1] << " at row=" << current_row-1 << " col=" << i+1 << endl;
#endif
                            } 
                            if (m_data[current_row-1][i] == MAP_BOX_RIGHT)
                            {
                                work_added = true;
                                items_to_move[current_row-1][i-1] = true;
                                items_to_move[current_row-1][i] = true;
#ifdef DEBUG_DAY_15_EVERY_STEP
                                cout << "Item to move " << m_data[current_row-1][i-1] << " at row=" << current_row-1 << " col=" << i-1 << endl;
                                cout << "Item to move " << m_data[current_row-1][i] << " at row=" << current_row-1 << " col=" << i << endl;
#endif
                            } 
                        }
                    }
                    current_row--;
                }
                current_row++;
                while (current_row <= row)
                {
                    for (int i=0; i<100; i++)
                    {
                        if (items_to_move[current_row][i] == true)
                        {
#ifdef DEBUG_DAY_15_EVERY_STEP
                            cout << "Moving " << m_data[current_row][i] << " at row=" << current_row << " col=" << i << " to " << m_data[current_row-1][i] << " at row=" << current_row-1 << " col=" << i << endl;
#endif
                            m_data[current_row-1][i] = m_data[current_row][i];
                            m_data[current_row][i] = MAP_OPEN;
                        }
                    }
                    current_row++;
                }
                break;
            case DIRECTION_DOWN:
                items_to_move[row][col] = true;
#ifdef DEBUG_DAY_15_EVERY_STEP
                cout << "Item to move " << m_data[row][col] << " at row=" << row << " col=" << col << endl;
#endif
                
                current_row = row;
                work_added = true;
                while (work_added == true)
                {
                    work_added = false;
                    for (int i=0; i<100; i++)
                    {
                        if (items_to_move[current_row][i] == true)
                        {
                            if (m_data[current_row+1][i] == MAP_BOX_LEFT)
                            {
                                work_added = true;
                                items_to_move[current_row+1][i] = true;
                                items_to_move[current_row+1][i+1] = true;
#ifdef DEBUG_DAY_15_EVERY_STEP
                                cout << "Item to move " << m_data[current_row+1][i] << " at row=" << current_row+1 << " col=" << i << endl;
                                cout << "Item to move " << m_data[current_row+1][i+1] << " at row=" << current_row+1 << " col=" << i+1 << endl;
#endif
                            } 
                            if (m_data[current_row+1][i] == MAP_BOX_RIGHT)
                            {
                                work_added = true;
                                items_to_move[current_row+1][i-1] = true;
                                items_to_move[current_row+1][i] = true;
#ifdef DEBUG_DAY_15_EVERY_STEP
                                cout << "Item to move " << m_data[current_row+1][i-1] << " at row=" << current_row+1 << " col=" << i-1 << endl;
                                cout << "Item to move " << m_data[current_row+1][i] << " at row=" << current_row+1 << " col=" << i << endl;
#endif
                            } 
                        }
                    }
                    current_row++;
                }
                current_row--;
                while (current_row >= row)
                {
                    for (int i=0; i<100; i++)
                    {
                        if (items_to_move[current_row][i] == true)
                        {
#ifdef DEBUG_DAY_15_EVERY_STEP
                            cout << "Moving " << m_data[current_row][i] << " at row=" << current_row << " col=" << i << " to " << m_data[current_row+1][i] << " at row=" << current_row+1 << " col=" << i << endl;
#endif
                            m_data[current_row+1][i] = m_data[current_row][i];
                            m_data[current_row][i] = MAP_OPEN;
                        }
                    }
                    current_row--;
                }
                break;
        }
        return;
    }
    
    void ExpandedFishMap::perform_robot_move(char direction)
    {
#ifdef DEBUG_DAY_15_EVERY_STEP
        cout << "Moving " << direction << endl;
#endif
        if (test(direction, m_robot_row, m_robot_col) == true)
        {
            move(direction, m_robot_row, m_robot_col);
            switch (direction)
            {
                case DIRECTION_UP:
                    m_robot_row--;
                    break;
                case DIRECTION_DOWN:
                    m_robot_row++;
                    break;
                case DIRECTION_LEFT:
                    m_robot_col--;
                    break;
                case DIRECTION_RIGHT:
                    m_robot_col++;
                    break;
            }
        }
#ifdef DEBUG_DAY_15_EVERY_STEP
        display_map();
#endif
    }
    
    int ExpandedFishMap::get_gps_score_total()
    {
        int total = 0;
        for (int i=0; i<m_rows; i++)
        {
            for (int j=0; j<m_cols; j++)
            {
                if (m_data[i][j] == MAP_BOX_LEFT)
                {
                    total += ((100 * i) + j);
                }
            }
        }
        return total;
    }
    
}

AocDay15::AocDay15():AocDay(15)
{
}

AocDay15::~AocDay15()
{
}

vector<string> AocDay15::read_input(string filename)
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

string AocDay15::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    int num_map_rows;
    for (int i=0; i<data.size(); i++)
    {
        if (data[i].length() == 0)
        {
            num_map_rows = i;
            break;
        }
    }
    
    FishMap map;
    map.load_map(data, num_map_rows);
    map.display_map();
    
    for (int i=num_map_rows+1; i<data.size(); i++)
    {
        for (int j=0; j<data[i].length(); j++)
        {
            map.perform_robot_move(data[i][j]);
        }
    }
    
    ostringstream out;
    out << map.get_gps_score_total();
    return out.str();
}

string AocDay15::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    int num_map_rows;
    for (int i=0; i<data.size(); i++)
    {
        if (data[i].length() == 0)
        {
            num_map_rows = i;
            break;
        }
    }
    
    ExpandedFishMap map;
    map.load_map(data, num_map_rows);
    map.display_map();
    
    for (int i=num_map_rows+1; i<data.size(); i++)
    {
        for (int j=0; j<data[i].length(); j++)
        {
            map.perform_robot_move(data[i][j]);
        }
    }
    
    ostringstream out;
    out << map.get_gps_score_total();
    return out.str();
}
