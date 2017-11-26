/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <algorithm>
#include <cctype>
#include "RemoveEmptyLine.hpp"

Lines RemoveEmptyLine::removeEmptyLine(Lines && p_lines)
{
    p_lines.erase(remove_if(begin(p_lines), end(p_lines), [](auto & p_line){ return p_line.second.empty();}),
                  end(p_lines));
    return p_lines;
}

Lines RemoveEmptyLine::getLines(const FilePath & p_filePath)
{
    return removeEmptyLine(m_fileReader->getLines(p_filePath));
}
