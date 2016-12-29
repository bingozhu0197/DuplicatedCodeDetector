/**
 *******************************************************************************
 *
 * Copyright (c) 2016 GPL. All rights reserved.
 *******************************************************************************/
#include <string>
#include "Common.hpp"
#include "Config.hpp"

class MainArgsParser
{
public:        
    bool parseMainArgument(int argc, char * argv[]);

    bool shouldRemoveComments() const
    {
        return m_removeComments;
    }

    bool shouldFormatCurlyBraces() const
    {
       return m_formatCurlyBraces;
    }

    string getOutputJsonFileName() const
    {
        return m_outputJsonFileName;
    }

    size_t getDuplicatedBlockLeastCodeLines() const
    {
        return m_leastLinesOfDuplicated;
    }

    string getCodeFileDirectory() const
    {
        return m_codeFileDirectory;
    }
private:
    void helpInfo(const string & p_programName);
    bool m_removeComments = false;
    bool m_formatCurlyBraces = false;
    string m_outputJsonFileName;
    unsigned int m_leastLinesOfDuplicated = CODE_BLOCK_LEAST_LINES; 
    string m_codeFileDirectory;
};

