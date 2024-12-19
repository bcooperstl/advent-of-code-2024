#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_8.h"
#include "file_utils.h"

using namespace std;
using namespace Day8;

#define EMPTY_LOCATION '.'

namespace Day8
{
    bool Location::operator == (const Location & other)
    {
        return ((row==other.row) && (col==other.col));
    }
    
    Frequency::Frequency()
    {
    }
    
    Frequency::Frequency(char symbol)
    {
        m_symbol = symbol;
    }
    
    Frequency::~Frequency()
    {
    }
    
    void Frequency::add_node(Location location)
    {
#ifdef DEBUG_DAY_8
        cout << "Frequency " << m_symbol << " has a node at row=" << location.row << " col=" << location.col << endl;
#endif
        m_nodes.push_back(location);
    }
    
    // this returns all antinodes, whether they are in the map or not. this list may have dupes
    vector<Location> Frequency::get_antinodes()
    {
        vector<Location> antinodes;
#ifdef DEBUG_DAY_8
        cout << "Finding antinodes for frequency " << m_symbol << endl;
#endif
        
        for (int i=0; i<m_nodes.size()-1; i++)
        {
            for (int j=i+1; j<m_nodes.size(); j++)
            {
#ifdef DEBUG_DAY_8
                cout << " Antinodes for locations row=" << m_nodes[i].row << " col=" << m_nodes[i].col
                     << " and row=" << m_nodes[j].row << " col=" << m_nodes[j].col << ":" << endl;
#endif
                Location one, two;
                int row_change = m_nodes[i].row - m_nodes[j].row;
                int col_change = m_nodes[i].col - m_nodes[j].col;
                
                // 2,4  3,1
                // rc=-1, cc=3
                // 2+-1=1, 4+3=7
                // 3--1=4, 1-3=-2
                
                // 3,1 2,4
                // rc=1, cc=-3
                // 3+1-4, 2+-3=-1
                // 2-1=1, 4--3=7
                
                // 1,2 3,4
                // rc=-2, cc=-2
                // 1+-2=-1, 2+-2=0
                // 3--2=5, 4--2=6
                
                // 3,4 1,2
                // rc=2, cc=2
                // 3+2=5, 4+2=6
                // 1-2=-1, 2-2=0
                
                one.row = m_nodes[i].row+row_change;
                one.col = m_nodes[i].col+col_change;
                two.row = m_nodes[j].row-row_change;
                two.col = m_nodes[j].col-col_change;
                
#ifdef DEBUG_DAY_8
                cout << "  Antinode at row=" << one.row << " col=" << one.col << endl;
                cout << "  Antinode at row=" << two.row << " col=" << two.col << endl;
#endif
                
                antinodes.push_back(one);
                antinodes.push_back(two);
            }
        }
        return antinodes;
    }
    
    vector<Location> Frequency::get_harmonic_antinodes(int min_row, int max_row, int min_col, int max_col)
    {
        vector<Location> antinodes;
#ifdef DEBUG_DAY_8
        cout << "Finding antinodes for frequency " << m_symbol << endl;
#endif
        
        for (int i=0; i<m_nodes.size()-1; i++)
        {
            for (int j=i+1; j<m_nodes.size(); j++)
            {
                int row_change = m_nodes[i].row - m_nodes[j].row;
                int col_change = m_nodes[i].col - m_nodes[j].col;
#ifdef DEBUG_DAY_8
                cout << " Antinodes for locations row=" << m_nodes[i].row << " col=" << m_nodes[i].col
                     << " and row=" << m_nodes[j].row << " col=" << m_nodes[j].col 
                     << " with row_change=" << row_change << " and col_change=" << col_change << ":" << endl;
#endif
                Location loc;

                // first do nodes moving in the positive change direction from the i node
                loc.row = m_nodes[i].row;
                loc.col = m_nodes[i].col;
                while (loc.row >= min_row && loc.row <= max_row &&
                       loc.col >= min_col && loc.col <= max_col)
                {
#ifdef DEBUG_DAY_8
                cout << "  Antinode at row=" << loc.row << " col=" << loc.col << endl;
#endif
                    antinodes.push_back(loc);

                    loc.row+=row_change;
                    loc.col+=col_change;
                }

                // next do nodes moving in the negative change direction from the j node
                loc.row = m_nodes[j].row;
                loc.col = m_nodes[j].col;
                while (loc.row >= min_row && loc.row <= max_row &&
                       loc.col >= min_col && loc.col <= max_col)
                {
#ifdef DEBUG_DAY_8
                cout << "  Antinode at row=" << loc.row << " col=" << loc.col << endl;
#endif
                    antinodes.push_back(loc);

                    loc.row-=row_change;
                    loc.col-=col_change;
                }
            }
        }
        return antinodes;
    }

    City::City()
    {
    }
    
    City::~City()
    {
    }
    
    void City::add_node(char symbol, Location location)
    {
        if (m_frequencies.find(symbol) != m_frequencies.end())
        {
            m_frequencies.at(symbol).add_node(location);
        }
        else
        {
            Frequency frequency(symbol);
            frequency.add_node(location);
            m_frequencies[symbol] = frequency;
        }
    }
    
    vector <Location> City::get_all_antinodes_in_city()
    {
#ifdef DEBUG_DAY_8
        cout << "~~Building antinodes for city" << endl;
#endif
        vector<Location> antinodes;
        map<char, Frequency>::iterator pos = m_frequencies.begin();
        while (pos != m_frequencies.end())
        {
            Frequency current = pos->second;
            vector<Location> curr_antinodes = current.get_antinodes();
            for (int i=0; i<curr_antinodes.size(); i++)
            {
                bool found = false;
                for (int j=0; j<antinodes.size(); j++)
                {
                    if (curr_antinodes[i] == antinodes[j])
                    {
#ifdef DEBUG_DAY_8
                        cout << "~~~Antinode at row=" << curr_antinodes[i].row << " col=" << curr_antinodes[i].col << " already exists" << endl;
#endif
                        found = true;
                        break;
                    }
                }
                if (found == false)
                {
                    if (curr_antinodes[i].row < m_min_row || curr_antinodes[i].row > m_max_row ||
                        curr_antinodes[i].col < m_min_col || curr_antinodes[i].col > m_max_col)
                    {
#ifdef DEBUG_DAY_8
                        cout << "~~~Antinode at row=" << curr_antinodes[i].row << " col=" << curr_antinodes[i].col << " is outside of the map" << endl;
#endif                        
                    }
                    else
                    {
#ifdef DEBUG_DAY_8
                        cout << "~~~Adding antinode at row=" << curr_antinodes[i].row << " col=" << curr_antinodes[i].col << endl;
#endif
                        antinodes.push_back(curr_antinodes[i]);
                    }
                }
            }
            ++pos;
        }
        return antinodes;
    }
    
    vector <Location> City::get_all_harmonic_antinodes_in_city()
    {
#ifdef DEBUG_DAY_8
        cout << "~~Building harmonic antinodes for city" << endl;
#endif
        vector<Location> antinodes;
        map<char, Frequency>::iterator pos = m_frequencies.begin();
        while (pos != m_frequencies.end())
        {
            Frequency current = pos->second;
            vector<Location> curr_antinodes = current.get_harmonic_antinodes(m_min_row, m_max_row, m_min_col, m_max_col);
            for (int i=0; i<curr_antinodes.size(); i++)
            {
                bool found = false;
                for (int j=0; j<antinodes.size(); j++)
                {
                    if (curr_antinodes[i] == antinodes[j])
                    {
#ifdef DEBUG_DAY_8
                        cout << "~~~Antinode at row=" << curr_antinodes[i].row << " col=" << curr_antinodes[i].col << " already exists" << endl;
#endif
                        found = true;
                        break;
                    }
                }
                // bound checking is now done in get_harmonic_antinodes so no need to duplicate it here
                if (found == false)
                {
#ifdef DEBUG_DAY_8
                    cout << "~~~Adding antinode at row=" << curr_antinodes[i].row << " col=" << curr_antinodes[i].col << endl;
#endif
                    antinodes.push_back(curr_antinodes[i]);
                }
            }
            ++pos;
        }
        return antinodes;
    }

    void City::map_city(vector<string> data)
    {
        m_min_row = 0;
        m_max_row = data.size() - 1;
        m_min_col = 0;
        m_max_col = data[0].length()  - 1;
#ifdef DEBUG_DAY_8
        cout << "City goes from row " << m_min_row << " to row " << m_max_row 
             << " and from col " << m_min_col << " to col " << m_max_col << endl;
#endif
        for (int row=m_min_row; row<=m_max_row; row++)
        {
            string row_data = data[row];
            for (int col=m_min_col; col<=m_max_col; col++)
            {
                if (row_data[col] != EMPTY_LOCATION)
                {
                    Location loc;
                    loc.row = row;
                    loc.col = col;
                    add_node(row_data[col], loc);
                }
            }
        }
    }
}

AocDay8::AocDay8():AocDay(8)
{
}

AocDay8::~AocDay8()
{
}

vector<string> AocDay8::read_input(string filename)
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

string AocDay8::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    City city;
    city.map_city(data);
    vector<Location> antinodes = city.get_all_antinodes_in_city();
    
    ostringstream out;
    out << antinodes.size();
    return out.str();
}

string AocDay8::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    City city;
    city.map_city(data);
    vector<Location> antinodes = city.get_all_harmonic_antinodes_in_city();
    
    ostringstream out;
    out << antinodes.size();
    return out.str();
}
