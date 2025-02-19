#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_13.h"
#include "file_utils.h"

#define BUTTON_A_COST 3
#define BUTTON_B_COST 1

using namespace std;
using namespace Day13;

namespace Day13
{
    Machine::Machine()
    {
        
    }
    
    Machine::~Machine()
    {
    }
    
    /* Example input:
    Button A: X+94, Y+34
    Button B: X+22, Y+67
    Prize: X=8400, Y=5400
    */
    
    void Machine::load_machine(string button_a, string button_b, string prize)
    {
        int pos;
#ifdef DEBUG_DAY_13
        cout << "a: [" << button_a << "]" << endl;
        cout << "b: [" << button_b << "]" << endl;
        cout << "prize: [" << prize << "]" << endl;
#endif        

        
        m_buttons[0].label = 'A';
        m_buttons[0].cost  = BUTTON_A_COST;
        pos = button_a.find('+');
        m_buttons[0].x=strtol(button_a.c_str()+pos+1, NULL, 10);
        pos = button_a.find('+', pos+1);
        m_buttons[0].y=strtol(button_a.c_str()+pos+1, NULL, 10);
        
        m_buttons[1].label = 'B';
        m_buttons[1].cost  = BUTTON_B_COST;
        pos = button_b.find('+');
        m_buttons[1].x=strtol(button_b.c_str()+pos+1, NULL, 10);
        pos = button_b.find('+', pos+1);
        m_buttons[1].y=strtol(button_b.c_str()+pos+1, NULL, 10);
        
        pos = prize.find('=');
        m_prize_x=strtol(prize.c_str()+pos+1, NULL, 10);
        pos = prize.find('=', pos+1);
        m_prize_y=strtol(prize.c_str()+pos+1, NULL, 10);
        
#ifdef DEBUG_DAY_13
        cout << "Button A: x=" << m_buttons[0].x << " y=" << m_buttons[0].y << endl;
        cout << "Button B: x=" << m_buttons[1].x << " y=" << m_buttons[1].y << endl;
        cout << "Prize: x=" << m_prize_x << " y=" << m_prize_y << endl;
#endif
    }
    
}

AocDay13::AocDay13():AocDay(13)
{
}

AocDay13::~AocDay13()
{
}

vector<string> AocDay13::read_input(string filename)
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

vector<Machine> AocDay13::create_machines(vector<string> input)
{
    vector<Machine> machines;
    for (int i=0; i<input.size(); i+=4)
    {
        cout << "Machine " << i/4 << ":" << endl;
        Machine machine;
        machine.load_machine(input[i], input[i+1], input[i+2]);
        machines.push_back(machine);
    }
    return machines;
}

string AocDay13::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    
    vector<Machine> machines = create_machines(data);
    
    out << "Day 13 - Part 1 not implemented";
    return out.str();
}

string AocDay13::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);

    ostringstream out;
    out << "Day 13 - Part 2 not implemented";
    return out.str();
}
