/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <memory>
#include "Common.hpp"
#include "IDuplicatedCodeBlocks.hpp"
#include "DuplicatedCodeBlocksBuilder.hpp"
#include "DuplicatedCodeBlocksBuilderFactory.hpp"

DuplicatedCodeBlocksBuilderFactory::DuplicatedCodeBlocksBuilderFactory(
    const shared_ptr<IDuplicatedCodeBlocks> & p_duplicatedCodeBlocks,
    unsigned int p_blockLeastCodeLines)
    : m_duplicatedCodeBlocks(p_duplicatedCodeBlocks),
      m_blockLeastCodeLines(p_blockLeastCodeLines)
{}

unique_ptr<IDuplicatedCodeBlocksBuilder> 
    DuplicatedCodeBlocksBuilderFactory::createBuilder(const FilePath & p_filePath)
{

    return make_unique<DuplicatedCodeBlocksBuilder>(p_filePath, m_duplicatedCodeBlocks, m_blockLeastCodeLines);
}

