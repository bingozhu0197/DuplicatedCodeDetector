/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <fstream>
#include "DuplicatedCodeBlocksBuilder.hpp"
#include "DuplicatedCodeBlocksMock.hpp"
#include "TestCommon.hpp"
#include "gtest/gtest.h"

namespace testing
{

const size_t LEAST_CODE_BLOCK_LINES = 5;

class DuplicatedCodeBlocksBuilderTestSuite: public Test
{
public:
    DuplicatedCodeBlocksBuilderTestSuite()
        : m_code_block_1(FILE_NAME_1, BLOCK_1_START_LINE),
          m_code_block_2(FILE_NAME_2, BLOCK_2_START_LINE),
          m_code_block_3(FILE_NAME_3, BLOCK_3_START_LINE),
          m_duplicatedCodeBlocksMock(make_shared<DuplicatedCodeBlocksMock>()),
          m_sut(FILE_NAME_1, m_duplicatedCodeBlocksMock, LEAST_CODE_BLOCK_LINES)
    {
        m_code_block_1.updateEndLineNumber(BLOCK_1_END_LINE);
        m_code_block_2.updateEndLineNumber(BLOCK_2_END_LINE);
        m_code_block_3.updateEndLineNumber(BLOCK_3_END_LINE);
    }

protected:
    CodeBlock m_code_block_1;
    CodeBlock m_code_block_2;
    CodeBlock m_code_block_3;
    shared_ptr<DuplicatedCodeBlocksMock> m_duplicatedCodeBlocksMock;
    DuplicatedCodeBlocksBuilder m_sut;
};

TEST_F(DuplicatedCodeBlocksBuilderTestSuite, buildingBlockNotContinued)
{
    LineNumber l_fileLineNumber = BLOCK_1_START_LINE;
    LineNumber l_duplicatedFileLineNumber = BLOCK_2_START_LINE;

    EXPECT_CALL(*m_duplicatedCodeBlocksMock, insert(DuplicatedCodeBlock{m_code_block_1, m_code_block_2})).WillOnce(Return());
    
    CodeLine l_line(FILE_NAME_1, CodeLineStatus(true), l_fileLineNumber, l_fileLineNumber);
    vector<CodeLine> l_duplicatedCodeLines{
        CodeLine(FILE_NAME_2, CodeLineStatus(true), l_duplicatedFileLineNumber, l_duplicatedFileLineNumber)};
    m_sut.addCodeLine(l_line, l_duplicatedCodeLines);

    for (++l_duplicatedFileLineNumber, ++l_fileLineNumber;l_duplicatedFileLineNumber <= BLOCK_2_END_LINE; ++l_duplicatedFileLineNumber, ++l_fileLineNumber)
    {
        l_line = CodeLine(FILE_NAME_1, CodeLineStatus(false), l_fileLineNumber, l_fileLineNumber);
        l_duplicatedCodeLines = vector<CodeLine>{
            CodeLine(FILE_NAME_2, CodeLineStatus(false), l_duplicatedFileLineNumber, l_duplicatedFileLineNumber)};    
        m_sut.addCodeLine(l_line, l_duplicatedCodeLines);
    }
    l_line = CodeLine(FILE_NAME_1, CodeLineStatus(false), l_fileLineNumber, l_fileLineNumber);
    m_sut.addCodeLine(l_line, {});
}

TEST_F(DuplicatedCodeBlocksBuilderTestSuite, finishBuilding)
{
    LineNumber l_fileLineNumber = BLOCK_1_START_LINE;
    LineNumber l_duplicatedFileLineNumber2 = BLOCK_2_START_LINE;
    LineNumber l_duplicatedFileLineNumber3 = BLOCK_3_START_LINE;

    EXPECT_CALL(*m_duplicatedCodeBlocksMock, insert(DuplicatedCodeBlock{m_code_block_1, m_code_block_2})).WillOnce(Return());
    EXPECT_CALL(*m_duplicatedCodeBlocksMock, insert(DuplicatedCodeBlock{m_code_block_1, m_code_block_3})).WillOnce(Return());
    
    CodeLine l_line(FILE_NAME_1, CodeLineStatus(true), l_fileLineNumber, l_fileLineNumber);
    vector<CodeLine> l_duplicatedCodeLines{
        CodeLine(FILE_NAME_2, CodeLineStatus(true), l_duplicatedFileLineNumber2, l_duplicatedFileLineNumber2),
        CodeLine(FILE_NAME_3, CodeLineStatus(true), l_duplicatedFileLineNumber3, l_duplicatedFileLineNumber3)};
    m_sut.addCodeLine(l_line, l_duplicatedCodeLines);

    for (++l_duplicatedFileLineNumber2, ++l_duplicatedFileLineNumber3, ++l_fileLineNumber;
         l_duplicatedFileLineNumber2 <= BLOCK_2_END_LINE; 
         ++l_duplicatedFileLineNumber2, ++l_duplicatedFileLineNumber3, ++l_fileLineNumber)
    {
        l_line = CodeLine(FILE_NAME_1, CodeLineStatus(false), l_fileLineNumber, l_fileLineNumber);
        l_duplicatedCodeLines = vector<CodeLine>{
            CodeLine(FILE_NAME_2, CodeLineStatus(false), l_duplicatedFileLineNumber2, l_duplicatedFileLineNumber2),
            CodeLine(FILE_NAME_3, CodeLineStatus(false), l_duplicatedFileLineNumber3, l_duplicatedFileLineNumber3)};    
        m_sut.addCodeLine(l_line, l_duplicatedCodeLines);
    }
    m_sut.finishAddingCodeLine();
}

}

