/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <algorithm>
#include <cctype>
#include "CurlyBracesFormatter.hpp"

size_t CurlyBracesFormatter::getSplitPosition(const string & p_lineText)
{
    size_t l_splitPosition = 0;

    auto l_curlyBracePos = p_lineText.find_first_of("{}");
    if (l_curlyBracePos == string::npos)
    {
        return l_splitPosition;
    }

    if (l_curlyBracePos != 0
        && !all_of(begin(p_lineText),  begin(p_lineText) + l_curlyBracePos, ::isspace))
    {
        l_splitPosition = l_curlyBracePos;
    }
    else if (l_curlyBracePos != p_lineText.length() - 1
             && !all_of(begin(p_lineText) + l_curlyBracePos + 1,
                        end(p_lineText),
                        ::isspace))
    {
        l_splitPosition = l_curlyBracePos + 1;
    }
    return l_splitPosition;
}

Lines CurlyBracesFormatter::splitLineAtCurlyBrace(Lines && p_lines)
{
    for (auto l_line = begin(p_lines); l_line != end(p_lines); l_line = next(l_line))
    {
        auto l_splitPosition = getSplitPosition(l_line->second);
        if (l_splitPosition == 0)
        {
            continue;
        }

        auto l_newLine = l_line->second.substr(l_splitPosition);
        l_line->second.erase(l_splitPosition);
        if (!l_newLine.empty())
        {
            p_lines.emplace(next(l_line), l_line->first, move(l_newLine));
        }
    }
    return p_lines;
}

Lines CurlyBracesFormatter::eraseCurlyBraces(Lines && p_lines)
{
    for (auto & l_line : p_lines)
    {
        auto & l_lineText = l_line.second;
        l_lineText.erase(remove_if(l_lineText.begin(), l_lineText.end(), [](char p_char){ return p_char == '{' || p_char == '}';}), l_lineText.end());
    }
    return p_lines;
}

Lines CurlyBracesFormatter::getLines(const FilePath & p_filePath)
{
    return eraseCurlyBraces(m_fileReader->getLines(p_filePath));
}
