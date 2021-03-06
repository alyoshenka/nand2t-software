#pragma once

#include <string>
#include <fstream>

#include "commandType.h"
#include "symbolTable.h"

using std::string;
using std::ifstream;
using std::ofstream;

/*  Encapsulates access to the input code. Reads an assembly language command, parses it, and
    provides convenient access to the command’s components (fields and symbols). In addition, removes all
    white space and comments. */
class parser{

    string curCmd;
    ifstream inFile;
    ofstream outFile;

    symbolTable table;
    int symAddr; // ()
    int varAddr; // @
    
public:
    // opens the input file and gets ready to use it
    parser(char* fileName);
    // closes the input file
    ~parser();
    // current command string
    string getCurCmd();
    // are there more commands in the input?
    bool hasMoreCommands();
    /* reads the next command from the input and makes it the current command
        should be called only if hasMoreCommands is true
        initially there is no current command */
    void advance();
    // returns the type of the current command
    commandType currentCommand();
    /* returns the symbol or decimal Xxx of the current command @Xxx or (Xxx)
        should be called only when commandType is A or L */
    string symbol();
    /* returns the dest mnemonic in the current C command */
    string dest();
    /* returns the comp mnemonic in the current C command */
    string comp();
    /* returns the jump mnemonic in the current C command */
    string jump();
    /* writes a given line to the output file */
    void push(string line);
    /* adds the current symbol to the table */
    void addCurrentSymbol();
    /* check if current symbol is not a number */
    bool isSymbol(string sym);
    /* returns the numerical address of a symbol or address */
    int getAddress(string sym);
    /* reset file handle to beginning */
    void resetFile(string fileName);
    /* increment symbol counter () */
    void incSym();
};