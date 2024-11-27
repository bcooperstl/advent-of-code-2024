#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_24.h"
#include "file_utils.h"

using namespace std;

AocDay24::AocDay24():AocDay(24)
{
}

AocDay24::~AocDay24()
{
}

vector<string> AocDay24::read_input(string filename)
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

string AocDay24::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    out << "Day 24 - Part 1 not implemented";
    return out.str();
}

string AocDay24::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 24 - Part 2 not implemented";
    return out.str();
}
