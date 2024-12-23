#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_10.h"
#include "file_utils.h"

using namespace std;
using namespace Day10;

namespace Day10
{
    Map::Map()
    {
        m_rows = 0;
        m_cols = 0;
    }
    
    Map::~Map()
    {
    }
    
    void Map::load_map(vector<string> data)
    {
        m_rows = data.size();
        m_cols = data[0].length();
        
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                m_map[row][col].height = data[row][col]-'0';
                m_map[row][col].reachable_high_points.clear();
            }
        }
        
#ifdef DEBUG_DAY_10
        cout << "Loaded map of " << m_rows << " rows and " << m_cols << " columns." << endl;
#endif
    }

    void Map::add_high_points(Location * destination, Location * source)
    {
        vector<ReachableHighPoint>::iterator src_pos=source->reachable_high_points.begin();
        while (src_pos != source->reachable_high_points.end())
        {
            int row=(*src_pos).row;
            int col=(*src_pos).col;
            
            bool found=false;
            for (vector<ReachableHighPoint>::iterator dst_pos=destination->reachable_high_points.begin(); dst_pos!=destination->reachable_high_points.end(); dst_pos++)
            {
                if (row==(*dst_pos).row && col==(*dst_pos).col)
                {
#ifdef DEBUG_DAY_10
                    cout << "  High point row=" << row << " col=" << col << " already included" << endl;
#endif
                    found=true;
                    break;
                }
            }
            
            if (!found)
            {
#ifdef DEBUG_DAY_10
                cout << "  Adding high point row=" << row << " col=" << col << endl;
#endif
                destination->reachable_high_points.push_back(*src_pos);
            }
            
            ++src_pos;
        }
    }
    
    void Map::find_paths_to_high_points(int height)
    {
#ifdef DEBUG_DAY_10
        cout << "Finding paths to high points at height " << height << endl;
#endif
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                if (m_map[row][col].height == height)
                {
                    if (height == 9)
                    {
#ifdef DEBUG_DAY_10
                        cout << " Level point at row=" << row << " col=" << col << endl;
#endif
                        ReachableHighPoint loc;
                        loc.row=row;
                        loc.col=col;
                        m_map[row][col].reachable_high_points.push_back(loc);
                    }
                    else
                    {
#ifdef DEBUG_DAY_10
                        cout << " Checking neighbors at row=" << row << " col=" << col << endl;
#endif
                        // north
                        if (row > 0)
                        {
                            if (m_map[row-1][col].height == (height+1))
                            {
#ifdef DEBUG_DAY_10
                                cout << " Using North neighbor at row=" << row-1 << " col=" << col << " with level " << height+1 << endl;
#endif
                                add_high_points(&m_map[row][col], &m_map[row-1][col]);
                            }
                            else
                            {
#ifdef DEBUG_DAY_10
                                cout << " Skipping North neighbor at row=" << row-1 << " col=" << col << " with level " << height+1 << endl;
#endif
                            }
                        }

                        // south
                        if (row < (m_rows-1))
                        {
                            if (m_map[row+1][col].height == (height+1))
                            {
#ifdef DEBUG_DAY_10
                                cout << " Using South neighbor at row=" << row+1 << " col=" << col << " with level " << height+1 << endl;
#endif
                                add_high_points(&m_map[row][col], &m_map[row+1][col]);
                            }
                            else
                            {
#ifdef DEBUG_DAY_10
                                cout << " Skipping South neighbor at row=" << row+1 << " col=" << col << " with level " << height+1 << endl;
#endif
                            }
                        }
                        
                        // west
                        if (col > 0)
                        {
                            if (m_map[row][col-1].height == (height+1))
                            {
#ifdef DEBUG_DAY_10
                                cout << " Using West neighbor at row=" << row << " col=" << col-1 << " with level " << height+1 << endl;
#endif
                                add_high_points(&m_map[row][col], &m_map[row][col-1]);
                            }
                            else
                            {
#ifdef DEBUG_DAY_10
                                cout << " Skipping West neighbor at row=" << row << " col=" << col-1 << " with level " << height+1 << endl;
#endif
                            }
                        }
                        
                        // east
                        if (col < (m_cols-1))
                        {
                            if (m_map[row][col+1].height == (height+1))
                            {
#ifdef DEBUG_DAY_10
                                cout << " Using East neighbor at row=" << row << " col=" << col+1 << " with level " << height+1 << endl;
#endif
                                add_high_points(&m_map[row][col], &m_map[row][col+1]);
                            }
                            else
                            {
#ifdef DEBUG_DAY_10
                                cout << " Skipping East neighbor at row=" << row << " col=" << col+1 << " with level " << height+1 << endl;
#endif
                            }
                        }

                    }
                }
            }
        }
        return;
    }
    
    int Map::get_total_score()
    {
        int sum=0;
        for (int row=0; row<m_rows; row++)
        {
            for (int col=0; col<m_cols; col++)
            {
                if (m_map[row][col].height == 0)
                {
#ifdef DEBUG_DAY_10
                    cout << "Starting point at row=" << row << " col=" << col << " has score of " << m_map[row][col].reachable_high_points.size() << endl;
#endif
                    sum+=m_map[row][col].reachable_high_points.size();
                }
            }
        }
        return sum;
    }
}

AocDay10::AocDay10():AocDay(10)
{
}

AocDay10::~AocDay10()
{
}

vector<string> AocDay10::read_input(string filename)
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

string AocDay10::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Map map;
    
    map.load_map(data);
    for (int level=9; level>=0; level--)
    {
        map.find_paths_to_high_points(level);
    }
    
    ostringstream out;
    out << map.get_total_score();
    return out.str();
}

string AocDay10::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 10 - Part 2 not implemented";
    return out.str();
}
