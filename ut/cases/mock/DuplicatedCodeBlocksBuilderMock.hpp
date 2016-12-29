/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include "Common.hpp"
#include "IDuplicatedCodeBlocksBuilder.hpp"
#include "gmock/gmock.h"

class DuplicatedCodeBlocksBuilderMock : public IDuplicatedCodeBlocksBuilder
{
public:
    MOCK_METHOD2(addCodeLine, void(const CodeLine &, const std::vector<CodeLine> &));
    MOCK_METHOD0(finishAddingCodeLine, void ());
};

