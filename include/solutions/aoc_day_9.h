#ifndef __AOC_DAY_9__
#define __AOC_DAY_9__

#include "aoc_day.h"

#define DAY9_MAX_BLOCKS 200000

namespace Day9
{
    struct Block
    {
        int file_id;
    };
    
    class DiskMap
    {
        private:
            Block m_disk_map[DAY9_MAX_BLOCKS];
            int m_num_blocks_used;
            int m_next_file_id;
            int m_file_blocks;
        public:
            DiskMap();
            ~DiskMap();
            void load_disk_map(string input);
            void display_disk_map();
            void remap_over_free_blocks();
            long compute_checksum();
    };
}

using namespace Day9;

class AocDay9 : public AocDay
{
    private:
        string read_input(string filename);
    public:
        AocDay9();
        ~AocDay9();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
