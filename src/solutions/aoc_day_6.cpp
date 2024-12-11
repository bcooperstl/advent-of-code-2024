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
                    m_start_x=col;
                    m_start_y=row;
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
#ifdef DEBUG_DAY_6
            cout << " This position is out of bounds...all done" << endl; 
#endif
            return false;
        }
        
        // check if next position is space or obstruction
        if (m_screen->get(next_x, next_y) == DAY_6_OBSTRUCTION)
        {
            m_current_direction_index = ((m_current_direction_index + 1 ) % DAY_6_NUM_DIRECTIONS);
#ifdef DEBUG_DAY_6
            cout << " This position has an obstruction. Changing current direction to " << m_directions.directions[m_current_direction_index].symbol << endl;
#endif
        }
        else if ((m_screen->get(next_x, next_y) == DAY_6_SPACE) || 
                 ((m_screen->get(next_x, next_y) == DAY_6_START)))
        {
#ifdef DEBUG_DAY_6
            cout << " Position is available...moving to it" << endl;
#endif
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
    
    bool Map::does_new_obstruction_loop(int col, int row)
    {
        m_screen->set(col, row, DAY_6_OBSTRUCTION);
        m_location_x=m_start_x;
        m_location_y=m_start_y;
        m_current_direction_index=0;
        Overlay direction_maps[4] = {Overlay(m_screen), Overlay(m_screen), Overlay(m_screen), Overlay(m_screen)};
        
        bool loop_found = false;
        
        while (1)
        {
            char current = ((Screen)direction_maps[m_current_direction_index]).get(m_location_x, m_location_y);
            if (current == m_directions.directions[m_current_direction_index].symbol)
            {
#ifdef DEBUG_DAY_6
                cout << "Loop found with duplicate " << m_directions.directions[m_current_direction_index].symbol
                     << " at " << m_location_x << "," << m_location_y << endl;
#endif            
                loop_found=true;
                break;
            }
            
#ifdef DEBUG_DAY_6
            cout << "Setting " << m_directions.directions[m_current_direction_index].symbol
                 << " at " << m_location_x << "," << m_location_y << endl;
#endif            
            direction_maps[m_current_direction_index].set(m_location_x, m_location_y, m_directions.directions[m_current_direction_index].symbol);
            
#ifdef DEBUG_DAY_6_STEPS
            direction_maps[m_current_direction_index].display_overlay();
#endif            
            // if this is false, we have exited the map and there is no loop
            if (!run_one_step())
            {
#ifdef DEBUG_DAY_6
                cout << "Outside of map!!" << endl;
#endif            
                break;
            }
#ifdef DEBUG_DAY_6_STEPS
            m_visited->display_overlay();
#endif
        }
        
        m_screen->set(col, row, DAY_6_SPACE);
        return loop_found;
    }
    
    
    int Map::get_num_obstruction_loop_positions()
    {
        Overlay * original_visited = m_visited;
        
        int count = 0;
        for (int row=m_screen->get_min_y(); row<=m_screen->get_max_y(); row++)
        {
            for (int col=m_screen->get_min_x(); col<=m_screen->get_max_x(); col++)
            {
                if ((original_visited->get(col, row) == DAY_6_VISITED) && (m_screen->get(col, row) != DAY_6_START))
                {
                    cout << "Checking with new obstrction at " << col << "," << row << endl;
                    m_visited = new Overlay(m_screen);
                    count += (does_new_obstruction_loop(col, row) ? 1 : 0);
                    delete m_visited;
                }
            }
        }
        m_visited = original_visited;
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
