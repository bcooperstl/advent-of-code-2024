#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>

#include "aoc_day_13.h"
#include "file_utils.h"

#define BUTTON_A_COST 3
#define BUTTON_B_COST 1

#define CORRECTION 10000000000000ll // long long


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
    
    void Machine::load_machine_corrected(string button_a, string button_b, string prize)
    {
        load_machine(button_a, button_b, prize);
        m_prize_x+=CORRECTION;
        m_prize_y+=CORRECTION;
#ifdef DEBUG_DAY_13
        cout << "Corrected Prize: x=" << m_prize_x << " y=" << m_prize_y << endl;
#endif
    }
    
    int Machine::find_cheapest_cost_to_win()
    {
        bool solution_found = false;
        int best_cost = INT_MAX;
        
#ifdef DEBUG_DAY_13
        cout << "Searching for solution to prize x=" << m_prize_x << " y=" << m_prize_y << endl;
#endif
        for (int a_presses=100; a_presses>=0; a_presses--)
        {
            int x = m_buttons[0].x*a_presses;
            int y = m_buttons[0].y*a_presses;
            
#ifdef DEBUG_DAY_13
            cout << " Pressing a " << a_presses << " times" << endl;
            cout << "  x=" << x << " y=" << y << endl;
#endif
            
            if ((x > m_prize_x) || (y > m_prize_y))
            {
#ifdef DEBUG_DAY_13
                cout << "  beyond range of prize" << endl;
#endif
                continue;
            }
            int x_to_go=m_prize_x-x;
            int y_to_go=m_prize_y-y;
            if ((x_to_go%m_buttons[1].x != 0) || (y_to_go%m_buttons[1].y != 0))
            {
#ifdef DEBUG_DAY_13
                cout << "  not an even multiple of b buttons to get to prize" << endl;
#endif
                continue;
            }
            int b_presses_x = x_to_go/m_buttons[1].x;
            int b_presses_y = y_to_go/m_buttons[1].y;
            if (b_presses_x != b_presses_y)
            {
#ifdef DEBUG_DAY_13
                cout << "   different values for b button presses to get to prize" << endl;
#endif
                continue;
            }
            
            if (b_presses_x > 100)
            {
#ifdef DEBUG_DAY_13
                cout << "   too many b presses are needed to get to prize" << endl;
#endif
                continue;
            }
            
            int cost = ((m_buttons[0].cost * a_presses) + (m_buttons[1].cost * b_presses_x));
#ifdef DEBUG_DAY_13
            cout << "  MATCHING COMBO FOUND WITH " << a_presses << " presses of a and " << b_presses_x << " presses of b costing " << cost << endl;
#endif
            if (cost < best_cost)
            {
                solution_found=true;
                best_cost = cost;
#ifdef DEBUG_DAY_13
                cout << "   NEW BEST COST FOUND!!" << endl;
#endif
            }
            else
            {
#ifdef DEBUG_DAY_13
                cout << "   NOT THE BEST COST" << endl;
#endif
            }
        }
        return (solution_found ? best_cost : 0);
    }
    
    long long int Machine::find_cheapest_cost_to_win_corrected()
    {
#ifdef DEBUG_DAY_13
        cout << "Searching for solution to prize x=" << m_prize_x << " y=" << m_prize_y << endl;
#endif
        long long int presses_a = (((m_prize_x * m_buttons[1].y) - (m_prize_y * m_buttons[1].x))/((m_buttons[0].x*m_buttons[1].y)-(m_buttons[0].y*m_buttons[1].x)));
        long long int presses_b = ((m_prize_y - (presses_a*m_buttons[0].y))/m_buttons[1].y);
        
        long long int calc_x = presses_a * m_buttons[0].x + presses_b * m_buttons[1].x;
        long long int calc_y = presses_a * m_buttons[0].y + presses_b * m_buttons[1].y;
        
        cout << "Test solution is " << presses_a << " presses of a and " << presses_b << " presses of b" << " resulting in x=" << calc_x << " and y=" << calc_y << endl;
        
        if (calc_x == m_prize_x && calc_y == m_prize_y)
        {
            long long int cost = ((m_buttons[0].cost * presses_a) + (m_buttons[1].cost * presses_b));
            cout << "MATCHING answer found. Cost is " << cost << endl;
            return cost;
        }
        cout << "Match not found" << endl;
        return 0;
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

vector<Machine> AocDay13::create_machines_corrected(vector<string> input)
{
    vector<Machine> machines;
    for (int i=0; i<input.size(); i+=4)
    {
        cout << "Machine " << i/4 << ":" << endl;
        Machine machine;
        machine.load_machine_corrected(input[i], input[i+1], input[i+2]);
        machines.push_back(machine);
    }
    return machines;
}

string AocDay13::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    
    vector<Machine> machines = create_machines(data);
    
    int sum_of_best_costs = 0;
    
    for (int i=0; i<machines.size(); i++)
    {
        sum_of_best_costs+=machines[i].find_cheapest_cost_to_win();
    }
    
    out << sum_of_best_costs;
    return out.str();
}

string AocDay13::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    ostringstream out;
    
    vector<Machine> machines = create_machines_corrected(data);
    
    long long int sum_of_best_costs = 0;
    
    for (int i=0; i<machines.size(); i++)
    {
        sum_of_best_costs+=machines[i].find_cheapest_cost_to_win_corrected();
    }
    
    out << sum_of_best_costs;
    return out.str();
}
