#pragma once

#include <string>
#include <fstream>

#include "commandType.h"

using std::string;
using std::ifstream;

/* Handles the parsing of a single .vm file, and 
    encapsulates access to the input code. It reads VM
    commands, parses them, and provides convenient 
    access to their components. In addition, it removes 
    all white space and comments. */
class parser{

    string curCmd;
    ifstream inFile;

    const string comment = "\\";
    const string whitespace = " \n\t\r\f\v";

public:
    // opens input file/stream
    parser(string fileName);
    // closes input file/stream
    ~parser();
    // more commands in input?
    bool hasMoreCommands();
    /* reads the next command from the input and
        makes it the current command
        should be called only if hasMoreCommands
        initially there is no current command */
    void advance();
    // current command type
    commandType currentCommand();
    /* first argument of current command 
        C_ARITHMETIC: command itself
        not called if C_RETURN */
    string arg1();
    /* second argument of current command
        only called if C_PUSH, C_POP, C_FUNCTION, OR C_CALL */
    int arg2();
};