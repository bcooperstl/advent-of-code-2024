#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_6.h"
#include "file_utils.h"

using namespace std;

using namespace Day6;

#define DAY_6_SPACE '.'
#define DAY_6_OBSTRUCTION '#'
#define DAY_6_START '^'
#define DAY_6_VISITED 'X'

#define DAY_6_NOT_VISITED 0
#define DAY_6_VISITED_NORTH 1
#define DAY_6_VISITED_EAST 2
#define DAY_6_VISITED_SOUTH 4
#define DAY_6_VISITED_WEST 8
#define DAY_6_VISITED_ANY 15

namespace Day6
{
    Map::Map(vector<string> data)
    {
        init_directions();
        
        load_data(data);
    }
    
    Map::~Map()
    {
    }
    
    void Map::init_directions()
    {
        m_directions.directions[0].symbol='^';
        m_directions.directions[0].visited_mask=DAY_6_VISITED_NORTH;
        m_directions.directions[0].move_x=0;
        m_directions.directions[0].move_y=-1;

        m_directions.directions[1].symbol='>';
        m_directions.directions[1].visited_mask=DAY_6_VISITED_EAST;
        m_directions.directions[1].move_x=1;
        m_directions.directions[1].move_y=0;

        m_directions.directions[2].symbol='v';
        m_directions.directions[2].visited_mask=DAY_6_VISITED_SOUTH;
        m_directions.directions[2].move_x=0;
        m_directions.directions[2].move_y=1;

        m_directions.directions[3].symbol='<';
        m_directions.directions[3].visited_mask=DAY_6_VISITED_WEST;
        m_directions.directions[3].move_x=-1;
        m_directions.directions[3].move_y=0;
        
    }
    
    void Map::load_data(vector<string> data)
    {
        m_rows = data.size();
        m_cols = data[0].length();
        
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                m_map[y][x].symbol=data[y][x];
                m_map[y][x].visited_part1=DAY_6_NOT_VISITED;
                m_map[y][x].visited_part1=DAY_6_NOT_VISITED;
                if (m_map[y][x].symbol == DAY_6_START)
                {
#ifdef DEBUG_DAY_6
                    cout << "Starting position found at x=" << x << " and y=" << y << " direction " << m_map[y][x].symbol << endl;
#endif
                    m_location_x=x;
                    m_location_y=y;
                    m_start_x=x;
                    m_start_y=y;
                    m_current_direction_index = 0;
                }
            }
        }
#ifdef DEBUG_DAY_6
        cout << "Starting screen is:" << endl;
        display();
        cout << "Map goes from min_x 0  to max_x " << m_cols - 1
             << " and min_y 0 to max_y " << m_rows - 1 << endl;
#endif
        return;
        
    }
    
    void Map::display()
    {
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                if (m_map[y][x].visited_part1 != DAY_6_NOT_VISITED)
                {
                    cout << DAY_6_VISITED;
                }
                else
                {
                    cout << m_map[y][x].symbol;
                }
            }
            cout << endl;
        }
        
        return;
    }
    
    void Map::display_part2()
    {
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                cout << m_map[y][x].symbol;
            }
            cout << endl;
        }
        cout << "NORTH:" << endl;
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                cout << (m_map[y][x].visited_part2 & DAY_6_VISITED_NORTH ? '^' : ' ');
            }
            cout << endl;
        }
        cout << "EAST:" << endl;
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                cout << (m_map[y][x].visited_part2 & DAY_6_VISITED_EAST ? '>' : ' ');
            }
            cout << endl;
        }
        cout << "SOUTH:" << endl;
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                cout << (m_map[y][x].visited_part2 & DAY_6_VISITED_SOUTH ? 'v' : ' ');
            }
            cout << endl;
        }
        cout << "WEST" << endl;
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                cout << (m_map[y][x].visited_part2 & DAY_6_VISITED_WEST ? '<' : ' ');
            }
            cout << endl;
        }

        return;
    }

    bool Map::run_one_step(bool set_visited)
    {
        // mark current position as visited
        if (set_visited)
        {
            m_map[m_location_y][m_location_x].visited_part1 = DAY_6_VISITED_ANY;
        }
        
        // calculate next position for current direction
        int next_x = m_location_x + m_directions.directions[m_current_direction_index].move_x;
        int next_y = m_location_y + m_directions.directions[m_current_direction_index].move_y;
        
        cout << "moving " << m_directions.directions[m_current_direction_index].symbol 
             << " from " << m_location_x << "," << m_location_y
             << " to " << next_x << "," << next_y << endl;
        
        // check if next position is out of bounds
        if ( (next_x < 0) || (next_x >= m_cols) ||
             (next_y < 0) || (next_y >= m_rows) ) 
        {
#ifdef DEBUG_DAY_6
            cout << " This position is out of bounds...all done" << endl; 
#endif
            return false;
        }
        
        // check if next position is space or obstruction
        if (m_map[next_y][next_x].symbol == DAY_6_OBSTRUCTION)
        {
            m_current_direction_index = ((m_current_direction_index + 1 ) % DAY_6_NUM_DIRECTIONS);
#ifdef DEBUG_DAY_6
            cout << " This position has an obstruction. Changing current direction to " << m_directions.directions[m_current_direction_index].symbol << endl;
#endif
        }
        else if ((m_map[next_y][next_x].symbol == DAY_6_SPACE) || 
                 ((m_map[next_y][next_x].symbol == DAY_6_START)))
        {
#ifdef DEBUG_DAY_6
            cout << " Position is available...moving to it" << endl;
#endif
            m_location_x = next_x;
            m_location_y = next_y;
        }
        else
        {
            cerr << "!!!!!invalid value " << m_map[next_y][next_x].symbol << endl;
            return false;
        }
        return true;
    }
    
    void Map::run_to_end()
    {
        while (run_one_step())
        {
#ifdef DEBUG_DAY_6_STEPS
            display();
#endif
        }
#ifdef DEBUG_DAY_6_STEPS
        display();
#endif
    }
    
    int Map::get_num_visited()
    {
        int count=0;
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                if (m_map[row][col].visited_part1==DAY_6_VISITED_ANY)
                {
                    count++;
                }
            }
        }
        return count;
    }
    
    bool Map::does_new_obstruction_loop(int col, int row)
    {
        m_map[row][col].symbol=DAY_6_OBSTRUCTION;
        reset();
        bool loop_found = false;
        
        while (1)
        {
            cout << "Checking for loop at " << m_location_x << "," << m_location_y << endl;
#ifdef DEBUG_DAY_6_STEPS
            display_part2();
#endif
            if (m_map[m_location_y][m_location_x].visited_part2 & m_directions.directions[m_current_direction_index].visited_mask)
            {
#ifdef DEBUG_DAY_6
                cout << "Loop found with duplicate " << m_directions.directions[m_current_direction_index].symbol
                     << " at " << m_location_x << "," << m_location_y << endl;
#endif            
                loop_found=true;
                break;
            }
            
#ifdef DEBUG_DAY_6_STEPS
            cout << "Setting " << m_directions.directions[m_current_direction_index].symbol
                 << " at " << m_location_x << "," << m_location_y << endl;
#endif            
            m_map[m_location_y][m_location_x].visited_part2 = m_map[m_location_y][m_location_x].visited_part2 | m_directions.directions[m_current_direction_index].visited_mask;
            // if this is false, we have exited the map and there is no loop
            
            /* bringing in logic for running one step, since we cannot mark visited here */
            
            if (!run_one_step(false))
            {
#ifdef DEBUG_DAY_6
                cout << "Outside of map!!" << endl;
#endif            
                break;
            }
#ifdef DEBUG_DAY_6_STEPS
            display_part2();
#endif
        }
        
        m_map[row][col].symbol=DAY_6_SPACE;
        return loop_found;
    }
    
    void Map::reset()
    {
        m_location_x = m_start_x;
        m_location_y = m_start_y;
        m_current_direction_index = 0;
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                m_map[y][x].visited_part2=DAY_6_NOT_VISITED;
            }
        }
    }
    
    int Map::get_num_obstruction_loop_positions()
    {
        cout << " Checking for loops " << endl;
        int count = 0;
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                if ((m_map[row][col].visited_part1 == DAY_6_VISITED_ANY) && (m_map[row][col].symbol != DAY_6_START))
                {
                    cout << "Checking with new obstrction at " << col << "," << row << endl;
                    count += (does_new_obstruction_loop(col, row) ? 1 : 0);
                }
            }
        }
        return count;
    }
}

AocDay6::AocDay6():AocDay(6)
{
}

AocDay6::~AocDay6()
{
}

vector<string> AocDay6::read_input(string filename)
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

string AocDay6::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Map map(data);
    
    map.run_to_end();
    
    ostringstream out;
    out << map.get_num_visited();
    return out.str();
}

string AocDay6::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Map map(data);
    
    map.run_to_end();
    
    ostringstream out;
    out << map.get_num_obstruction_loop_positions();
    return out.str();
}
