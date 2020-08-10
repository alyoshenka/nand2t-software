

#include <string>
#include <fstream>

#include "commandType.h"

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
};