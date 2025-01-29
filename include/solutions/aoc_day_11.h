#ifndef __AOC_DAY_11__
#define __AOC_DAY_11__

#include <map>

#include "aoc_day.h"

#define DAY_11_NUM_BLINKS 25

using namespace std;
namespace Day11
{
    struct StoneQuantity
    {
        long long int quantity;
        long long int value;
    };
    
    class StoneProcessor
    {
        private:
            map<long long int, StoneQuantity> m_single_digit_dictionary[10][DAY_11_NUM_BLINKS+1]; // for values 0-9
            void merge_values_to_results(map<long long int, StoneQuantity> & results, map<long long int, StoneQuantity> & additions, long long int additions_quantity);
        public:
            StoneProcessor();
            ~StoneProcessor();
            vector<StoneQuantity> perform_blink(long long int value);
            void build_single_digit_dictionary();
            map<long long int, StoneQuantity> process_input(vector<long> input_values);
    };
}

class AocDay11 : public AocDay
{
    private:
        vector<long> read_input(string filename);
    public:
        AocDay11();
        ~AocDay11();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
