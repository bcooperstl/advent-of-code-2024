#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#include "aoc_day_1.h"
#include "file_utils.h"

using namespace std;

AocDay1::AocDay1():AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

void AocDay1::parse_input(string filename, vector<long> & left_list, vector<long> & right_list)
{
    FileUtils fileutils;
    vector<vector<long>> data;
    if (!fileutils.read_as_list_of_split_longs(filename, data, ' ', '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return;
    }
    
    for (int i=0; i<data.size(); i++)
    {
        left_list.push_back(data[i][0]);
        right_list.push_back(data[i][1]);
    }
    
#ifdef DEBUG_DAY_1
    cout << "There were " << left_list.size() << " lines of data" << endl;
#endif
    
    return;
}

long AocDay1::get_count(long target, vector<long> & search_list)
{
    long count = 0;
    for (int i=0; i<search_list.size(); i++)
    {
        if (search_list[i] == target)
        {
            count++;
        }
    }
    return count;
}

string AocDay1::part1(string filename, vector<string> extra_args)
{
    vector<long> left_list, right_list;
    
    parse_input(filename, left_list, right_list);
    
    sort(left_list.begin(), left_list.end());
    sort(right_list.begin(), right_list.end());
    
    long sum_of_differences = 0;
    for (int i=0; i<left_list.size(); i++)
    {
        long difference = labs(left_list[i] - right_list[i]);
        
#ifdef DEBUG_DAY_1
        cout << "Index " << i << ": left = " << left_list[i] << "  right = " << right_list[i] << "  difference = " << difference << endl;
#endif        
        
        sum_of_differences += difference;
    }
    
    ostringstream out;
    out << sum_of_differences;
    return out.str();
}

string AocDay1::part2(string filename, vector<string> extra_args)
{
    vector<long> left_list, right_list;
    
    parse_input(filename, left_list, right_list);
    
    long similarity_score = 0;
    for (int i=0; i<left_list.size(); i++)
    {
        long count = get_count(left_list[i], right_list);
        long score = left_list[i] * count;
#ifdef DEBUG_DAY_1
        cout << "Index " << i << ": left = " << left_list[i] << "  appears " << count << " times in the right list for score of " << score << endl;
#endif        
        
        similarity_score += score;
    }
    
    ostringstream out;
    out << similarity_score;
    return out.str();
}
