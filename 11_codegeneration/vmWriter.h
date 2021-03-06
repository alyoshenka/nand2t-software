#pragma once

#include "constructs.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

using std::ofstream;
using std::string;

/** Emits VM commands into a file, 
 * using the VM command syntax. */
class vmWriter
{

    ofstream outStream;

public:
    /** Creates a new file and prepares it
     * for writing. */
    vmWriter(string outFile);

    /** Writes a VM push command. */
    void writePush(segment seg, int idx);

    /** Writes a VM pop command. */
    void writePop(segment seg, int idx);

    /** Writes a VM arithmetic command. */
    void writeArithmetic(command com);

    /** Writes a VM label command. */
    void writeLabel(string label);

    /** Writes a VM goto command. */
    void writeGoto(string label);

    /** Writes a VM if-goto command. */
    void writeIf(string label);

    /** Writes a VM call command. */
    void writeCall(string name, int argCnt);

    /** Writes a VM function. */
    void writeFunction(string name, int argCnt);

    /** Writes a VM return command. */
    void writeReturn();

    /** Closes the output file. */
    void close();

    string segToStr(segment seg);
    string comToStr(command com);
};