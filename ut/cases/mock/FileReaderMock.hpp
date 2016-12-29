/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"
#include "IFileReader.hpp"
#include "gmock/gmock.h"

class FileReaderMock : public IFileReader
{
public:
    MOCK_METHOD1(getLines, Lines(const FilePath &));
};

