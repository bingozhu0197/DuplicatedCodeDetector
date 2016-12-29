/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <memory>
#include "IFileReader.hpp"
#include "ILinesDecorator.hpp"

class RemoveEmptyLine : public ILinesDecorator
{
public:
    RemoveEmptyLine(const std::shared_ptr<IFileReader> & p_fileReader)
        : m_fileReader(p_fileReader)
    {}
    
    Lines getLines(const FilePath & p_filePath) override;

private:
    Lines removeEmptyLine(Lines && p_lines);

    std::shared_ptr<IFileReader> m_fileReader;
};

