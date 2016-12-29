/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <memory>
#include <unordered_map>
#include "CodeLine.hpp"
#include "Config.hpp"

class IFileReader;
class IDuplicatedCodeBlocksBuilderFactory;

class DuplicatedCodeBlocksDetector
{
public:
    DuplicatedCodeBlocksDetector(
        const shared_ptr<IFileReader> & p_fileReader,
        const shared_ptr<IDuplicatedCodeBlocksBuilderFactory> & p_builderFactory);
    void scanFile(const FilePath & p_filePath);
    
private:
    void processLines(const FilePath & p_filePath, const Lines & p_lines);
    shared_ptr<IFileReader> m_fileReader;
    shared_ptr<IDuplicatedCodeBlocksBuilderFactory> m_builderFactory;
    unordered_map<string, vector<CodeLine>> m_codeLines;
};

