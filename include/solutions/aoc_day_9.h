#ifndef __AOC_DAY_9__
#define __AOC_DAY_9__

#include "aoc_day.h"

#define DAY9_MAX_BLOCKS 200000
#define DAY9_MAX_FREE_SPACES 10000
#define DAY9_MAX_FILES 10000

namespace Day9
{
    struct Block
    {
        int file_id;
    };
    
    struct FreeSpace
    {
        int starting_block;
        int num_blocks;
    };
    
    struct File
    {
        int starting_block;
        int num_blocks;
    };
    
    class DiskMap
    {
        private:
            Block m_disk_map[DAY9_MAX_BLOCKS];
            FreeSpace m_free_spaces[DAY9_MAX_FREE_SPACES];
            File m_files[DAY9_MAX_FREE_SPACES];
            int m_num_blocks_used;
            int m_free_spaces_used;
            int m_files_used;
            int m_next_file_id;
            int m_file_blocks;
        public:
            DiskMap();
            ~DiskMap();
            void load_disk_map(string input);
            void display_disk_map();
            void remap_over_free_blocks();
            void remap_file_based();
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
