#pragma once

#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>

#include "jackTokenizer.h"

using std::string;
using std::ofstream;

/** Effects the actual compilation output. Gets 
 * its input from a JackTokenizer and emits
 * its parsed structure into an output file/stream. 
 * The output is generated by a series of compilexxx()
 * routines, one for every syntactic element xxx of
 * the Jack grammar. The contract between these routines 
 * is that each compilexxx() routine should read the 
 * syntactic construct xxx from the input, advance() 
 * the tokenizer exactly beyond xxx, and output the 
 * parsing of xxx. Thus, compilexxx() may only be 
 * called if indeed xxx is the next syntactic element 
 * of the input. */
class compilationEngine{

    ofstream outStream;
    string indentation;

    jackTokenizer* tokenizer;

    static string kwToString(keyword kw);
    static bool isClassVarDec(keyword kw);
    static bool isSubroutineDec(keyword kw);
    static bool isFundamentalType(keyword kw);

public:

    /** Creates a new compilation engine. 
     * The next routine called must be compileClass() */
    compilationEngine(jackTokenizer* _tokenizer, string outputFile);

    /** Compiles a complete class */
    void compileClass();

    /** Compiles a static or field declaration. */
    void compileClassVarDec();

    /** Compiles a complete method, function, or 
     * constructor. */
    void compileSubroutine();

    /** Compiles a (possibly empty) parameter list, 
     * not including the closing "()". */
    void compileParameterList();

    /** Compiles a variable declaration. */
    void compileVarDec();

    /** Compiles a sequence of statements, not including
     * the enclosing "{}". */
    void compileStatements();

    /** Compiles a do statement. */
    void compileDo();

    /** Compiles a let statement. */
    void compileLet();

    /** Compiles a while statement. */
    void compileWhile();

    /** Compiles a return statement. */
    void compileReturn();

    /** Compiles an if statement, possibly with a 
     * trailing else clause. */
    void compileIf();

    /** Compiles an expression. */
    void compileExpression();

    /** Compiles a term. This routine is faced with some 
     * difficulty when trying to decide between some of the 
     * alternative parsing rules. Specifically, if the current 
     * token is an identifier, the routine must distinguish 
     * between a variable, an array entry, and a subroutine 
     * call. A single lookahead token, which may be one of 
     * "[", "(", or "." suffices to distinguish between the 
     * three possibilities. Any other token is not part of this
     * term and should be advanced over. */
    void compileTerm();

    /** Compiles a (possibly empty) comma-separated
     * list of expressions. */
    void compileExpressionList();
};