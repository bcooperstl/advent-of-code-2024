#ifndef __AOC_DAY_13__
#define __AOC_DAY_13__

#include "aoc_day.h"

namespace Day13
{
    struct Button
    {
        int x;
        int y;
        int cost;
        char label;
    };
    
    class Machine
    {
        private:
            int m_prize_x;
            int m_prize_y;
            Button m_buttons[2];
        public:
            Machine();
            ~Machine();
            void load_machine(string button_a, string button_b, string prize);
    };
}

using namespace Day13;

class AocDay13 : public AocDay
{
    private:
        vector<string> read_input(string filename);
        vector<Machine> create_machines(vector<string> input);
    public:
        AocDay13();
        ~AocDay13();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
