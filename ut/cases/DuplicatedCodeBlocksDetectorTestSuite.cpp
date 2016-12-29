/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/

#include "DuplicatedCodeBlocksDetector.hpp"
#include "FileReaderMock.hpp"
#include "DuplicatedCodeBlocksBuilderMock.hpp"
#include "DuplicatedCodeBlocksBuilderFactoryMock.hpp"
#include "TestCommon.hpp"
#include "gtest/gtest.h"

namespace testing
{

const LineNumber LINE_1 = 1;
const LineNumber LINE_2 = 2;

class DuplicatedCodeBlocksDetectorTestSuite : public Test
{
public:
    DuplicatedCodeBlocksDetectorTestSuite()
        : m_fileReaderMock(make_shared<FileReaderMock>()),
          m_builderFactory(make_shared<DuplicatedCodeBlocksBuilderFactoryMock>()),
          m_sut(m_fileReaderMock, m_builderFactory)
    {
    }

protected:
    shared_ptr<FileReaderMock> m_fileReaderMock;
    shared_ptr<DuplicatedCodeBlocksBuilderFactoryMock> m_builderFactory;
    DuplicatedCodeBlocksDetector m_sut;
};


TEST_F(DuplicatedCodeBlocksDetectorTestSuite, correctGetDuplicatedCodeLines)
{
    Lines l_lines{{LINE_1, "hello"}, {LINE_2, "world"}};
    
    CodeLine l_file_1_line_1(FILE_NAME_1, CodeLineStatus(true), LINE_1, LINE_1);
    CodeLine l_file_1_line_2(FILE_NAME_1, CodeLineStatus(true), LINE_2, LINE_2);

    EXPECT_CALL(*m_fileReaderMock, getLines(FILE_NAME_1)).WillOnce(Return(l_lines));
    auto l_builderMock1 = new DuplicatedCodeBlocksBuilderMock;
    EXPECT_CALL(*l_builderMock1, addCodeLine(l_file_1_line_1, vector<CodeLine>{})).WillOnce(Return());
    EXPECT_CALL(*l_builderMock1, addCodeLine(l_file_1_line_2, vector<CodeLine>{})).WillOnce(Return());
    EXPECT_CALL(*l_builderMock1, finishAddingCodeLine()).WillOnce(Return());
    EXPECT_CALL(*m_builderFactory, createBuilderProxy(FILE_NAME_1)).WillOnce(Return(l_builderMock1));
    m_sut.scanFile(FILE_NAME_1);

    CodeLine l_file_2_line_1(FILE_NAME_2, CodeLineStatus(true), LINE_1, LINE_1);
    CodeLine l_file_2_line_2(FILE_NAME_2, CodeLineStatus(true), LINE_2, LINE_2);

    auto l_builderMock2 = new DuplicatedCodeBlocksBuilderMock;
    EXPECT_CALL(*m_builderFactory, createBuilderProxy(FILE_NAME_2)).WillOnce(Return(l_builderMock2));
    EXPECT_CALL(*m_fileReaderMock, getLines(FILE_NAME_2)).WillOnce(Return(l_lines));
    EXPECT_CALL(*l_builderMock2, addCodeLine(l_file_2_line_1, vector<CodeLine>{l_file_1_line_1})).WillOnce(Return());
    EXPECT_CALL(*l_builderMock2, addCodeLine(l_file_2_line_2, vector<CodeLine>{l_file_1_line_2})).WillOnce(Return());
    EXPECT_CALL(*l_builderMock2, finishAddingCodeLine()).WillOnce(Return());
    m_sut.scanFile(FILE_NAME_2);
}

}

