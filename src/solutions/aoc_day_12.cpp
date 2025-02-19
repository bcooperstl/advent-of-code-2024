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
#define MAX_REGIONS 750

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
                for (int i=0; i<4; i++)
                {
                    m_plots[y][x].is_perimeter[i] = DAY_12_NO;
                    m_plots[y][x].is_side[i] = DAY_12_NO;
                }
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
            
            if (m_plots[current.first][current.second].region != NO_REGION)
            {
                continue;
            }
            
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
    
    void Farm::calculate_perimeters()
    {
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
#ifdef DEBUG_DAY_12
                cout << "Checking perimeters for row=" << y << " col=" << x << endl;
#endif
                // check north
                if ((y==0) || (m_plots[y][x].region != m_plots[y-1][x].region))
                {
                    m_plots[y][x].is_perimeter[DAY_12_NORTH]=DAY_12_YES;
#ifdef DEBUG_DAY_12
                    cout << " North is a permimeter" << endl;
#endif
                }
                // check south
                if((y==(m_rows-1)) || (m_plots[y][x].region != m_plots[y+1][x].region))
                {
                    m_plots[y][x].is_perimeter[DAY_12_SOUTH]=DAY_12_YES;
#ifdef DEBUG_DAY_12
                    cout << " South is a permimeter" << endl;
#endif
                }
                // check west
                if ((x==0) || (m_plots[y][x].region != m_plots[y][x-1].region))
                {
                    m_plots[y][x].is_perimeter[DAY_12_WEST]=DAY_12_YES;
#ifdef DEBUG_DAY_12
                    cout << " West is a permimeter" << endl;
#endif
                }
                // check east
                if((x==(m_cols-1)) || (m_plots[y][x].region != m_plots[y][x+1].region))
                {
                    m_plots[y][x].is_perimeter[DAY_12_EAST]=DAY_12_YES;
#ifdef DEBUG_DAY_12
                    cout << " East is a permimeter" << endl;
#endif
                }

#ifdef DEBUG_DAY_12
                int sum=0;
                for (int i=0; i<4; i++)
                {
                    sum+=m_plots[y][x].is_perimeter[i];
                }
                cout << " Total perimeters is " << sum << endl;
#endif
            }
        }
    }
    
    void Farm::calculate_sides()
    {
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
#ifdef DEBUG_DAY_12
                cout << "Checking sides for row=" << y << " col=" << x << endl;
#endif

                // check north
                if (m_plots[y][x].is_perimeter[DAY_12_NORTH] == DAY_12_YES)
                {
#ifdef DEBUG_DAY_12
                    cout << " North is a permimeter ";
#endif
                    if ((x==0) || // at the left
                        (m_plots[y][x].region != m_plots[y][x-1].region) || // different regions
                        ((m_plots[y][x].region == m_plots[y][x-1].region) && (m_plots[y][x-1].is_perimeter[DAY_12_NORTH] == DAY_12_NO))) // left is not perimeter
                    {
                        m_plots[y][x].is_side[DAY_12_NORTH] = DAY_12_YES;
#ifdef DEBUG_DAY_12
                        cout << " and is a new side" << endl;
#endif
                    }
                    else
                    {
#ifdef DEBUG_DAY_12
                        cout << " but is not a new side" << endl;
#endif
                    }
                }
                // check south
                if(m_plots[y][x].is_perimeter[DAY_12_SOUTH] == DAY_12_YES)
                {
#ifdef DEBUG_DAY_12
                    cout << " South is a permimeter ";
#endif
                    if ((x==0) || // at the left
                        (m_plots[y][x].region != m_plots[y][x-1].region) || // different regions
                        ((m_plots[y][x].region == m_plots[y][x-1].region) && (m_plots[y][x-1].is_perimeter[DAY_12_SOUTH] == DAY_12_NO))) // left is not perimeter
                    {
                        m_plots[y][x].is_side[DAY_12_SOUTH] = DAY_12_YES;
#ifdef DEBUG_DAY_12
                        cout << " and is a new side" << endl;
#endif
                    }
                    else
                    {
#ifdef DEBUG_DAY_12
                        cout << " but is not a new side" << endl;
#endif
                    }
                }
                // check west
                if (m_plots[y][x].is_perimeter[DAY_12_WEST] == DAY_12_YES)
                {
#ifdef DEBUG_DAY_12
                    cout << " West is a permimeter ";
#endif
                    if ((y==0) || // at the top
                        (m_plots[y][x].region != m_plots[y-1][x].region) || // different regions
                        ((m_plots[y][x].region == m_plots[y-1][x].region) && (m_plots[y-1][x].is_perimeter[DAY_12_WEST] == DAY_12_NO))) // top is not perimeter
                    {
                        m_plots[y][x].is_side[DAY_12_WEST] = DAY_12_YES;
#ifdef DEBUG_DAY_12
                        cout << " and is a new side" << endl;
#endif
                    }
                    else
                    {
#ifdef DEBUG_DAY_12
                        cout << " but is not a new side" << endl;
#endif
                    }
                }
                // check east
                if(m_plots[y][x].is_perimeter[DAY_12_EAST] == DAY_12_YES)
                {
#ifdef DEBUG_DAY_12
                    cout << " East is a permimeter ";
#endif
                    if ((y==0) || // at the top
                        (m_plots[y][x].region != m_plots[y-1][x].region) || // different regions
                        ((m_plots[y][x].region == m_plots[y-1][x].region) && (m_plots[y-1][x].is_perimeter[DAY_12_EAST] == DAY_12_NO))) // top is not perimeter
                    {
                        m_plots[y][x].is_side[DAY_12_EAST] = DAY_12_YES;
#ifdef DEBUG_DAY_12
                        cout << " and is a new side" << endl;
#endif
                    }
                    else
                    {
#ifdef DEBUG_DAY_12
                        cout << " but is not a new side" << endl;
#endif
                    }
                }

#ifdef DEBUG_DAY_12
                int sum=0;
                for (int i=0; i<4; i++)
                {
                    sum+=m_plots[y][x].is_side[i];
                }
                cout << " Total sides is " << sum << endl;
#endif
            }
        }
    }
    
    int Farm::get_total_price()
    {
        int total_price = 0;
        int areas[MAX_REGIONS];
        int perimeters[MAX_REGIONS];
        for (int i=1; i<= m_num_assigned_regions; i++)
        {
            areas[i]=0;
            perimeters[i]=0;
        }
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                areas[m_plots[y][x].region]++;
                perimeters[m_plots[y][x].region]+=(  m_plots[y][x].is_perimeter[DAY_12_NORTH]
                                                   + m_plots[y][x].is_perimeter[DAY_12_SOUTH]
                                                   + m_plots[y][x].is_perimeter[DAY_12_WEST]
                                                   + m_plots[y][x].is_perimeter[DAY_12_EAST]);
            }
        }
        
        for (int i=0; i<m_first_plots.size(); i++)
        {
            int row=m_first_plots[i].first;
            int col=m_first_plots[i].second;
            
            int region=m_plots[row][col].region;
            
#ifdef DEBUG_DAY_12
            cout << "Region " << region 
                 << " with plant " << m_plots[row][col].plant
                 << " has area " << areas[region]
                 << " and perimeter " << perimeters[region]
                 << " resulting in price " << areas[region] * perimeters[region] << endl;
#endif

            total_price += (areas[region] * perimeters[region]);
        }
        
        return total_price;
    }

    int Farm::get_total_discount_price()
    {
        int total_price = 0;
        int areas[MAX_REGIONS];
        int sides[MAX_REGIONS];
        for (int i=1; i<= m_num_assigned_regions; i++)
        {
            areas[i]=0;
            sides[i]=0;
        }
        for (int y=0; y<m_rows; y++)
        {
            for (int x=0; x<m_cols; x++)
            {
                areas[m_plots[y][x].region]++;
                sides[m_plots[y][x].region]+=(  m_plots[y][x].is_side[DAY_12_NORTH]
                                              + m_plots[y][x].is_side[DAY_12_SOUTH]
                                              + m_plots[y][x].is_side[DAY_12_WEST]
                                              + m_plots[y][x].is_side[DAY_12_EAST]);
            }
        }
        
        for (int i=0; i<m_first_plots.size(); i++)
        {
            int row=m_first_plots[i].first;
            int col=m_first_plots[i].second;
            
            int region=m_plots[row][col].region;
            
#ifdef DEBUG_DAY_12
            cout << "Region " << region 
                 << " with plant " << m_plots[row][col].plant
                 << " has area " << areas[region]
                 << " and sides " << sides[region]
                 << " resulting in price " << areas[region] * sides[region] << endl;
#endif

            total_price += (areas[region] * sides[region]);
        }
        
        return total_price;
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
    
    farm.calculate_perimeters();
    
    ostringstream out;
    out << farm.get_total_price();
    return out.str();
}

string AocDay12::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Farm farm(data);
    
    farm.display();
    
    farm.map_regions();
    farm.calculate_perimeters();
    farm.calculate_sides();
    
    ostringstream out;
    out << farm.get_total_discount_price();
    return out.str();
}
