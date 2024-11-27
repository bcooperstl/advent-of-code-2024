#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_20.h"
#include "file_utils.h"

using namespace std;

AocDay20::AocDay20():AocDay(20)
{
}

AocDay20::~AocDay20()
{
}

vector<string> AocDay20::read_input(string filename)
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

string AocDay20::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    out << "Day 20 - Part 1 not implemented";
    return out.str();
}

string AocDay20::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 20 - Part 2 not implemented";
    return out.str();
}
