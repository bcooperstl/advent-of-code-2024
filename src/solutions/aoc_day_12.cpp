#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <list>

#include "aoc_day_12.h"
#include "file_utils.h"

using namespace std;

using namespace Day12;

#define NO_REGION 0

namespace Day12
{
    Farm::Farm(vector<string> data)
    {
        m_rows = 0;
        m_cols = 0;
        m_num_assigned_regions = NO_REGION;
        load_data(data);
    }
    
    Farm::~Farm()
    {
    }
    
    void Farm::load_data(vector<string> data)
    {
        m_rows = data.size();
        m_cols = data[0].length();
        
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                m_plots[y][x].plant = data[y][x];
                m_plots[y][x].region = 0;
                m_plots[y][x].perimeter_included = 0;
            }
        }        
    }
    
    void Farm::display()
    {
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                cout << m_plots[y][x].plant;
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void Farm::map_region(int start_row, int start_col, int region_number)
    {
#ifdef DEBUG_DAY_12
        cout << "Mapping region " << region_number << " starting at row=" << start_row << " col=" << start_col << endl;
#endif
        list<pair<int, int>> region_plots;
        region_plots.push_back(make_pair(start_row, start_col));
        
        while (!region_plots.empty())
        {
            pair <int, int> current = region_plots.front();
            region_plots.pop_front();
            
            m_plots[current.first][current.second].region = region_number;

#ifdef DEBUG_DAY_12
            cout << " Checking plot row=" << current.first << " col=" << current.second << endl;
#endif
            // check north
            if (current.first > 0)
            {
                if (m_plots[current.first-1][current.second].region == NO_REGION && 
                    m_plots[current.first-1][current.second].plant == m_plots[start_row][start_col].plant)
                {
                    region_plots.push_back(make_pair(current.first-1, current.second));
#ifdef DEBUG_DAY_12
                    cout << "  Adding plot at row=" << current.first-1 << " col=" << current.second << endl;
#endif
                }
            }
            
            // check south
            if (current.first < (m_rows - 1))
            {
                if (m_plots[current.first+1][current.second].region == NO_REGION && 
                    m_plots[current.first+1][current.second].plant == m_plots[start_row][start_col].plant)
                {
                    region_plots.push_back(make_pair(current.first+1, current.second));
#ifdef DEBUG_DAY_12
                    cout << "  Adding plot at row=" << current.first+1 << " col=" << current.second << endl;
#endif
                }
            }
            
            // check west
            if (current.second > 0)
            {
                if (m_plots[current.first][current.second-1].region == NO_REGION && 
                    m_plots[current.first][current.second-1].plant == m_plots[start_row][start_col].plant)
                {
                    region_plots.push_back(make_pair(current.first, current.second-1));
#ifdef DEBUG_DAY_12
                    cout << "  Adding plot at row=" << current.first << " col=" << current.second-1 << endl;
#endif
                }
            }
            
            // check east
            if (current.second < (m_cols - 1))
            {
                if (m_plots[current.first][current.second+1].region == NO_REGION && 
                    m_plots[current.first][current.second+1].plant == m_plots[start_row][start_col].plant)
                {
                    region_plots.push_back(make_pair(current.first, current.second+1));
#ifdef DEBUG_DAY_12
                    cout << "  Adding plot at row=" << current.first << " col=" << current.second+1 << endl;
#endif
                }
            }
        }
        return;
    }
    
    void Farm::map_regions()
    {
        vector<Plot *> plots_to_search;
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                if (m_plots[y][x].region == NO_REGION)
                {
                    m_num_assigned_regions++;
                    m_first_plots.push_back(make_pair(y,x));
                    map_region(y, x, m_num_assigned_regions);
                }
            }
        }
    }
    
}

AocDay12::AocDay12():AocDay(12)
{
}

AocDay12::~AocDay12()
{
}

vector<string> AocDay12::read_input(string filename)
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

string AocDay12::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Farm farm(data);
    
    farm.display();
    
    farm.map_regions();
    
    ostringstream out;
    out << "Day 12 - Part 1 not implemented";
    return out.str();
}

string AocDay12::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 12 - Part 2 not implemented";
    return out.str();
}
