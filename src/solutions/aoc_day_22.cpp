#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_22.h"
#include "file_utils.h"

using namespace std;

AocDay22::AocDay22():AocDay(22)
{
}

AocDay22::~AocDay22()
{
}

vector<string> AocDay22::read_input(string filename)
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

string AocDay22::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    out << "Day 22 - Part 1 not implemented";
    return out.str();
}

string AocDay22::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 22 - Part 2 not implemented";
    return out.str();
}
