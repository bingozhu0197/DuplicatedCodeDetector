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
    const shared_ptr<IDuplicatedCodeBlocksBuilderFactory> & p_builderFactory,
    uint32_t p_fileNumbers,
    uint32_t p_leastCodeLinesOfDuplicatedBlock)
    : m_fileReader(p_fileReader),
      m_builderFactory(p_builderFactory),
      m_codeLines(p_fileNumbers * 10),
      m_leastCodeLinesOfDuplicatedBlock(p_leastCodeLinesOfDuplicatedBlock)
{}

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

void DuplicatedCodeBlocksDetector::processLines(const FilePath & p_filePath, const Lines & p_lines)
{
    auto l_builder = m_builderFactory->createBuilder(p_filePath);
    if (p_lines.size() < m_leastCodeLinesOfDuplicatedBlock)
    {
        return;
    }

    uint32_t l_codeLineNumber = m_leastCodeLinesOfDuplicatedBlock;
    for (auto l_line = std::next(begin(p_lines), m_leastCodeLinesOfDuplicatedBlock);
         l_line != end(p_lines);
         l_line = next(l_line), ++l_codeLineNumber)
    {
        bool l_isNewLine = false;
        if (l_line == begin(p_lines)
            || l_line->first != prev(l_line)->first)
        {
            l_isNewLine = true;
        }

        CodeLine l_codeLine{p_filePath, CodeLineStatus(l_isNewLine), l_line->first, l_codeLineNumber, std::prev(l_line, m_leastCodeLinesOfDuplicatedBlock)->first};
        size_t l_hash = 0;
        for (int i = m_leastCodeLinesOfDuplicatedBlock; i > 0; i--)
        {
            hash_combine(l_hash, std::prev(l_line, i)->second);
        }

        l_builder->addCodeLine(l_codeLine, m_codeLines[l_hash]);
        m_codeLines[l_hash].push_back(move(l_codeLine));
    }
    l_builder->finishAddingCodeLine();
}

void DuplicatedCodeBlocksDetector::scanFile(const FilePath & p_filePath)
{
    processLines(p_filePath, m_fileReader->getLines(p_filePath));
}
