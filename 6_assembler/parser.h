

#include <string>
#include <fstream>
#include <map>

#include "commandType.h"

using std::string;
using std::ifstream;
using std::map;

/*  Encapsulates access to the input code. Reads an assembly language command, parses it, and
    provides convenient access to the command’s components (fields and symbols). In addition, removes all
    white space and comments. */
class parser{

    map<string, string> compMapNotA;
    map<string, string> compMapA;

    string curCmd;
    ifstream myFile;
    
public:
    // opens the input file and gets ready to use it
    parser(char* inFile);
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
    /* return the dest mnemonic in the current C command (8 possibilities)
        should be called only when commandType is C */
    string dest();
    /* returns the comp mnemonic in the current C command (28 possibilities)
        should be called only when commandType is C */
    string comp();
    /* returns the jump mnemonic in the current C command (8 possibilities)
        should be called only when commandType is C */
    string jump();
};