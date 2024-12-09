#ifndef __AOC_DAY_5__
#define __AOC_DAY_5__

#include "aoc_day.h"

#define DAY_5_MAX_PAGE 100

namespace Day5
{
    enum Ordering
    {
        first_before = -1,
        undefined = 0,
        first_after = 1
    };
    
    class Rules
    {
        private:
            Ordering m_ordering[DAY_5_MAX_PAGE][DAY_5_MAX_PAGE];
        public:
            Rules();
            ~Rules();
            Ordering get_ordering(int first_page, int second_page);
            void add_ordering(int first_page, int second_page);
    };
    
    class Update
    {
        private:
            vector<long> m_page_list;
        public:
            Update(vector<long> page_list);
            ~Update();
            bool are_pages_in_order(Rules * rules);
            long get_middle_page();
    };
}

using namespace Day5;

class AocDay5 : public AocDay
{
    private:
        void parse_input(string filename, Rules & rules, vector<Update> & updates);
    public:
        AocDay5();
        ~AocDay5();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
