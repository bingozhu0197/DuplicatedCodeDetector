/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#pragma once

#include <sstream>

class Json
{
public:
    static void dump(stringstream & p_data, const string & p_fileName);

private:
    static string indent(unsigned int p_level);
};

