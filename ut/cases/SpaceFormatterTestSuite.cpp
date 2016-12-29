/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/

#include "SpaceFormatter.hpp"
#include "FileReaderMock.hpp"
#include "gtest/gtest.h"

namespace testing
{

class SpaceFormatterTestSuite: public Test
{
public:
    SpaceFormatterTestSuite()
        : m_fileReaderMock(make_shared<FileReaderMock>()),
          m_sut(m_fileReaderMock)
    {}

protected: 
    shared_ptr<FileReaderMock> m_fileReaderMock;
    SpaceFormatter m_sut;
};


TEST_F(SpaceFormatterTestSuite, removeSpace)
{
    Lines l_lines{{1, "  hello  "}, {2, "  world  "}, {3, "   "}};
    Lines l_expectedLines{{1, "hello"}, {2, "world"}, {3, ""}};
    const FilePath l_testFileName = make_shared<string>("MyHellowWorld/src/hello.cpp");
        
    EXPECT_CALL(*m_fileReaderMock, getLines(l_testFileName)).WillOnce(Return(l_lines));
    auto l_formatedLines = m_sut.getLines(l_testFileName);
    EXPECT_EQ(l_formatedLines, l_expectedLines);
}

}

