#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_14.h"
#include "file_utils.h"

#define DEFAULT_WIDTH 101
#define DEFAULT_HEIGHT 103

#define PART_1_MOVES 100

using namespace std;
using namespace Day14;

namespace Day14
{
    World::World(int width, int height)
    {
        m_width = width;
        m_height = height;
    }
    
    World::~World()
    {
    }
    
    /*
    line format is p=0,4 v=3,-3
    split on equals, commas, spaces
    pos_x at position 1
    pos_y at position 2
    vel_x at position 4
    vel_y at position 5
    */    
    void World::load_robots(vector<vector<string>> data)
    {
        for (int i=0; i<data.size(); i++)
        {
            Robot robot;
            robot.pos_x = strtol(data[i][1].c_str(), NULL, 10);
            robot.pos_y = strtol(data[i][2].c_str(), NULL, 10);
            robot.vel_x = strtol(data[i][4].c_str(), NULL, 10);
            robot.vel_y = strtol(data[i][5].c_str(), NULL, 10);
            m_robots.push_back(robot);
#ifdef DEBUG_DAY_14
            cout << "Robot " << i << " starts at " << robot.pos_x << "," << robot.pos_y 
                 << " and has velocities " << robot.vel_x << "," << robot.vel_y << endl;
#endif
        }
        return;
    }
    
    void World::move_robots(int num_moves)
    {
        for (int i=0; i<m_robots.size(); i++)
        {
#ifdef DEBUG_DAY_14
            cout << "Moving robot from " << m_robots[i].pos_x << "," << m_robots[i].pos_y 
                 << " velocity " << m_robots[i].vel_x << "," << m_robots[i].vel_y;
#endif
            int vel_x = m_robots[i].vel_x;
            int vel_y = m_robots[i].vel_y;
            if (vel_x < 0)
            {
                vel_x+=m_width;
            }
            if (vel_y < 0)
            {
                vel_y+=m_height;
            }
            
            m_robots[i].pos_x = (m_robots[i].pos_x + (num_moves * vel_x)) % m_width;
            m_robots[i].pos_y = (m_robots[i].pos_y + (num_moves * vel_y)) % m_height;
#ifdef DEBUG_DAY_14
            cout << " results in " << m_robots[i].pos_x << "," << m_robots[i].pos_y;
#endif
        }
        return;
    }
    
    int World::get_safety_factor()
    {
        int quad_count[4] = {0,0,0,0};
        int mid_width_val = m_width/2 + 1;
        int mid_height_val = m_height/2 + 1;

#ifdef DEBUG_DAY_14
        cout << "Width is " << m_width << ". Width halves go from 0 to " << mid_width_val-1 << " and " << mid_width_val+1 << " to " << m_width-1 << endl;
        cout << "Height is " << m_height << ". Height halves go from 0 to " << mid_height_val-1 << " and " << mid_height_val+1 << " to " << m_height-1 << endl;
#endif        

        for (int i=0; i<m_robots.size(); i++)
        {
#ifdef DEBUG_DAY_14
            cout << "Robot at " << m_robots[i].pos_x << "," << m_robots[i].pos_y << " ";
#endif
            if ((m_robots[i].pos_x >= 0) && (m_robots[i].pos_x <= (mid_width_val-1)))
            {
                if ((m_robots[i].pos_y >= 0) && (m_robots[i].pos_y <= (mid_height_val-1)))
                {
#ifdef DEBUG_DAY_14
                    cout << "is in quad 0" << endl;
#endif
                    quad_count[0]++;
                }
                else if ((m_robots[i].pos_y >= (mid_height_val+1)) && (m_robots[i].pos_y <= (m_height-1)))
                {
#ifdef DEBUG_DAY_14
                    cout << "is in quad 1" << endl;
#endif
                    quad_count[1]++;
                }
                else
                {
#ifdef DEBUG_DAY_14
                    cout << "is on the height dividing line" << endl;
#endif
                }
            }
            else if ((m_robots[i].pos_x >= (mid_width_val+1)) && (m_robots[i].pos_x <= (m_width-1)))
            {
                if ((m_robots[i].pos_y >= 0) && (m_robots[i].pos_y <= (mid_height_val-1)))
                {
#ifdef DEBUG_DAY_14
                    cout << "is in quad 2" << endl;
#endif
                    quad_count[2]++;
                }
                else if ((m_robots[i].pos_y >= (mid_height_val+1)) && (m_robots[i].pos_y <= (m_height-1)))
                {
#ifdef DEBUG_DAY_14
                    cout << "is in quad 3" << endl;
#endif
                    quad_count[3]++;
                }
                else
                {
#ifdef DEBUG_DAY_14
                    cout << "is on the height dividing line" << endl;
#endif
                }
            }
            else
            {
#ifdef DEBUG_DAY_14
                cout << "is on the width dividing line" << endl;
#endif
            }
        }
        return quad_count[0] * quad_count[1] * quad_count[2] * quad_count[3];
    }   
}


AocDay14::AocDay14():AocDay(14)
{
}

AocDay14::~AocDay14()
{
}

vector<vector<string>> AocDay14::read_input(string filename)
{
    FileUtils fileutils;
    vector<vector<string>> data;
    char delimeters[4] = "=, ";
    if (!fileutils.read_as_list_of_split_strings(filename, data, delimeters, 3, '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    return data;
}

string AocDay14::part1(string filename, vector<string> extra_args)
{
    vector<vector<string>> data = read_input(filename);
    
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    
    // extra args, if given, are width and height in that order
    if (extra_args.size() == 2)
    {
        width = strtol(extra_args[0].c_str(), NULL, 10);
        height = strtol(extra_args[1].c_str(), NULL, 10);
    }
    
    World world(width, height);
    
    world.load_robots(data);
    world.move_robots(PART_1_MOVES);
    
    ostringstream out;
    out << world.get_safety_factor();
    return out.str();
}

string AocDay14::part2(string filename, vector<string> extra_args)
{
    vector<vector<string>> data = read_input(filename);

    ostringstream out;
    out << "Day 14 - Part 2 not implemented";
    return out.str();
}
