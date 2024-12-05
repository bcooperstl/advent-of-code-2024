#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_4.h"
#include "file_utils.h"
#include "screen.h"

using namespace std;

AocDay4::AocDay4():AocDay(4)
{
}

AocDay4::~AocDay4()
{
}

vector<string> AocDay4::read_input(string filename)
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

int AocDay4::find_xmas_as_line(Screen & screen)
{
    char xmas_letters[4]={'X','M','A','S'};
    
    int count = 0;
    
    int xmas_locations[8][4][2] = { { { 0, 0},{-1, 0},{-2, 0},{-3, 0} }, // WEST
                                    { { 0, 0},{ 1, 0},{ 2, 0},{ 3, 0} }, // EAST
                                    { { 0, 0},{ 0,-1},{ 0,-2},{ 0,-3} }, // NORTH
                                    { { 0, 0},{ 0, 1},{ 0, 2},{ 0, 3} }, // SOUTH
                                    { { 0, 0},{ 1,-1},{ 2,-2},{ 3,-3} }, // NORTHEAST
                                    { { 0, 0},{-1,-1},{-2,-2},{-3,-3} }, // NORTHWEST
                                    { { 0, 0},{ 1, 1},{ 2, 2},{ 3, 3} }, // SOUTHEAST
                                    { { 0, 0},{-1, 1},{-2, 2},{-3, 3} } }; // SOUTHWEST
                                    
    // get the number of rows and cols
    int min_col=screen.get_min_x();
    int max_col=screen.get_max_x();
    int min_row=screen.get_min_y();
    int max_row=screen.get_max_y();
    
#ifdef DEBUG_DAY_4
    cout << "Screen goes from row " << min_row << " to row " << max_row << " and col " << min_col << " to " << max_col << endl;
#endif
    
    // expand the screen 3 times so no out of bounds
    screen.expand('.');
    screen.expand('.');
    screen.expand('.');
#ifdef DEBUG_DAY_4
    screen.display();
#endif

    for (int row=min_row; row<=max_row; row++)
    {
        for (int col=min_col; col<=max_col; col++)
        {
            if (screen.get(col,row) == xmas_letters[0]) // get takes x,y
            {
#ifdef DEBUG_DAY_4
                cout << "X found at " << col << "," << row << endl;
#endif
                for (int dir=0; dir<8; dir++)
                {
                    bool match = true;
                    for (int letter=0; letter<4; letter++)
                    {
                        if (screen.get(col+xmas_locations[dir][letter][0],row+xmas_locations[dir][letter][1]) != xmas_letters[letter])
                        {
                            match = false;
                            break;
                        }
                    }
                    if (match == true)
                    {
#ifdef DEBUG_DAY_4
                        cout << " XMAS found at " 
                             << col << "," << row << " "
                             << col+xmas_locations[dir][1][0] << "," << row+xmas_locations[dir][1][1] << " "
                             << col+xmas_locations[dir][2][0] << "," << row+xmas_locations[dir][2][1] << " "
                             << col+xmas_locations[dir][3][0] << "," << row+xmas_locations[dir][3][1] << endl;                             
#endif
                        count++;
                    }
                }
            }
        }
    }

    return count;
}


string AocDay4::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Screen screen;
    screen.load(data,0,0);
    
    ostringstream out;
    out << find_xmas_as_line(screen);
    return out.str();
}

string AocDay4::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 4 - Part 2 not implemented";
    return out.str();
}
