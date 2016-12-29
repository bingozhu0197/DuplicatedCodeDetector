/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"
#include "IDuplicatedCodeBlocksBuilderFactory.hpp"
#include "gmock/gmock.h"

class DuplicatedCodeBlocksBuilderFactoryMock : public IDuplicatedCodeBlocksBuilderFactory
{
public:
    unique_ptr<IDuplicatedCodeBlocksBuilder> createBuilder(const FilePath & p_filePath) 
    {
        return std::unique_ptr<IDuplicatedCodeBlocksBuilder>(createBuilderProxy(p_filePath));
    }
    MOCK_METHOD1(createBuilderProxy, IDuplicatedCodeBlocksBuilder * (const FilePath &));
};

