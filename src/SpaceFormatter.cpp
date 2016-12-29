/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <string>
#include <algorithm>
#include <cctype>
#include "SpaceFormatter.hpp"


Lines SpaceFormatter::removeSpace(Lines && p_lines)
{
    for (auto & l_line : p_lines)
    {
        auto & l_lineText = l_line.second;
        l_lineText.erase(remove_if(l_lineText.begin(), l_lineText.end(), ::isspace), l_lineText.end());
    }
    return p_lines;
}

Lines SpaceFormatter::getLines(const FilePath & p_filePath)
{
    return removeSpace(m_fileReader->getLines(p_filePath)); 
}

