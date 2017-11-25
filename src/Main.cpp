/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <climits>
#include <memory>
#include <cassert>
#include "Common.hpp"
#include "DuplicatedCodeBlocks.hpp"
#include "GetCodeFileNames.hpp"
#include "IFileReader.hpp"
#include "FileReader.hpp"
#include "ILinesDecorator.hpp"
#include "CurlyBracesFormatter.hpp"
#include "SpaceFormatter.hpp"
#include "DuplicatedCodeBlocksDetector.hpp"
#include "ClearComments.hpp"
#include "RemoveEmptyLine.hpp"
#include "MainArgsParser.hpp"
#include "DuplicatedCodeBlocksBuilderFactory.hpp"

void applyFileLinesFormatter(const MainArgsParser & p_argsParser, shared_ptr<IFileReader> &  p_fileReader)
{

    p_fileReader = make_shared<SpaceFormatter>(p_fileReader);
    if (p_argsParser.shouldRemoveComments())
    {
        p_fileReader = make_shared<ClearComments>(p_fileReader);
    }

    if (p_argsParser.shouldFormatCurlyBraces())
    {
        p_fileReader = make_shared<CurlyBracesFormatter>(p_fileReader);
    }
    p_fileReader = make_shared<RemoveEmptyLine>(p_fileReader);
}

int main(int argc, char * argv[])
{
    MainArgsParser l_argsParser;
    if (!l_argsParser.parseMainArgument(argc, argv))
    {
        exit(EXIT_FAILURE);
    }

    auto l_codeFilePaths = getCodeFilePathsRecursively(l_argsParser.getCodeFileDirectory());
    if (l_codeFilePaths.empty())
    {
        cout << "no code files found" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto l_duplicatedCodeBlock = make_shared<DuplicatedCodeBlocks>();

    auto l_builderFactory = make_shared<DuplicatedCodeBlocksBuilderFactory>(
        l_duplicatedCodeBlock,
        l_argsParser.getDuplicatedBlockLeastCodeLines());

    shared_ptr<IFileReader> l_fileReader = make_shared<FileReader>();
    applyFileLinesFormatter(l_argsParser, l_fileReader);
    DuplicatedCodeBlocksDetector l_duplicatedCodeBlocksDetector(
        l_fileReader,
        l_builderFactory);

    for (auto & l_codeFilePath : l_codeFilePaths)
    {
        l_duplicatedCodeBlocksDetector.scanFile(l_codeFilePath);
    }

    if (l_argsParser.getOutputJsonFileName().empty())
    {
        l_duplicatedCodeBlock->dumpDuplicatedCodeLines();
    }
    else
    {
        l_duplicatedCodeBlock->dumpDuplicatedCodeInfo(l_argsParser.getOutputJsonFileName());
    }

    return 0;
}
