#ifndef __AOC_DAY_13__
#define __AOC_DAY_13__

#include "aoc_day.h"

namespace Day13
{
    struct Button
    {
        long long int x;
        long long int y;
        long long int cost;
        char label;
    };
    
    class Machine
    {
        private:
            long long int m_prize_x;
            long long int m_prize_y;
            Button m_buttons[2];
        public:
            Machine();
            ~Machine();
            void load_machine(string button_a, string button_b, string prize);
            void load_machine_corrected(string button_a, string button_b, string prize);
            int find_cheapest_cost_to_win();
            long long int find_cheapest_cost_to_win_corrected();
    };
}

using namespace Day13;

class AocDay13 : public AocDay
{
    private:
        vector<string> read_input(string filename);
        vector<Machine> create_machines(vector<string> input);
        vector<Machine> create_machines_corrected(vector<string> input);
    public:
        AocDay13();
        ~AocDay13();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
