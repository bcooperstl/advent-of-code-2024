#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_5.h"
#include "file_utils.h"

using namespace std;

using namespace Day5;

namespace Day5
{
    Rules::Rules()
    {
        for (int i=0; i<DAY_5_MAX_PAGE; i++)
        {
            for (int j=0; j<DAY_5_MAX_PAGE; j++)
            {
                m_ordering[i][j]=undefined;
            }
        }
    }
    
    Rules::~Rules()
    {
    }
    
    Ordering Rules::get_ordering(int first_page, int second_page)
    {
        return m_ordering[first_page][second_page];
    }
    
    void Rules::add_ordering(int first_page, int second_page)
    {
#ifdef DEBUG_DAY_5
        cout << "Setting " << first_page << " to be before " << second_page << " and " 
             << second_page << " to be after " << first_page << endl;
#endif
        m_ordering[first_page][second_page] = first_before;
        m_ordering[second_page][first_page] = first_after;
        return;
    }
    
    Update::Update(vector<long> page_list)
    {
        m_page_list = page_list;
    }
    
    Update::~Update()
    {
    }
    
    bool Update::are_pages_in_order(Rules * rules)
    {
#ifdef DEBUG_DAY_5
        cout << "Checking if pages are in order" << endl;
#endif
        for (int first=0; first<m_page_list.size() - 1; first++)
        {
            for (int second=first+1; second<m_page_list.size(); second++)
            {
#ifdef DEBUG_DAY_5
                cout << " comparing " << m_page_list[first] << " and " << m_page_list[second] << ": ";
#endif
                Ordering result = rules->get_ordering(m_page_list[first], m_page_list[second]);
                switch (result)
                {
                    case first_before:
#ifdef DEBUG_DAY_5
                        cout << "pages are in order due to existing rule" << endl;
#endif
                        continue;
                    case undefined:
#ifdef DEBUG_DAY_5
                        cout << "pages are in order because no rule exists" << endl;
#endif
                        continue;
                    case first_after:
#ifdef DEBUG_DAY_5
                        cout << "pages are out of order due to existing rule" << endl;
#endif
                        return false;
                }
            }
        }
        return true;
    }

    long Update::get_middle_page()
    {
        return m_page_list[(m_page_list.size()) / 2];
    }
    
    void Update::fix_order(Rules * rules)
    {
        vector<long> pages = m_page_list;
        m_page_list.clear();
        while (!pages.empty())
        {
#ifdef DEBUG_DAY_5
            cout << "Searching for element " << m_page_list.size() + 1 << endl;
#endif
            vector<long>::iterator target = pages.begin();
            while (target!=pages.end())
            {
                bool valid = true;
                for (vector<long>::iterator pos = pages.begin(); pos != pages.end(); pos++)
                {
                    Ordering result = rules->get_ordering(*target, *pos);
                    if (result == first_after)
                    {
#ifdef DEBUG_DAY_5
                        cout << " " << *target << " cannot be in this position because it goes after " << *pos << endl;
#endif
                        valid = false;
                        break;
                    }
                }
                if (valid)
                {
                    break;
                }
                target++;
            }
            if (target == pages.end())
            {
                cerr << "!!!LOGIC FAILURE - NO ELEMENT TO ADD!!!" << endl;
                break;
            }
#ifdef DEBUG_DAY_5
            cout << "Adding element " << *target << " to reordered list" << endl;
#endif
            m_page_list.push_back(*target);
            pages.erase(target);
            
        }
        return;
    }
    
}


AocDay5::AocDay5():AocDay(5)
{
}

AocDay5::~AocDay5()
{
}

void AocDay5::parse_input(string filename, Rules & rules, vector<Update> & updates)
{
    FileUtils fileutils;
    vector<vector<long>> raw_data;
    char delimiters[3] = "|,";
    if (!fileutils.read_as_list_of_split_longs(filename, raw_data, delimiters, 2, '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return;
    }
    
    int data_index=0;
    while (raw_data[data_index].size() == 2)
    {
        rules.add_ordering(raw_data[data_index][0], raw_data[data_index][1]);
        data_index++;
    }
    
    data_index++;
    
    while (data_index < raw_data.size())
    {
        Update update(raw_data[data_index]);
        updates.push_back(update);
        data_index++;
    }
    
    return;
}

string AocDay5::part1(string filename, vector<string> extra_args)
{
    Rules rules;
    vector<Update> updates;
    
    parse_input(filename, rules, updates);
    
    int middle_page_sum=0;
    for (int i=0; i<updates.size(); i++)
    {
#ifdef DEBUG_DAY_5
        cout << "Checking update " << i << endl;
#endif
        if (updates[i].are_pages_in_order(&rules) == true)
        {
            int middle_page = updates[i].get_middle_page();
#ifdef DEBUG_DAY_5
            cout << "Adding middle page " << middle_page << " to sum" << endl;
#endif
            middle_page_sum += middle_page;
        }
    }
    
    ostringstream out;
    out << middle_page_sum;
    return out.str();
}

string AocDay5::part2(string filename, vector<string> extra_args)
{
    Rules rules;
    vector<Update> updates;
    
    parse_input(filename, rules, updates);
    
    int middle_page_sum=0;
    for (int i=0; i<updates.size(); i++)
    {
#ifdef DEBUG_DAY_5
        cout << "Checking update " << i << endl;
#endif
        if (updates[i].are_pages_in_order(&rules) == true)
        {
#ifdef DEBUG_DAY_5
            cout << "  Update is in order...skipping" << endl;
#endif
        }
        else
        {
            updates[i].fix_order(&rules);
            int middle_page = updates[i].get_middle_page();
#ifdef DEBUG_DAY_5
            cout << "Adding middle page " << middle_page << " to sum" << endl;
#endif
            middle_page_sum += middle_page;
        }
    }
    
    ostringstream out;
    out << middle_page_sum;
    return out.str();
}
