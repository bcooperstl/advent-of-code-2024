#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

#include "aoc_day_9.h"
#include "file_utils.h"

using namespace std;
using namespace Day9;

#define DAY_9_FREE_SPACE -9999

namespace Day9
{
    DiskMap::DiskMap()
    {
        m_num_blocks_used = 0;
        m_next_file_id=0;
        m_file_blocks=0;
    }
    
    DiskMap::~DiskMap()
    {
    }
    
    void DiskMap::load_disk_map(string input)
    {
        bool loading_file=true;
        
        for (int i=0; i<input.size(); i++)
        {
            int count = input[i]-'0';
            if (loading_file)
            {
#ifdef DEBUG_DAY_9
                cout << "Loading file id " << m_next_file_id << " taking up " << count << " blocks from positions " 
                     << m_num_blocks_used << " to " << m_num_blocks_used + count - 1 << endl;
#endif
                for (int block=m_num_blocks_used; block < m_num_blocks_used + count; block++)
                {
                    m_disk_map[block].file_id=m_next_file_id;
                }
                m_num_blocks_used+=count;
                m_file_blocks+=count;
                m_next_file_id++;
                loading_file=false;
            }
            else
            {
#ifdef DEBUG_DAY_9
                cout << "Loading free space taking up " << count << " blocks from positions " 
                     << m_num_blocks_used << " to " << m_num_blocks_used + count - 1 << endl;
#endif
                for (int block=m_num_blocks_used; block < m_num_blocks_used + count; block++)
                {
                    m_disk_map[block].file_id=DAY_9_FREE_SPACE;
                }
                m_num_blocks_used+=count;
                loading_file=true;
            }
        }
#ifdef DEBUG_DAY_9
        cout << "Loaded " << m_num_blocks_used << " blocks containing " << m_next_file_id << " files using " << m_file_blocks << " blocks." << endl;
#endif
        return;
    }

    void DiskMap::display_disk_map()
    {
        for (int block=0; block<m_num_blocks_used; block++)
        {
            if (block % 16 == 0)
            {
                cout << "Blocks " << setw(6) << block << " - " << setw(6) << block+15 << ": ";
            }
            if (m_disk_map[block].file_id == DAY_9_FREE_SPACE)
            {
                cout << "....";
            }
            else
            {
                cout << setw(4) << m_disk_map[block].file_id;
            }
            cout << " ";
            if (block %16 == 15)
            {
                cout << endl;
            }
        }
        cout << endl;
        return;
    }
       
    void DiskMap::remap_over_free_blocks()
    {
        int file_pos = m_num_blocks_used-1;
        int empty_pos = 0;
        while (file_pos >= m_file_blocks)
        {
            if (m_disk_map[file_pos].file_id != DAY_9_FREE_SPACE)
            {
                while (m_disk_map[empty_pos].file_id != DAY_9_FREE_SPACE)
                {
                    empty_pos++;
                }
#ifdef DEBUG_DAY_9
                cout << "Swapping block " << file_pos 
                     << " with file_id " << m_disk_map[file_pos].file_id
                     << " and empty block " << empty_pos << endl;
#endif
                m_disk_map[empty_pos].file_id = m_disk_map[file_pos].file_id;
                m_disk_map[file_pos].file_id = DAY_9_FREE_SPACE;
                empty_pos++;
#ifdef DEBUG_DAY_9_SWAPS
                display_disk_map();
#endif
            }
            file_pos--;
        }
    }
    
    long DiskMap::compute_checksum()
    {
        long checksum = 0;
        for (int block=0; block<m_file_blocks; block++)
        {
            checksum+=((long)block) * ((long)m_disk_map[block].file_id);
        }
        return checksum;
    }
}

AocDay9::AocDay9():AocDay(9)
{
}

AocDay9::~AocDay9()
{
}

string AocDay9::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> data;
    if (!fileutils.read_as_list_of_strings(filename, data))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return "";
    }
    return data[0];
}

string AocDay9::part1(string filename, vector<string> extra_args)
{
    string data = read_input(filename);
    
    DiskMap diskmap;
    
    diskmap.load_disk_map(data);
#ifdef DEBUG_DAY_9
    cout << "Starting map:" << endl;
    diskmap.display_disk_map();
#endif

    diskmap.remap_over_free_blocks();

#ifdef DEBUG_DAY_9
    cout << "Ending map:" << endl;
    diskmap.display_disk_map();
#endif
    
    ostringstream out;
    out << diskmap.compute_checksum();
    return out.str();
}

string AocDay9::part2(string filename, vector<string> extra_args)
{
    string data = read_input(filename);

    ostringstream out;
    out << "Day 9 - Part 2 not implemented";
    return out.str();
}
