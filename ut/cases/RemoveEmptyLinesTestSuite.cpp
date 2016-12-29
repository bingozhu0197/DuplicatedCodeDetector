/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/

#include "RemoveEmptyLine.hpp"
#include "FileReaderMock.hpp"
#include "gtest/gtest.h"

namespace testing
{

class RemoveEmptyLineTestSuite: public Test
{
public:
    RemoveEmptyLineTestSuite()
        : m_fileReaderMock(make_shared<FileReaderMock>()),
          m_sut(m_fileReaderMock)
    {}

protected: 
    shared_ptr<FileReaderMock> m_fileReaderMock;
    RemoveEmptyLine m_sut;
};


TEST_F(RemoveEmptyLineTestSuite, removeEmptyLine)
{
    Lines l_lines{{1, ""}, {2, "hello"}, {3, ""}, {4, "world"}, {5, ""}};
    Lines l_expectedLines{{2, "hello"}, {4, "world"}};
    const FilePath l_testFileName = make_shared<string>("MyHellowWorld/src/hello.cpp");
        
    EXPECT_CALL(*m_fileReaderMock, getLines(l_testFileName)).WillOnce(Return(l_lines));
    auto l_formatedLines = m_sut.getLines(l_testFileName);
    EXPECT_EQ(l_formatedLines, l_expectedLines);
}

}

