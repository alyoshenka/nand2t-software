#pragma once


#include <string>
#include <fstream>

#include "commandType.h"

using std::string;
using std::ofstream;

// translates VM commands into Hack assembly code
class codeWriter {
    ofstream outFile;
    string fileName;
public:
    // opens output file and gets ready to write to it
    codeWriter(const string file);
    // closes output file
    ~codeWriter();
    // translation of a new VM file is started
    void setFileName(string fileName);
    // the name of the current file
    string getFileName();
    /* writes the assembly code that is the translation
        of the given arithmetic command */
    void writeArithmetic(string command);
    /* writes the assembly code this is the translation
        of the gicen command, where command is either
        C_PUSH or C_POP */
    void writePushPop(commandType command, string segment, int index);
    // closes the output file
    void close();
    /* writes assembly code that effects the VM initialization
        this code must be placed at the beginning of the output file */
    void writeInit();
    // writes assembly code that effects the label command
    void writeLabel(string label);
    // writes assembly code that effects the goto command
    void writeGoto(string label);
    // writes assembly code that effects the if-goto command
    void writeIf(string label);
    // writes assembly code that effects the call command
    void writeCall(string label, int numArgs);
    // writes assembly code that effects the return command
    void writeReturn();
    // writes assembly code that effects the function command
    void writeFunction(string label, int numLocals);
};