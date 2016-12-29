/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <unistd.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>
#include "Common.hpp"

bool shouldIgnoreName(const string & p_fileName)
{
    if (p_fileName.front() == '.')
    {
        return true;
    }
    return false;    
}

bool isDirectory(const string & p_filePath)
{
    struct stat l_s;
    if(stat(p_filePath.c_str(), &l_s) != -1
       && S_ISDIR(l_s.st_mode))
    {
        return true;
    }
    return false;    
}

bool isRegularFile(const string & p_filePath)
{
    struct stat l_s;    
    if(stat(p_filePath.c_str(), &l_s) != -1
       && S_ISREG(l_s.st_mode))
    {
        return true;
    }
    return false;
}

const vector<string> CODE_FILE_POSTFIX{".c", ".h", ".cpp", ".hpp", ".cc"};

bool hasCodeFilePostfix(const string & p_fileName)
{
    for (auto & l_postfix : CODE_FILE_POSTFIX)
    {
        if (p_fileName.length() > l_postfix.length()
            && 0 == p_fileName.compare(p_fileName.length() - l_postfix.length(), l_postfix.length(), l_postfix))
        {
            return true;
        }
    }
    return false;
}
    
bool isCodeFile(const string & p_fileName)
{
    if (isRegularFile(p_fileName)
        && hasCodeFilePostfix(p_fileName))
    {
        return true;
    }
    return false;
}

string buildFilePath(const string & p_directory,
                     const string & p_fileName)
{
    if (p_directory.back() == '/')
    {
        return p_directory + p_fileName;
    }
    return p_directory + "/" +  p_fileName;

}

FilePaths operator += (FilePaths & lhs, FilePaths && rhs)
{
    lhs.insert(end(lhs), begin(rhs), end(rhs));
    return lhs;
}

FilePaths getCodeFilePathsRecursively(const string & p_directory)
{
    DIR * l_dir = opendir(p_directory.c_str());
    if (l_dir == nullptr) 
    {
        cerr << "can't open " << p_directory << endl;
        return {};
    }
    
    struct dirent *l_ent = nullptr;
    FilePaths l_filePaths;
    while((l_ent = readdir (l_dir)) != nullptr)
    {
        string l_fileName = l_ent->d_name;
        if (shouldIgnoreName(l_fileName))
        {
            continue;
        }

        string l_filePath = buildFilePath(p_directory, l_fileName);
        if (isDirectory(l_filePath))
        {
            l_filePaths += getCodeFilePathsRecursively(l_filePath);
        }
        else if (isCodeFile(l_filePath))
        {
            l_filePaths.push_back(make_shared<string>(l_filePath));
        }
    };
    
    closedir (l_dir);
    return l_filePaths;
}

