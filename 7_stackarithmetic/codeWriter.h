#pragma once


#include <string>
#include <fstream>

#include "commandType.h"

using std::string;
using std::ofstream;

// translates VM commands into Hack assembly code
class codeWriter {
    ofstream outFile;
public:
    // opens output file and gets ready to write to it
    codeWriter(string fileName);
    // closes output file
    ~codeWriter();
    // translation of a new VM file is started
    void setFileName(string fileName);
    /* writes the assembly code that is the translation
        of the given arithmetic command */
    void writeArithmetic(string command);
    /* writes the assembly code this is the translation
        of the gicen command, where command is either
        C_PUSH or C_POP */
    void writePushPop(commandType command, string segment, int index);
    // closes the output file
    void close();
};