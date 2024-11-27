#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_23.h"
#include "file_utils.h"

using namespace std;

AocDay23::AocDay23():AocDay(23)
{
}

AocDay23::~AocDay23()
{
}

vector<string> AocDay23::read_input(string filename)
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

string AocDay23::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    out << "Day 23 - Part 1 not implemented";
    return out.str();
}

string AocDay23::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 23 - Part 2 not implemented";
    return out.str();
}
