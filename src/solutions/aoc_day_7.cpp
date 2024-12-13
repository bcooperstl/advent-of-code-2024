#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_7.h"
#include "file_utils.h"

using namespace std;
using namespace Day7;

AocDay7::AocDay7():AocDay(7)
{
}

AocDay7::~AocDay7()
{
}

bool AocDay7::is_calibration_valid(Calibration calibration)
{
    vector<unsigned long long int> in_progress;
    // add the first value as the only operand so far
    in_progress.push_back(calibration.numbers[0]);
#ifdef DEBUG_DAY_7
    cout << "Searching for calibration with result " << calibration.result << endl;
    cout << "Starting with " << calibration.numbers[0] << " as the first operand" << endl;
#endif
    for (int i=1; i<calibration.numbers.size(); i++)
    {
#ifdef DEBUG_DAY_7
        cout << "Applying operand " << calibration.numbers[i] << ":" << endl;
#endif
        vector<unsigned long long int> results;
        for (int j=0; j<in_progress.size(); j++)
        {
            // addition operation first
            unsigned long long int result = calibration.numbers[i] + in_progress[j];
#ifdef DEBUG_DAY_7
            cout << " " << calibration.numbers[i] << " + " <<  in_progress[j] << " = " << result << endl;
#endif
            if (result <= calibration.result)
            {
                results.push_back(result);
            }
            else
            {
#ifdef DEBUG_DAY_7
                cout << "  too large...removing" << endl;
#endif
            }
            
            // multiplication operation second
            result = calibration.numbers[i] * in_progress[j];
            cout << " " << calibration.numbers[i] << " * " <<  in_progress[j] << " = " << result << endl;
            if (result <= calibration.result)
            {
                results.push_back(result);
            }
            else
            {
#ifdef DEBUG_DAY_7
                cout << "  too large...removing" << endl;
#endif
            }
        }
        in_progress = results;
    }
    for (int i=0; i<in_progress.size(); i++)
    {
        if (calibration.result == in_progress[i])
        {
#ifdef DEBUG_DAY_7
            cout << "Matching result " << calibration.result << " found!" << endl;
#endif
            return true;
        }
    }
#ifdef DEBUG_DAY_7
    cout << "No matching result " << calibration.result << " found." << endl;
#endif
    return false;
}

void AocDay7::parse_input(string filename, vector<Calibration> & calibrations)
{
    FileUtils fileutils;
    vector<vector<string>> raw_data;
    char delimeters[3] = ": ";
    if (!fileutils.read_as_list_of_split_strings(filename, raw_data, delimeters, 2, '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return;
    }
    
    for (int i=0; i<raw_data.size(); i++)
    {
        Calibration cal;
        cal.result = strtoull(raw_data[i][0].c_str(), NULL, 10);
        for (int j=1; j<raw_data[i].size(); j++)
        {
            unsigned long long int number = strtoull(raw_data[i][j].c_str(), NULL, 10);
            cal.numbers.push_back(number);
        }
        calibrations.push_back(cal);
    }
    return;
}

string AocDay7::part1(string filename, vector<string> extra_args)
{
    vector<Calibration> calibrations;
    parse_input(filename, calibrations);
    
    unsigned long long int sum = 0;
    for (int i=0; i<calibrations.size(); i++)
    {
        if (is_calibration_valid(calibrations[i]))
        {
            sum += calibrations[i].result;
        }
    }
    
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay7::part2(string filename, vector<string> extra_args)
{
    vector<Calibration> calibrations;
    parse_input(filename, calibrations);

    ostringstream out;
    out << "Day 7 - Part 2 not implemented";
    return out.str();
}
