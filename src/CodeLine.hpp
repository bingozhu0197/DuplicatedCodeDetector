/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"

//One file line may split into multi code line.
class CodeLineStatus
{
public:
    CodeLineStatus(bool p_isNewLine)
        : m_isNewLine(p_isNewLine)
    {}
    
    bool isNewLine() const
    {
        return m_isNewLine;
    }
    bool operator == (const CodeLineStatus & rhs) const
    {
        return m_isNewLine == rhs.m_isNewLine;
    }
private:
    bool m_isNewLine;
};

class CodeLine
{
public:
    CodeLine(
        const FilePath & p_filePath,
        CodeLineStatus p_codeLineStatus,
        LineNumber p_fileLineNumber,
        LineNumber p_codeLineNumber)
        : m_filePath(p_filePath),
          m_codeLineStatus(p_codeLineStatus),
          m_fileLineNumber(p_fileLineNumber),
          m_codeLineNumber(p_codeLineNumber)
    {}

    FilePath getFilePath() const
    {
        return m_filePath;
    }

    LineNumber getCodeLineNumber() const
    {
        return m_codeLineNumber;
    }
    
    LineNumber getFileLineNumber() const
    {
        return m_fileLineNumber;
    }

    CodeLineStatus getLineStatus() const
    {
        return m_codeLineStatus;
    }
    
    bool operator == (const CodeLine & rhs) const
    {
        return m_filePath == rhs.m_filePath
            && m_codeLineStatus == rhs.m_codeLineStatus
            && m_fileLineNumber == rhs.m_fileLineNumber
            && m_codeLineNumber == rhs.m_codeLineNumber;
    }
public:
    FilePath m_filePath;
    CodeLineStatus m_codeLineStatus;
    LineNumber m_fileLineNumber;
    LineNumber m_codeLineNumber;
};

