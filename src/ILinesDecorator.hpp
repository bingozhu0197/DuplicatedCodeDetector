/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <vector>
#include <string>
#include "IFileReader.hpp"

class ILinesDecorator : public IFileReader
{
public:
    Lines getLines(const FilePath & p_filePath) override = 0;
};

