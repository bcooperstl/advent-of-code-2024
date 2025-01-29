#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_11.h"
#include "file_utils.h"

using namespace std;
using namespace Day11;

namespace Day11
{
    StoneProcessor::StoneProcessor()
    {
    }
    
    StoneProcessor::~StoneProcessor()
    {
    }
    
    vector<StoneQuantity> StoneProcessor::perform_blink(long long int value)
    {
        vector<StoneQuantity> results;
        // if the value is 0, replace it with a 1
#ifdef DEBUG_DAY_11
        cout << "Performing blink for value " << value << " results in:" << endl;;
#endif
        ostringstream tmp;
        tmp << value;
        string value_str = tmp.str();
        if (value == 0)
        {
            StoneQuantity sq;
            sq.quantity = 1;
            sq.value = 1;
            results.push_back(sq);
        }
        else if (value_str.length() % 2 == 0) // if even length, split into 2 values
        {
            string left = value_str.substr(0, (value_str.length()/2));
            string right = value_str.substr((value_str.length()/2), (value_str.length()/2));
            long long int left_val = strtoll(left.c_str(), NULL, 10);
            long long int right_val = strtoll(right.c_str(), NULL, 10);
            StoneQuantity sq[2];
            if (left_val == right_val)
            {
                sq[0].quantity=2;
                sq[0].value = left_val;
                results.push_back(sq[0]);
            }
            else
            {
                sq[0].quantity = 1;
                sq[0].value = left_val;
              
                sq[1].quantity = 1;
                sq[1].value = right_val;
                
                results.push_back(sq[0]);
                results.push_back(sq[1]);
            }
        }
        else
        {
            StoneQuantity sq;
            sq.quantity=1;
            sq.value=value*2024ll; // 2024 as a long long
            results.push_back(sq);
        }
#ifdef DEBUG_DAY_11
        for (int i=0; i<results.size(); i++)
        {
            cout << " Value " << results[i].value << " with quantity " << results[i].quantity << endl;
        }
#endif
        return results;
    }
    
    void StoneProcessor::build_single_digit_dictionary()
    {
        for (int i=0; i<=9; i++)
        {
            vector<StoneQuantity> ret = perform_blink(i);
        }
        
    }
}




AocDay11::AocDay11():AocDay(11)
{
}

AocDay11::~AocDay11()
{
}

vector<long> AocDay11::read_input(string filename)
{
    FileUtils fileutils;
    vector<vector<long>> data;
    if (!fileutils.read_as_list_of_split_longs(filename, data, ' ', '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data[0];
    }
    return data[0];
}

string AocDay11::part1(string filename, vector<string> extra_args)
{
    vector<long> data = read_input(filename);
    
    StoneProcessor processor;
    processor.build_single_digit_dictionary();
    
    ostringstream out;
    out << "Day 11 - Part 1 not implemented";
    return out.str();
}

string AocDay11::part2(string filename, vector<string> extra_args)
{
    vector<long> data = read_input(filename);

    ostringstream out;
    out << "Day 11 - Part 2 not implemented";
    return out.str();
}
