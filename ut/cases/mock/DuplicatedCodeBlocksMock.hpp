/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"
#include "IDuplicatedCodeBlocks.hpp"
#include "gmock/gmock.h"

class DuplicatedCodeBlocksMock : public IDuplicatedCodeBlocks
{
public:
    MOCK_METHOD1(insert, void(const DuplicatedCodeBlock &));
};

