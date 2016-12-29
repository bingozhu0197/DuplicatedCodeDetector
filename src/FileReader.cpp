/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <iostream>
#include <fstream>
#include "FileReader.hpp"

Lines FileReader::getLines(const FilePath & p_filePath)
{
    Lines l_file;
    
    ifstream l_fileStream(*p_filePath);
    if (!l_fileStream)
    {
        cout << "open " << p_filePath << " failed" << endl;
        return l_file;
    }

    string l_line;
    LineNumber l_lineNumber = 1;
    while (getline(l_fileStream, l_line))
    {
        if (!l_line.empty())
        {
            l_file.emplace_back(l_lineNumber, move(l_line));
        }
        ++l_lineNumber;
    }
    return l_file;    
}

