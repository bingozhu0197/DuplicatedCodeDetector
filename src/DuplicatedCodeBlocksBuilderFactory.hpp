/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/

#include "IDuplicatedCodeBlocksBuilderFactory.hpp"

class IDuplicatedCodeBlocks;

class DuplicatedCodeBlocksBuilderFactory : public IDuplicatedCodeBlocksBuilderFactory
{
public:
    DuplicatedCodeBlocksBuilderFactory(
        const shared_ptr<IDuplicatedCodeBlocks> & p_duplicatedCodeBlocks,
        unsigned int p_blockLeastCodeLines);
    unique_ptr<IDuplicatedCodeBlocksBuilder> createBuilder(const FilePath & p_filePath) override;
private:
    shared_ptr<IDuplicatedCodeBlocks> m_duplicatedCodeBlocks;
    unsigned int m_blockLeastCodeLines;
};
