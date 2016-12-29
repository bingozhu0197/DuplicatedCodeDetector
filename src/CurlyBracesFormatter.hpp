/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "ILinesDecorator.hpp"

class CurlyBracesFormatter : public ILinesDecorator
{
public:
    CurlyBracesFormatter(const std::shared_ptr<IFileReader> & p_fileReader)
        : m_fileReader(p_fileReader)
    {}
    
    Lines getLines(const FilePath & p_filePath) override;

private:
    size_t getSplitPosition(const string & p_lineText);
    Lines splitLineAtCurlyBrace(Lines && p_code);
    std::shared_ptr<IFileReader> m_fileReader;
};

