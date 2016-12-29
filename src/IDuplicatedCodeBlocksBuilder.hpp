/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <vector>
#include "Common.hpp"

class IDuplicatedCodeBlocksBuilder
{
public:
    virtual ~IDuplicatedCodeBlocksBuilder() = default;
    virtual void addCodeLine(const CodeLine & p_codeLine, const std::vector<CodeLine> & p_duplicatedCodeLines) = 0;
    virtual void finishAddingCodeLine() = 0;
};

