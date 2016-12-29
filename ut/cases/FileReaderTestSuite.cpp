/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include "gtest/gtest.h"
#include "FileReader.hpp"

namespace testing
{

class FileReaderTestSuite: public Test
{
public:
    FileReaderTestSuite()
        : m_sut()
    {}

protected: 
    FileReader m_sut;
};

TEST_F(FileReaderTestSuite, getFileLines)
{
    FilePath l_file = make_shared<string>("../cases/FileReaderTest.txt");
    Lines l_expectedLines{{1, "hello"}, {2, "world"}};
    
    EXPECT_EQ(l_expectedLines,  m_sut.getLines(l_file));
}

}

