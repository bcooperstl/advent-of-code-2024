#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <regex>

#include "aoc_day_3.h"
#include "file_utils.h"

using namespace std;

// looking to capture mul(aaa,bbb) where a and b are 1-3 digits long

#define MUL_REGEX "mul\\((\\d{1,3})\\,(\\d{1,3})\\)"
#define MUL_DO_DONT_REGEX "mul\\((\\d{1,3})\\,(\\d{1,3})\\)|do\\(\\)|don't\\(\\)"

AocDay3::AocDay3():AocDay(3)
{
}

AocDay3::~AocDay3()
{
}

vector<string> AocDay3::read_input(string filename)
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

long AocDay3::calculate(string line)
{
    long sum = 0;
    
    regex mul_regex(MUL_REGEX);
    regex_token_iterator<string::iterator> regex_end;

    int submatches[] = { 0, 1, 2 };
    regex_token_iterator<string::iterator> regex_pos(line.begin(), line.end(), mul_regex, submatches );
    while (regex_pos != regex_end)
    {
        string whole = *regex_pos;
        regex_pos++;
        string first = *regex_pos;
        regex_pos++;
        string second = *regex_pos;
        regex_pos++;

        long first_val = strtol(first.c_str(), NULL, 10);
        long second_val = strtol(second.c_str(), NULL, 10);

#ifdef DEBUG_DAY_3
        cout << "Match [" << whole << "] results in " << first_val << "*" << second_val << "=" << first_val * second_val << endl;
#endif
        sum+=(first_val*second_val);
    }
    return sum;
}

string AocDay3::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    long sum = 0;
    for (int i=0; i<data.size(); i++)
    {
#ifdef DEBUG_DAY_3
        cout << "Processing line " << i+1 << endl;
#endif
        sum += calculate(data[i]);
    }
    
    ostringstream out;
    out << sum;
    return out.str();
}

long AocDay3::calculate_do_dont(string line)
{
    long sum = 0;
    
    regex mul_regex(MUL_DO_DONT_REGEX);
    regex_token_iterator<string::iterator> regex_end;

    int submatches[] = { 0, 1, 2 };
    regex_token_iterator<string::iterator> regex_pos(line.begin(), line.end(), mul_regex, submatches );
    while (regex_pos != regex_end)
    {
        string whole = *regex_pos;
        regex_pos++;
        
        if (whole.find("mul") != string::npos)
        {
            string first = *regex_pos;
            regex_pos++;
            string second = *regex_pos;
            regex_pos++;

            long first_val = strtol(first.c_str(), NULL, 10);
            long second_val = strtol(second.c_str(), NULL, 10);

#ifdef DEBUG_DAY_3
            if (m_enabled)
            {
                cout << "Enabled: ";
            }
            else
            {
                cout << "Disabled...skipping: ";
            }
            cout << "Match [" << whole << "] results in " << first_val << "*" << second_val << "=" << first_val * second_val << endl;
#endif
            if (m_enabled)
            {
                sum+=(first_val*second_val);
            }
        }
        else if (whole.find("don't") != string::npos)
        {
#ifdef DEBUG_DAY_3
            cout << "Match [" << whole << "] ... setting to disabled" << endl;
#endif
            m_enabled = false;
        }
        else if (whole.find("do") != string::npos)
        {
#ifdef DEBUG_DAY_3
            cout << "Match [" << whole << "] ... setting to enabled" << endl;
#endif
            m_enabled = true;
        }            
    }
    return sum;
}


string AocDay3::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    m_enabled = true;
    
#ifdef DEBUG_DAY_3
    cout << "Setting enabled to true at start of program" << endl;
#endif
    long sum = 0;
    for (int i=0; i<data.size(); i++)
    {
#ifdef DEBUG_DAY_3
        cout << "Processing line " << i+1 << endl;
#endif
        sum += calculate_do_dont(data[i]);
    }
    
    ostringstream out;
    out << sum;
    return out.str();
}
