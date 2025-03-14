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
    ostringstream out;
    out << "Day 15 - Part 1 not implemented";
    return out.str();
}

string AocDay15::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 15 - Part 2 not implemented";
    return out.str();
}
