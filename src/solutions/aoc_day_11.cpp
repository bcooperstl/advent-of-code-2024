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
#ifdef DEBUG_DAY_11_PERFORM
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
#ifdef DEBUG_DAY_11_PERFORM
        for (int i=0; i<results.size(); i++)
        {
            cout << " Value " << results[i].value << " with quantity " << results[i].quantity << endl;
        }
#endif
        return results;
    }
    
    void StoneProcessor::build_single_digit_dictionary()
    {
        for (int digit=0; digit<=9; digit++)
        {
#ifdef DEBUG_DAY_11
            cout << "*Processing digit " << digit << endl;
#endif
            // set up the initial digit
            StoneQuantity sq;
            sq.value=digit;
            sq.quantity=1;
            m_single_digit_dictionary[digit][0][digit] = sq;
            for (int blink=1; blink<=DAY_11_NUM_BLINKS; blink++)
            {
#ifdef DEBUG_DAY_11
                cout << endl << "**Processing blink " << blink << endl;
#endif
                map<long long int, StoneQuantity>::iterator pos = m_single_digit_dictionary[digit][blink-1].begin();
                while (pos != m_single_digit_dictionary[digit][blink-1].end())
                {
                    long long int init_value = pos->second.value;
                    long long int init_quantity = pos->second.quantity;
#ifdef DEBUG_DAY_11
                    cout << "***Processing value " << init_value << " with quantity " << init_quantity << endl;
#endif
                    vector<StoneQuantity> after = perform_blink(init_value);
                    
                    for (int after_pos=0; after_pos<after.size(); after_pos++)
                    {
#ifdef DEBUG_DAY_11
                        cout << "****After blink has value " << after[after_pos].value << " with quantity " << after[after_pos].quantity << endl;
#endif
                        if (m_single_digit_dictionary[digit][blink].find(after[after_pos].value) == m_single_digit_dictionary[digit][blink].end())
                        {
                            // not found in post-blink values; add it as a new StoneQuantity
                            StoneQuantity sq_after;
                            sq_after.value = after[after_pos].value;
                            sq_after.quantity = init_quantity * after[after_pos].quantity;
                            m_single_digit_dictionary[digit][blink][sq_after.value] = sq_after;
#ifdef DEBUG_DAY_11
                            cout << "*****Setting new element with value " << sq_after.value << " with quantity " << sq_after.quantity << endl;
#endif
                        }
                        else
                        {
                            // found in post-blink values. add quantity
                            long long int quantity_to_add = init_quantity * after[after_pos].quantity;
                            m_single_digit_dictionary[digit][blink][after[after_pos].value].quantity = m_single_digit_dictionary[digit][blink][after[after_pos].value].quantity + quantity_to_add;
#ifdef DEBUG_DAY_11
                            cout << "*****Adding " << quantity_to_add << " to existing element with value " << after[after_pos].value << " resulting in quantity " << m_single_digit_dictionary[digit][blink][after[after_pos].value].quantity << endl;
#endif
                        }
                    }
                    
                    ++pos;
                }
            }
        }
    }
    
    void StoneProcessor::merge_values_to_results(map<long long int, StoneQuantity> & results, map<long long int, StoneQuantity> & additions, long long int additions_quantity)
    {
        map<long long int, StoneQuantity>::iterator add_pos = additions.begin();
        while (add_pos != additions.end())
        {
            if (results.find(add_pos->first) != results.end())
            {
                results[add_pos->first].quantity = results[add_pos->first].quantity + (add_pos->second.quantity * additions_quantity);
            }
            else
            {
                results[add_pos->first]=add_pos->second;
            }
            
            ++add_pos;
        }
    }
    
    map<long long int, StoneQuantity> StoneProcessor::process_input(map<long long int, StoneQuantity> input_map, int blinks)
    {
        map<long long int, StoneQuantity> results;
        map<long long int, StoneQuantity> current_level;
        map<long long int, StoneQuantity> next_level;
        
        current_level = input_map;
        
        for (int blink=1; blink<=blinks; blink++)
        {
            next_level.clear();
#ifdef DEBUG_DAY_11
            cout << endl << "Processing blink " << blink << endl;
#endif
            map<long long int, StoneQuantity>::iterator pos = current_level.begin();
            while (pos != current_level.end())
            {
                long long int init_value = pos->second.value;
                long long int init_quantity = pos->second.quantity;
#ifdef DEBUG_DAY_11
                cout << " Processing value " << init_value << " with quantity " << init_quantity << endl;
#endif
                // short circuit any 1-digit input values. already pre-computed the results
                if (init_value >= 0 && init_value <= 9)
                {
#ifdef DEBUG_DAY_11
                    cout << "  Short circuiting for value " << init_value << " and using the single-digit lookup" << endl;
#endif
                    merge_values_to_results(results, m_single_digit_dictionary[init_value][blinks-(blink-1)], init_quantity);
                    ++pos;
                    continue;
                }
                
                vector<StoneQuantity> after = perform_blink(init_value);
                    
                for (int after_pos=0; after_pos<after.size(); after_pos++)
                {
#ifdef DEBUG_DAY_11
                    cout << "  After blink has value " << after[after_pos].value << " with quantity " << after[after_pos].quantity << endl;
#endif
                    if (next_level.find(after[after_pos].value) == next_level.end())
                    {
                        // not found in post-blink values; add it as a new StoneQuantity
                        StoneQuantity sq_after;
                        sq_after.value = after[after_pos].value;
                        sq_after.quantity = init_quantity * after[after_pos].quantity;
                        next_level[sq_after.value] = sq_after;
#ifdef DEBUG_DAY_11
                        cout << "    Setting new element with value " << sq_after.value << " with quantity " << sq_after.quantity << endl;
#endif
                    }
                    else
                    {
                        // found in post-blink values. add quantity
                        long long int quantity_to_add = init_quantity * after[after_pos].quantity;
                        next_level[after[after_pos].value].quantity = next_level[after[after_pos].value].quantity + quantity_to_add;
#ifdef DEBUG_DAY_11
                        cout << "    Adding " << quantity_to_add << " to existing element with value " << after[after_pos].value << " resulting in quantity " << next_level[after[after_pos].value].quantity << endl;
#endif
                    }
                }
                ++pos;
            }
            current_level = next_level;
        }
        merge_values_to_results(results, current_level, 1);
        return results;
    }
}



AocDay11::AocDay11():AocDay(11)
{
}

AocDay11::~AocDay11()
{
}

vector<long long int> AocDay11::read_input(string filename)
{
    FileUtils fileutils;
    vector<vector<long>> data;
    vector<long long int> results;
    if (!fileutils.read_as_list_of_split_longs(filename, data, ' ', '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return results;
    }
    
    for (int i=0; i<data[0].size(); i++)
    {
        results.push_back(data[0][i]);
    }
    return results;
}

string AocDay11::part1(string filename, vector<string> extra_args)
{
    vector<long long int> data = read_input(filename);
    
    StoneProcessor processor;
    processor.build_single_digit_dictionary();
    
    map<long long int, StoneQuantity> input_map;
    for (int i=0; i<data.size(); i++)
    {
        StoneQuantity sq;
        sq.quantity = 1;
        sq.value = data[i];
        input_map[sq.value] = sq;
    }
    
    map<long long int, StoneQuantity> results = processor.process_input(input_map, DAY_11_PART_1_BLINKS);
    
    long long int total_stones=0;
    map<long long int, StoneQuantity>::iterator pos = results.begin();
    while (pos != results.end())
    {
        total_stones += pos->second.quantity;
        ++pos;
    }
    
    ostringstream out;
    out << total_stones;
    return out.str();
}

string AocDay11::part2(string filename, vector<string> extra_args)
{
    vector<long long int> data = read_input(filename);
    
    StoneProcessor processor;
    processor.build_single_digit_dictionary();
    
    
    map<long long int, StoneQuantity> input_map;
    for (int i=0; i<data.size(); i++)
    {
        StoneQuantity sq;
        sq.quantity = 1;
        sq.value = data[i];
        input_map[sq.value] = sq;
    }
    
    map<long long int, StoneQuantity> results = processor.process_input(input_map, DAY_11_NUM_BLINKS);
    
    long long int total_stones=0;
    map<long long int, StoneQuantity>::iterator pos = results.begin();
    while (pos != results.end())
    {
        total_stones += pos->second.quantity;
        ++pos;
    }
    
    ostringstream out;
    out << total_stones;
    return out.str();
}
