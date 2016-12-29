/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include "gtest/gtest.h"
#include "GetCodeFileNames.hpp"

namespace testing
{

TEST(getCodeFilePathsRecursively, getFileNamesSuccessfully)
{
    FilePaths l_expectedFilePaths{
        make_shared<string>("../cases/src/b.c"),
        make_shared<string>("../cases/src/src1/a.c")
        };
    string l_directory("../cases/src");

    auto l_getPaths = getCodeFilePathsRecursively(l_directory);
    EXPECT_EQ(l_expectedFilePaths.size(),  l_getPaths.size());
    for (size_t i = 0; i < l_expectedFilePaths.size(); ++i)
    {
        EXPECT_EQ(*l_expectedFilePaths[i], *l_getPaths[i]);
    }
}

}

