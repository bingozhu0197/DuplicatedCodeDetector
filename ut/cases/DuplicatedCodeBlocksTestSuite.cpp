/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <fstream>
#include "DuplicatedCodeBlocks.hpp"
#include "TestCommon.hpp"
#include "gtest/gtest.h"

namespace testing
{

class DuplicatedCodeBlocksTestSuite: public Test
{
public:
    DuplicatedCodeBlocksTestSuite()
        : m_code_block_1{FILE_NAME_1, BLOCK_1_START_LINE},
          m_code_block_2{FILE_NAME_2, BLOCK_2_START_LINE},
          m_code_block_3{FILE_NAME_3, BLOCK_3_START_LINE},
          m_sut()
    {
        m_code_block_1.updateEndLineNumber(BLOCK_1_END_LINE);
        m_code_block_2.updateEndLineNumber(BLOCK_2_END_LINE);
        m_code_block_3.updateEndLineNumber(BLOCK_3_END_LINE);
    }
    bool isFileSame(const string p_file1, const string p_file2)
    {
        ifstream l_file1(p_file1);
        ifstream l_file2(p_file2);
        return std::equal(std::istreambuf_iterator<char>(l_file1), 
                          std::istreambuf_iterator<char>(), 
                          std::istreambuf_iterator<char>(l_file2));
    }
protected:
    CodeBlock m_code_block_1;
    CodeBlock m_code_block_2;
    CodeBlock m_code_block_3;
    DuplicatedCodeBlocks m_sut;
};

TEST_F(DuplicatedCodeBlocksTestSuite, dumpSummary)
{
    m_sut.insert({m_code_block_1, m_code_block_2});    
    string l_expectedDump{"totalDuplicate: "};
    l_expectedDump += to_string(m_code_block_1.getLines() + m_code_block_2.getLines());
    l_expectedDump += "\n";

    testing::internal::CaptureStdout();
    m_sut.dumpDuplicatedCodeLines();
    std::string l_dumpedDuplicatedCodeLines = testing::internal::GetCapturedStdout();
    EXPECT_EQ(l_expectedDump, l_dumpedDuplicatedCodeLines);

}

TEST_F(DuplicatedCodeBlocksTestSuite, dumpDetailInJson)
{
    m_sut.insert({m_code_block_1, m_code_block_2});
    m_sut.insert({m_code_block_2, m_code_block_3});

    //As json output is actually no ordered required, 
    //the expected output can be adjusted when refactor code
    const string l_outputFile = "output.json";
    const string l_expectFile = "../cases/DuplicatedCodeBlocksTestSuiteExpect.json"; 

    m_sut.dumpDuplicatedCodeInfo(l_outputFile);

    EXPECT_TRUE(isFileSame(l_outputFile, l_expectFile));
}

}

