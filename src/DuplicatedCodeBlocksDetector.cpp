/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include "Common.hpp"
#include "DuplicatedCodeBlocksDetector.hpp"
#include "IFileReader.hpp"
#include "CodeLine.hpp"
#include "IDuplicatedCodeBlocksBuilder.hpp"
#include "IDuplicatedCodeBlocksBuilderFactory.hpp"

DuplicatedCodeBlocksDetector::DuplicatedCodeBlocksDetector(
    const shared_ptr<IFileReader> & p_fileReader,
    const shared_ptr<IDuplicatedCodeBlocksBuilderFactory> & p_builderFactory)
    : m_fileReader(p_fileReader),
      m_builderFactory(p_builderFactory),
      m_codeLines()
{}

void DuplicatedCodeBlocksDetector::processLines(const FilePath & p_filePath, const Lines & p_lines)
{
    auto l_builder = m_builderFactory->createBuilder(p_filePath);
    
    LineNumber l_codeLineNumber = 1;
    for (auto l_line = begin(p_lines);
         l_line != end(p_lines);
         l_line = next(l_line), ++l_codeLineNumber)
    {
        bool l_isNewLine = false;
        if (l_line == begin(p_lines)
            || l_line->first != prev(l_line)->first)
        {
            l_isNewLine = true;
        }

        CodeLine l_codeLine{p_filePath, CodeLineStatus(l_isNewLine), l_line->first, l_codeLineNumber};           

        l_builder->addCodeLine(l_codeLine, m_codeLines[l_line->second]);           
        m_codeLines[l_line->second].push_back(move(l_codeLine));
    }
    l_builder->finishAddingCodeLine();
}

void DuplicatedCodeBlocksDetector::scanFile(const FilePath & p_filePath)
{
    processLines(p_filePath, m_fileReader->getLines(p_filePath));
}

