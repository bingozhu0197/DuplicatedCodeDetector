/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <string>
#include <algorithm>
#include "ClearComments.hpp"

Lines ClearComments::removeComments(Lines && p_lines)
{
    bool l_inCommentsBlock = false;
    for (auto & l_line : p_lines)
    {
        auto & l_lineText = l_line.second;
        auto l_pos = l_lineText.find("//");
        if (l_pos != string::npos)
        {   
            l_lineText.erase(l_pos);
        }

        if (l_lineText.find("/*") != string::npos)
        {
            if (l_lineText.find("*/") == string::npos)
            {
                l_inCommentsBlock = true;
            }
            l_lineText.clear();
        }
        if (l_inCommentsBlock)
        {
            if (l_lineText.find("*/") != string::npos)
            {
                l_inCommentsBlock = false;
            }
            l_lineText.clear();         
        }
    }
    return p_lines;
}

Lines ClearComments::getLines(const FilePath & p_filePath)
{
    return removeComments(m_fileReader->getLines(p_filePath));
}

