/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <string>
#include <memory>
#include <utility>
#include <list>
#include <vector>
#include <utility>

using namespace std;

using FilePath = shared_ptr<string>;
using FilePaths = vector<FilePath>;

using LineNumber = unsigned int;
using LineData = pair<LineNumber, string>;
using Lines = list<LineData>;

