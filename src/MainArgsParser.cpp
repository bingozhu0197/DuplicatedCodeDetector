/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <iostream>
#include "MainArgsParser.hpp"
extern "C" {
#include <unistd.h>
}

void MainArgsParser::helpInfo(const string & p_programName)
{
    cout << p_programName << " FileDirectory [OPTIONS]\n"
         << "[OPTIONS]\n"
         << "    -c Should ignore comments, default is take comments as code\n"
         << "    -b Should process different style of curly braces \"{\" or \"}\"\n"
         << "    -j FileName output json file\n"
         << "    -n Least duplicated code lines to be taken as duplciated code" 
         << endl;
}


bool MainArgsParser::parseMainArgument(int argc, char * argv[])
{
    if (argc == 1)
    {
        cout << "argument is " << argc << endl;
        helpInfo(argv[0]);
        return false;
    }
    m_codeFileDirectory = argv[1];
    
    int l_opt; 
    while((l_opt = getopt(argc - 1, argv + 1, "cbj:n:")) != -1)
    {
        switch (l_opt)
        {
            case 'c':
                m_removeComments = true;
                break;

            case 'b':
                m_formatCurlyBraces = true;
                break;

            case 'j':
                m_outputJsonFileName = optarg;
                break;

            case 'n':
                m_leastLinesOfDuplicated = stoi(optarg);
                break;

            default:
                helpInfo(argv[0]);
                return false;
        }
    }
    return true;
}


