/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include "Common.hpp"

class IDuplicatedCodeBlocksBuilder;
class IDuplicatedCodeBlocksBuilderFactory
{
public:
    virtual ~IDuplicatedCodeBlocksBuilderFactory() = default;
    virtual unique_ptr<IDuplicatedCodeBlocksBuilder> createBuilder(const FilePath & p_filePath) = 0;
};

