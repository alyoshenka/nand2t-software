#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "constructs.h"

using std::string;
using std::ifstream;

/** removes all comments and white space from the 
 * input stream and breaks it into Jack-language
 * tokens, as specified by the Jack grammar.
 */
class jackTokenizer{

    ifstream inputFile;
    string fileContents;
    string currentToken;

    /** strips a single block or api
     * comment. Returns the stripped string */
    static string stripComment(string text);

public:
    /** Opens the input file/stream and gets ready
     * to tokenize it. */
    jackTokenizer(string inFile);

    /** More tokens in input? */
    bool hasMoreTokens();

    /** Gets the next token from the input and 
     * makes it the current token. This method
     * should only be called if hasMoreTokens()
     * is true. Initially there is no current token. */
    void advance();

    /** Returns the type of the current token. */
    tokentype tokenType();

    /** Returns the keyword which is the current 
     * token. Should only be called when token()
     * is KEYWORD. */
    keyword keyWord();

    /** Returns the character which is the current 
     * token. Should only be called when tokenType()
     * is SYMBOL. */
    char symbol();

    /** Returns the identifier which is the current 
     * token. Should only be called when tokenType()
     * is IDENTIFIER. */
    string identifier();

    /** Returns the integer value of the current 
     * token. Should only be called when tokenType()
     * is INT_CONST. */
    int intVal();

    /** Returns the string value of the current 
     * token. Should only be called when tokenType()
     * is STRING_CONST. */
    string stringVal();

    /** returns the current token */
    string getCurrentToken() const;

    /** returns the file contents */
    string getFileContents() const;
};