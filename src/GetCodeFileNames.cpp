/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <experimental/filesystem>
#include "Common.hpp"

namespace fs = std::experimental::filesystem;

bool shouldIgnoreHideFiles(const string & p_fileName)
{
    if (p_fileName.front() == '.')
    {
        return true;
    }
    return false;
}

const vector<string> g_codeFileExtensions{".c", ".h", ".cpp", ".hpp", ".cc"};

bool hasCodeFileExtension(const string & p_fileExtension)
{
    return std::find(std::begin(g_codeFileExtensions),
              std::end(g_codeFileExtensions),
              p_fileExtension) != std::end(g_codeFileExtensions);
}

bool isCodeFile(const auto & p_filePath)
{
    if (fs::is_regular_file(p_filePath)
        && hasCodeFileExtension(p_filePath.extension()))
    {
        return true;
    }
    return false;
}

FilePaths operator += (FilePaths & lhs, FilePaths && rhs)
{
    lhs.insert(end(lhs), begin(rhs), end(rhs));
    return lhs;
}

FilePaths getCodeFilePathsRecursively(const string & p_directory)
{
    if (!fs::is_directory(p_directory))
    {
        cerr << "can't open " << p_directory << endl;
        return {};
    }

    FilePaths l_filePaths;
    for (auto & l_dirEntry : fs::directory_iterator(p_directory))
    {
        auto & l_path = l_dirEntry.path();
        if (shouldIgnoreHideFiles(l_path.filename()))
        {
            continue;
        }

        if (fs::is_directory(l_dirEntry))
        {
            l_filePaths += getCodeFilePathsRecursively(l_dirEntry.path());
        }
        else if (isCodeFile(l_path))
        {
            l_filePaths.push_back(make_shared<string>(l_path));
        }
    };

    return l_filePaths;
}
