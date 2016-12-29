/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <string>
#include "Common.hpp"
#include "CodeLine.hpp"

class CodeBlock
{
public:
    CodeBlock(
        const FilePath & p_filePath,
        LineNumber p_beginLineNumber)
        : m_filePath(p_filePath),
          m_beginLineNumber(p_beginLineNumber),
          m_endLineNumber(p_beginLineNumber)
    {}
    
    void updateEndLineNumber(LineNumber p_lineNumber)
    {
        m_endLineNumber = p_lineNumber;
    }
    
    LineNumber getEndLineNumber() const
    {
        return m_endLineNumber;
    }
    
    LineNumber getBeginLineNumber() const
    {
        return m_beginLineNumber;
    }

    size_t getLines() const
    {
        return m_endLineNumber - m_beginLineNumber + 1;
    }

    FilePath getFilePath() const
    {
        return m_filePath;
    }
    
    bool operator == (const CodeBlock & rhs) const
    {
        return m_filePath == rhs.m_filePath
            && m_beginLineNumber == rhs.m_beginLineNumber
            && m_endLineNumber == rhs.m_endLineNumber;        
    }

private:
    FilePath m_filePath;
    LineNumber m_beginLineNumber;
    LineNumber m_endLineNumber;
};

using DuplicatedCodeBlock = std::pair<CodeBlock, CodeBlock>;

inline size_t getDuplicatedCodeBlockLines(const DuplicatedCodeBlock & p_duplicatedCodeBlock)
{
    return p_duplicatedCodeBlock.first.getLines() + p_duplicatedCodeBlock.second.getLines();
}

