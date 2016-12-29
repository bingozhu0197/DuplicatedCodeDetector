/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"
#include "CodeBlock.hpp"

class IDuplicatedCodeBlocks
{
public:
    virtual ~IDuplicatedCodeBlocks() = default;
    virtual void insert(const DuplicatedCodeBlock & p_duplicatedCodeBlock) = 0;
};

