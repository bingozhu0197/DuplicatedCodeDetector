/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/

#include "CurlyBracesFormatter.hpp"
#include "FileReaderMock.hpp"
#include "gtest/gtest.h"

namespace testing
{

using LinesParam = pair<Lines, Lines>; //<input, expect>
class CurlyBracesFormatterTestSuite : public TestWithParam<LinesParam>
{
public:
    CurlyBracesFormatterTestSuite()
        : m_fileReaderMock(make_shared<FileReaderMock>()),
          m_sut(m_fileReaderMock)
    {}

protected: 
    shared_ptr<FileReaderMock> m_fileReaderMock;
    CurlyBracesFormatter m_sut;
};

INSTANTIATE_TEST_CASE_P(CurlyBracesFormatterTestSuite,
                        CurlyBracesFormatterTestSuite,
                        Values(
                            LinesParam{{{1, "hello{"}, {2, "world"}}, {{1, "hello"}, {1, "{"}, {2, "world"}}},
                            LinesParam{{{1, "hello"}, {2, "world}"}}, {{1, "hello"}, {2, "world"}, {2, "}"}}},
                            LinesParam{{{1, "hello{world"}}, {{1, "hello"}, {1, "{"}, {1, "world"}}},
                            LinesParam{{{1, "hello}world"}}, {{1, "hello"}, {1, "}"}, {1, "world"}}}));

TEST_P(CurlyBracesFormatterTestSuite, formatLinesCorrectly)
{
    Lines l_lines{{1, "hello{"}, {2, "world"}};
    Lines l_expectedLines{{1, "hello"}, {1, "{"}, {2, "world"}};
    const FilePath l_testFileName = make_shared<string>("MyHellowWorld/src/hello.cpp");
        
    EXPECT_CALL(*m_fileReaderMock, getLines(l_testFileName)).WillOnce(Return(GetParam().first));
    auto l_formatedLines = m_sut.getLines(l_testFileName);
    EXPECT_EQ(l_formatedLines, GetParam().second);
}

}

