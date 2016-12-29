/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include "Common.hpp"
#include "Json.hpp"

const string SPACE_PER_LEVEL = "    ";
void Json::dump(stringstream & p_data, const string & p_fileName)
{
    ofstream l_output(p_fileName);
    string l_line;
    unsigned int l_level = 0;
    while(getline(p_data, l_line))
    {
        if (l_line.front() == '}'
            || l_line.front() == ']')
        {
            --l_level;
        }

        l_output << indent(l_level) << l_line << endl;
        if (l_line.find_first_of("{[") != string::npos)
        {
            ++l_level;
        }
    }
}

string Json::indent(unsigned int l_level)
{
    string l_space;
    while (l_level != 0)
    {
         l_space += SPACE_PER_LEVEL;
         --l_level;
    }
    return l_space;
}

