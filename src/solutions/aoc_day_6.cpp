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

namespace Day6
{
    Map::Map(vector<string> data)
    {
        init_directions();
        
        m_screen = new Screen();
        m_screen->load(data);
        m_visited = new Overlay(m_screen);
#ifdef DEBUG_DAY_6
        cout << "Starting screen is:" << endl;
        m_screen->display();
        cout << "Starting visited map is:" << endl;
        m_visited->display_overlay();
        cout << "Map goes from min_x " << m_screen->get_min_x() << " to max_x " << m_screen->get_max_x()
             << " and min_y " << m_screen->get_min_y() << " to max_y " << m_screen->get_max_y() << endl;
#endif
        for (int row=m_screen->get_min_y(); row<=m_screen->get_max_y(); row++)
        {
            for (int col=m_screen->get_min_x(); col<=m_screen->get_max_x(); col++)
            {
                if (m_screen->get(col, row) == DAY_6_START)
                {
#ifdef DEBUG_DAY_6
                    cout << "Starting position found at x=" << col << " and y=" << row << " direction " << m_screen->get(col, row) << endl;
#endif
                    m_location_x=col;
                    m_location_y=row;
                    m_current_direction_index = 0;
                }
            }
        }
    }
    
    Map::~Map()
    {
        delete m_visited;
        delete m_screen;
    }
    
    void Map::init_directions()
    {
        m_directions.directions[0].symbol='^';
        m_directions.directions[0].move_x=0;
        m_directions.directions[0].move_y=-1;

        m_directions.directions[1].symbol='>';
        m_directions.directions[1].move_x=1;
        m_directions.directions[1].move_y=0;

        m_directions.directions[2].symbol='v';
        m_directions.directions[2].move_x=0;
        m_directions.directions[2].move_y=1;

        m_directions.directions[3].symbol='<';
        m_directions.directions[3].move_x=-1;
        m_directions.directions[3].move_y=0;
        
    }
    
    bool Map::run_one_step()
    {
        // mark current position as visited
        m_visited->set(m_location_x, m_location_y, DAY_6_VISITED);
        
        // calculate next position for current direction
        int next_x = m_location_x + m_directions.directions[m_current_direction_index].move_x;
        int next_y = m_location_y + m_directions.directions[m_current_direction_index].move_y;
        
        cout << "moving " << m_directions.directions[m_current_direction_index].symbol 
             << " from " << m_location_x << "," << m_location_y
             << " to " << next_x << "," << next_y << endl;
        
        // check if next position is out of bounds
        if ( (next_x < m_screen->get_min_x()) || (next_x > m_screen->get_max_x()) ||
             (next_y < m_screen->get_min_y()) || (next_y > m_screen->get_max_y()) ) 
        {
            cout << " This position is out of bounds...all done" << endl; 
            return false;
        }
        
        // check if next position is space or obstruction
        if (m_screen->get(next_x, next_y) == DAY_6_OBSTRUCTION)
        {
            m_current_direction_index = ((m_current_direction_index + 1 ) % DAY_6_NUM_DIRECTIONS);
            cout << " This position has an obstruction. Changing current direction to " << m_directions.directions[m_current_direction_index].symbol << endl;
        }
        else if ((m_screen->get(next_x, next_y) == DAY_6_SPACE) || 
                 ((m_screen->get(next_x, next_y) == DAY_6_START)))
        {
            cout << " Position is available...moving to it" << endl;
            m_location_x = next_x;
            m_location_y = next_y;
        }
        else
        {
            cerr << "!!!!!invalid value " << m_screen->get(next_x, next_y) << endl;
            return false;
        }
        return true;
    }
    
    void Map::run_to_end()
    {
        while (run_one_step())
        {
#ifdef DEBUG_DAY_6_STEPS
            m_visited->display_overlay();
#endif
        }
#ifdef DEBUG_DAY_6_STEPS
        m_visited->display_overlay();
#endif
    }
    
    int Map::get_num_visited()
    {
        return m_visited->num_matching(DAY_6_VISITED);
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

    ostringstream out;
    out << "Day 6 - Part 2 not implemented";
    return out.str();
}
