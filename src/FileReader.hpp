/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"
#include "IFileReader.hpp"

class FileReader : public IFileReader
{
public:
    Lines getLines(const FilePath & p_filePath) override;
};

