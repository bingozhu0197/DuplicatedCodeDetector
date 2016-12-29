/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"

class IFileReader
{
public:
    virtual ~IFileReader() = default;
    virtual Lines getLines(const FilePath & p_filePath) = 0;
};

