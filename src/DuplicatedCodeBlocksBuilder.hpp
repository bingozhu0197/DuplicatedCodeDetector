/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <memory>
#include <map>
#include "Common.hpp"
#include "CodeLine.hpp"
#include "CodeBlock.hpp"
#include "IDuplicatedCodeBlocksBuilder.hpp"

class IDuplicatedCodeBlocks;
class BuildingBlock final
{
public:
    BuildingBlock(LineNumber p_codeLineNumber, const DuplicatedCodeBlock & p_duplicatedCodeBlock)
        : m_duplicatedCodeBlock(p_duplicatedCodeBlock),
          m_lastCodeLineNumber(p_codeLineNumber)
    {}
    
    unsigned int getCodeLineCount() const
    {
        return m_lineCount;
    }
    void increaseCodeLineCount()
    {
        m_lineCount++;
    }

    void updateOwnBlockEndLineNumber(LineNumber p_newEndLineNum)
    {
        m_duplicatedCodeBlock.first.updateEndLineNumber(p_newEndLineNum);
    }
    
    void updatePeerBlockEndLineNumber(LineNumber p_newEndLineNum)
    {
        m_duplicatedCodeBlock.second.updateEndLineNumber(p_newEndLineNum);
    }

    LineNumber getLastCodeLineNumber() const
    {
        return m_lastCodeLineNumber;
    }
    
    void updateLastCodeLineNumber(LineNumber p_codeLineNum)
    {
        m_lastCodeLineNumber = p_codeLineNum;
    }
        
    DuplicatedCodeBlock getDuplicatedCodeBlock() const
    {
        return m_duplicatedCodeBlock;
    }

private:
    unsigned int m_lineCount = 1;
    DuplicatedCodeBlock m_duplicatedCodeBlock;
    LineNumber m_lastCodeLineNumber;
};


class DuplicatedCodeBlocksBuilder final : public IDuplicatedCodeBlocksBuilder 
{
public:
    DuplicatedCodeBlocksBuilder(
        const FilePath & p_filePath,
        const shared_ptr<IDuplicatedCodeBlocks> & p_duplicatedCodeBlocks, 
        unsigned int p_blockLeastCodeLines);
    
    ~DuplicatedCodeBlocksBuilder();
    
    void addCodeLine(const CodeLine & p_codeLine, const vector<CodeLine> & p_duplicatedCodeLines) override;
    void finishAddingCodeLine() override;

private:
    vector<CodeLine> updateBuildingBlocksContinued(
        const CodeLine & p_codeLine, 
        const vector<CodeLine> & p_duplicatedCodeLines);
    
    void createNewBuildingBlocks(
        const CodeLine & p_codeLine, 
        const vector<CodeLine> & p_duplicatedCodeLines);
    
    void pushBuildingBlocksNotConitnued(
        const vector<CodeLine> & p_duplicatedCodeLines);
    
    void pushAllBuildingBlocks();
    void clearBuildingBlocks();
    void pushToDuplicatedCodeBlocks(const BuildingBlock & p_duplicatedCodeBlock);

    FilePath m_filePath;
    shared_ptr<IDuplicatedCodeBlocks> m_duplicatedCodeBlocks;
    unsigned int m_blockLeastCodeLines;
    multimap<FilePath, BuildingBlock> m_buildingBlocks;
};


