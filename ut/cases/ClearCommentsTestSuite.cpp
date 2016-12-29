/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/

#include "ClearComments.hpp"
#include "FileReaderMock.hpp"
#include "gtest/gtest.h"

namespace testing
{

class ClearCommentsTestSuite: public Test
{
public:
    ClearCommentsTestSuite()
        : m_fileReaderMock(make_shared<FileReaderMock>()),
          m_sut(m_fileReaderMock)
    {}

protected: 
    shared_ptr<FileReaderMock> m_fileReaderMock;
    ClearComments m_sut;
};


TEST_F(ClearCommentsTestSuite, clearSingleLineComments)
{
    Lines l_lines{{1, "//comments"}, {2, "world//comments"}};
    Lines l_expectedLines{{1, ""}, {2, "world"}};
    const FilePath l_testFileName = make_shared<string>("MyHellowWorld/src/hello.cpp");
        
    EXPECT_CALL(*m_fileReaderMock, getLines(l_testFileName)).WillOnce(Return(l_lines));
    auto l_formatedLines = m_sut.getLines(l_testFileName);
    EXPECT_EQ(l_formatedLines, l_expectedLines);
}

TEST_F(ClearCommentsTestSuite, clearBlockComment)
{
    Lines l_lines{{1, "/*xxx"}, {2, "xxx"}, {3, "xxx*/"}};
    Lines l_expectedLines{{1, ""}, {2, ""}, {3, ""}};
    const FilePath l_testFileName = make_shared<string>("MyHellowWorld/src/hello.cpp");
        
    EXPECT_CALL(*m_fileReaderMock, getLines(l_testFileName)).WillOnce(Return(l_lines));
    auto l_formatedLines = m_sut.getLines(l_testFileName);
    EXPECT_EQ(l_formatedLines, l_expectedLines);
}

}

