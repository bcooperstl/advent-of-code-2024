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
        m_free_spaces_used=0;
        m_files_used=0;
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
                m_files[m_files_used].starting_block=m_num_blocks_used;
                m_files[m_files_used].num_blocks=count;
                m_files_used++;
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
                m_free_spaces[m_free_spaces_used].starting_block=m_num_blocks_used;
                m_free_spaces[m_free_spaces_used].num_blocks=count;
                m_free_spaces_used++;
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
        cout << "Loaded " << m_free_spaces_used << " free space sections" << endl;
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
    
    void DiskMap::remap_file_based()
    {
        int file_idx = m_files_used-1;
        while (file_idx > 0)
        {
            int free_idx=0;
            
            int target_free_idx=0;
            bool free_location_found=false;
            
            while (m_free_spaces[free_idx].starting_block < m_files[file_idx].starting_block)
            {
                if (m_free_spaces[free_idx].num_blocks >= m_files[file_idx].num_blocks)
                {
                    target_free_idx=free_idx;
                    free_location_found = true;
                    break;
                }
                free_idx++;
            }

            if (free_location_found == true)
            {
#ifdef DEBUG_DAY_9
                cout << "Moving file " << file_idx 
                     << " from blocks " << m_files[file_idx].starting_block
                     << " to " << m_files[file_idx].starting_block + m_files[file_idx].num_blocks - 1
                     << " to empty space at blocks " << m_free_spaces[target_free_idx].starting_block
                     << " to " << m_free_spaces[target_free_idx].starting_block + m_files[file_idx].num_blocks - 1 << endl;
#endif
                for (int i=0; i<m_files[file_idx].num_blocks; i++)
                {
                    m_disk_map[m_free_spaces[target_free_idx].starting_block+i].file_id = file_idx;
                    m_disk_map[m_files[file_idx].starting_block+i].file_id = DAY_9_FREE_SPACE;
                }
                m_files[file_idx].starting_block=m_free_spaces[target_free_idx].starting_block;

#ifdef DEBUG_DAY_9
                cout << "Modified free space of " << m_free_spaces[target_free_idx].num_blocks
                     << " blocks at " << m_free_spaces[target_free_idx].starting_block;
#endif

                m_free_spaces[target_free_idx].starting_block+=m_files[file_idx].num_blocks;
                m_free_spaces[target_free_idx].num_blocks-=m_files[file_idx].num_blocks;

#ifdef DEBUG_DAY_9
                cout << " to be " << m_free_spaces[target_free_idx].num_blocks
                     << " blocks at " << m_free_spaces[target_free_idx].starting_block << endl;
#endif
#ifdef DEBUG_DAY_9_SWAPS
                display_disk_map();
#endif
            }
            else
            {
#ifdef DEBUG_DAY_9
                cout << "No free space to move file " << file_idx << " which is " << m_files[file_idx].num_blocks << " blocks" << endl;
#endif
            }
            
            file_idx--;
        }
    }
    
    long DiskMap::compute_checksum()
    {
        long checksum = 0;
        for (int block=0; block<m_num_blocks_used; block++)
        {
            if (m_disk_map[block].file_id != DAY_9_FREE_SPACE)
            {
                checksum+=((long)block) * ((long)m_disk_map[block].file_id);
            }
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

    DiskMap diskmap;
    
    diskmap.load_disk_map(data);
#ifdef DEBUG_DAY_9
    cout << "Starting map:" << endl;
    diskmap.display_disk_map();
#endif

    diskmap.remap_file_based();

#ifdef DEBUG_DAY_9
    cout << "Ending map:" << endl;
    diskmap.display_disk_map();
#endif
    
    ostringstream out;
    out << diskmap.compute_checksum();
    return out.str();
}
