/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <string>
#include <vector>
#include <map>
#include <sstream> 

#include "IDuplicatedCodeBlocks.hpp"

using Key = pair<FilePath, FilePath>;

class DuplicatedCodeBlocks : public IDuplicatedCodeBlocks
{
public:
    DuplicatedCodeBlocks();

    void insert(const DuplicatedCodeBlock & p_duplicatedCodeBlock) override;
    void dumpDuplicatedCodeLines();
    void dumpDuplicatedCodeInfo(const string & p_fileName);

private:

    void printDupplicateedCodeBlockInfo(
        stringstream & p_output, 
        const DuplicatedCodeBlock & p_duplicatedCodeBlock);

    unsigned int m_totalDuplicateLines;
    map<Key, vector<DuplicatedCodeBlock>> m_duplicates;
};

