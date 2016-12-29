/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <memory>
#include <algorithm>
#include "Common.hpp"
#include "IDuplicatedCodeBlocks.hpp"
#include "DuplicatedCodeBlocksBuilder.hpp"

DuplicatedCodeBlocksBuilder::DuplicatedCodeBlocksBuilder(
    const FilePath & p_filePath,
    const shared_ptr<IDuplicatedCodeBlocks> & p_duplicatedCodeBlocks, 
    unsigned int p_blockLeastCodeLines)
    : m_filePath(p_filePath),
      m_duplicatedCodeBlocks(p_duplicatedCodeBlocks),
      m_blockLeastCodeLines(p_blockLeastCodeLines),
      m_buildingBlocks()
{
}

DuplicatedCodeBlocksBuilder::~DuplicatedCodeBlocksBuilder()
{
    pushAllBuildingBlocks();
}

void DuplicatedCodeBlocksBuilder::pushToDuplicatedCodeBlocks(const BuildingBlock & p_duplicatedCodeBlock)
{ 
    if (p_duplicatedCodeBlock.getCodeLineCount() < m_blockLeastCodeLines)
    {
        return;
    }
    m_duplicatedCodeBlocks->insert(p_duplicatedCodeBlock.getDuplicatedCodeBlock());
}

void DuplicatedCodeBlocksBuilder::clearBuildingBlocks()
{
    m_buildingBlocks.clear();
}

void DuplicatedCodeBlocksBuilder::pushAllBuildingBlocks()
{
    for (const auto & p_buildingBlock : m_buildingBlocks)
    {
        pushToDuplicatedCodeBlocks(p_buildingBlock.second);
    }
    clearBuildingBlocks();
}

void DuplicatedCodeBlocksBuilder::pushBuildingBlocksNotConitnued(const std::vector<CodeLine> & p_duplicatedCodeLines)
{
    for (auto l_buildingBlock = m_buildingBlocks.cbegin(); l_buildingBlock != m_buildingBlocks.cend(); )
    {
        auto l_codeLine = find_if(
            begin(p_duplicatedCodeLines), 
            end(p_duplicatedCodeLines), 
            [&l_buildingBlock](const auto & p_codeLine)
            {
                return l_buildingBlock->first == p_codeLine.getFilePath()
                       && l_buildingBlock->second.getLastCodeLineNumber() + 1 == p_codeLine.getCodeLineNumber();
            });

        if (l_codeLine == end(p_duplicatedCodeLines))
        {
            pushToDuplicatedCodeBlocks(l_buildingBlock->second);
            l_buildingBlock = m_buildingBlocks.erase(l_buildingBlock);
        }
        else
        {
            l_buildingBlock = next(l_buildingBlock);
        }
    }
}

void DuplicatedCodeBlocksBuilder::createNewBuildingBlocks(
    const CodeLine & p_codeLine, 
    const std::vector<CodeLine> & p_duplicatedCodeLines)
{
    if (!p_codeLine.getLineStatus().isNewLine())
    {
        return;
    }
    for (const auto & l_duplicatedCodeLine : p_duplicatedCodeLines)
    {
        if (!l_duplicatedCodeLine.getLineStatus().isNewLine())
        {
            continue;
        }
        m_buildingBlocks.emplace(
            l_duplicatedCodeLine.getFilePath(),
            BuildingBlock(
                l_duplicatedCodeLine.getCodeLineNumber(),
                make_pair(
                    CodeBlock{m_filePath, p_codeLine.getFileLineNumber()},
                    CodeBlock{l_duplicatedCodeLine.getFilePath(), 
                        l_duplicatedCodeLine.getFileLineNumber()}))
        );
    }
}

std::vector<CodeLine> DuplicatedCodeBlocksBuilder::updateBuildingBlocksContinued(
    const CodeLine & p_codeLine, 
    const std::vector<CodeLine> & p_duplicatedCodeLines)
{
    std::vector<CodeLine> l_remainingDuplicatedCodeLine;
    
    for (const auto & l_duplicatedCodeLine : p_duplicatedCodeLines)
    {
        auto l_duplicatingBlock = m_buildingBlocks.equal_range(l_duplicatedCodeLine.getFilePath());
        if (l_duplicatingBlock.first != l_duplicatingBlock.second)
        {
            auto l_codeBlock = find_if(
                l_duplicatingBlock.first, 
                l_duplicatingBlock.second, 
                [&l_duplicatedCodeLine](const auto & p_codeBlock)
                {
                    return p_codeBlock.second.getLastCodeLineNumber() + 1 == l_duplicatedCodeLine.getCodeLineNumber();
                });

            if (l_codeBlock != l_duplicatingBlock.second)
            {
                l_codeBlock->second.updateOwnBlockEndLineNumber(p_codeLine.getFileLineNumber());
                l_codeBlock->second.updatePeerBlockEndLineNumber(l_duplicatedCodeLine.getFileLineNumber());
                l_codeBlock->second.updateLastCodeLineNumber(l_duplicatedCodeLine.getCodeLineNumber());
                l_codeBlock->second.increaseCodeLineCount();
                continue;
            }
        }
        l_remainingDuplicatedCodeLine.push_back(l_duplicatedCodeLine);
    }

    return l_remainingDuplicatedCodeLine;
}

void DuplicatedCodeBlocksBuilder::addCodeLine(const CodeLine & p_codeLine, const std::vector<CodeLine> & p_duplicatedCodeLines)
{
    pushBuildingBlocksNotConitnued(p_duplicatedCodeLines);

    auto l_remainingDuplicatedCodeLine = updateBuildingBlocksContinued(p_codeLine, p_duplicatedCodeLines);
    createNewBuildingBlocks(p_codeLine, l_remainingDuplicatedCodeLine);
}

void DuplicatedCodeBlocksBuilder::finishAddingCodeLine()
{
    pushAllBuildingBlocks();
}

