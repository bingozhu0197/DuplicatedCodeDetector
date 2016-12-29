/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "ILinesDecorator.hpp"

class ClearComments : public ILinesDecorator
{
public:
    ClearComments(const std::shared_ptr<IFileReader> & p_fileReader)
        : m_fileReader(p_fileReader)
    {}
    
    Lines getLines(const FilePath & p_filePath) override;

private:
    Lines removeComments(Lines && p_code);
    std::shared_ptr<IFileReader> m_fileReader;
};

