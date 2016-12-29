/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <iostream>
#include "DuplicatedCodeBlocks.hpp"
#include "Json.hpp"

DuplicatedCodeBlocks::DuplicatedCodeBlocks()
    : m_totalDuplicateLines(0),
      m_duplicates()
{
}

void DuplicatedCodeBlocks::insert(const DuplicatedCodeBlock & p_duplicatedCodeBlock)
{
    auto l_key = make_pair(p_duplicatedCodeBlock.first.getFilePath(), 
                           p_duplicatedCodeBlock.second.getFilePath());
    m_duplicates[l_key].push_back(p_duplicatedCodeBlock);
    m_totalDuplicateLines +=   getDuplicatedCodeBlockLines(p_duplicatedCodeBlock);
}

void DuplicatedCodeBlocks::dumpDuplicatedCodeLines()
{
    cout << "totalDuplicate: " << m_totalDuplicateLines << endl;
}

void DuplicatedCodeBlocks::printDupplicateedCodeBlockInfo(stringstream & p_output, const DuplicatedCodeBlock & p_duplicatedCodeBlock)
{
    p_output << "{\n"
             << "\"duplicate\": "   << getDuplicatedCodeBlockLines(p_duplicatedCodeBlock) << ",\n"
             << "\"startLine1\": "  << p_duplicatedCodeBlock.first.getBeginLineNumber() << ",\n"
             << "\"lineNumber1\": " << p_duplicatedCodeBlock.first.getLines() << ",\n"
             << "\"startLine2\": "  << p_duplicatedCodeBlock.second.getBeginLineNumber() << ",\n"
             << "\"lineNumber2\": " << p_duplicatedCodeBlock.second.getLines() << "\n"
             << "},\n"; 
}

void DuplicatedCodeBlocks::dumpDuplicatedCodeInfo(const string & p_fileName)
{
    stringstream l_output;
    l_output << "{\n"
             << "\"results\": [\n";
             
    for (const auto & l_duplicate : m_duplicates)
    {
        l_output << "{\n";
        l_output << "\"fileName1\": \"" << *l_duplicate.first.first << "\",\n"
                 << "\"fileName2\": \"" << *l_duplicate.first.second << "\",\n"
                 << "\"details\": [\n";
        size_t l_duplicateLines = 0;
        for (const auto & l_duplicatedCodeBlock : l_duplicate.second)
        {
            printDupplicateedCodeBlockInfo(l_output, l_duplicatedCodeBlock);
            l_duplicateLines += getDuplicatedCodeBlockLines(l_duplicatedCodeBlock);
        }

        l_output.seekp(-2, ios_base::cur);
        l_output << "\n";
        l_output << "],\n"
                 << "\"duplicate\": " << l_duplicateLines << "\n"
                 << "},\n";
    }
    long l_pos = l_output.tellp();
    l_output.seekp(l_pos - 2);
    l_output << "\n";
    l_output << "],\n"
             << "\"totalDuplicate\": " << m_totalDuplicateLines << "\n"
             << "}";
    return Json::dump(l_output, p_fileName);
}

