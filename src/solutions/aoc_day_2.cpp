#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_2.h"
#include "file_utils.h"

#define MIN_NEXT_DIFFERENCE 1
#define MAX_NEXT_DIFFERENCE 3

using namespace std;
using namespace Day2;

namespace Day2
{
    Report::Report()
    {
        m_num_levels = 0;
    }
    
    Report::~Report()
    {
    }
    
    bool Report::load_report(vector<long> raw_data)
    {
        if (raw_data.size() > DAY_2_MAX_LEVELS)
        {
            cerr << "REPORT HAS " << raw_data.size() << " ELEMENTS!! INCREASE LEVEL ARRAY SIZE!!" << endl;
            return false;
        }
        for (int i=0; i<raw_data.size(); i++)
        {
            m_levels[i] = raw_data[i];
        }
        m_num_levels = raw_data.size();
        return true;
    }
    
    bool Report::is_safe()
    {
        if (m_num_levels == 1)
        {
#ifdef DEBUG_DAY_2
            cerr << "Report has 1 level and is safe" << endl;
#endif
            return true;
        }
        Direction dir = (m_levels[1] > m_levels[0]) ? increasing : decreasing;
        for (int i=1; i<m_num_levels; i++)
        {
            long difference;
            if (dir == increasing)
            {
                difference = m_levels[i] - m_levels[i-1];
            }
            else
            {
                difference = m_levels[i-1] - m_levels[i];
            }
            
            if ((difference < MIN_NEXT_DIFFERENCE) || (difference > MAX_NEXT_DIFFERENCE))
            {
#ifdef DEBUG_DAY_2
                cout << "Report is not safe because " << m_levels[i] << " is not between " 
                     << MIN_NEXT_DIFFERENCE << " and " << MAX_NEXT_DIFFERENCE << " "
                     << (difference == increasing ? "more" : "less") << " than " << m_levels[i-1] 
                     << " with calculated difference " << difference << endl;
#endif
                return false;
            }
        }
#ifdef DEBUG_DAY_2
        cout << "Report is safe" << endl;
#endif
        return true;        
    }
    
}

AocDay2::AocDay2():AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

bool AocDay2::parse_input(string filename, vector<Report> & reports)
{
    FileUtils fileutils;
    reports.clear();
    vector<vector<long>> data;
    if (!fileutils.read_as_list_of_split_longs(filename, data, ' ', '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return false;
    }
    for (int i=0; i<data.size(); i++)
    {
        Report report;
        if (!report.load_report(data[i]))
        {
            reports.clear();
            return false;
        }
        reports.push_back(report);
    }
        
    return true;
}

string AocDay2::part1(string filename, vector<string> extra_args)
{
    vector<Report> reports;
    
    if (!parse_input(filename, reports))
    {
        return "";
    }
    
    ostringstream out;
    int num_safe = 0;
    for (int i=0; i<reports.size(); i++)
    {
#ifdef DEBUG_DAY_2
        cout << "Checking report " << i << ": ";
#endif
        if (reports[i].is_safe())
        {
            num_safe++;
        }
    }
    out << num_safe;
    return out.str();
}

string AocDay2::part2(string filename, vector<string> extra_args)
{
    ostringstream out;
    out << "Day 2 - Part 2 not implemented";
    return out.str();
}
