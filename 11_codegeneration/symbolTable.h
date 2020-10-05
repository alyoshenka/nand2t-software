#pragma once

#include <string>

#include "constructs.h"

using std::string;

/** Provides a symbol table abstraction. 
 * The symbol table associates the identifier 
 * names found in the program with identifier 
 * properties needed for compilation: type, 
 * kind, and running index. The symbol table 
 * for Jack programs has two nested scopes 
 * (class/subroutine)
 */
class symbolTable{

public:

    /** Creates a new empty symbol table. */
    symbolTable();

    /** Starts a new subroutine scope
     * (resets the subroutine symbol table) */
    void startSubroutine();

    /** Defines a new identifier of a given
     * name, type, and kind and assigns it
     * a running index. */
    void define(string name, string type, varKind kind);

    /** Returns the number of variables of the
     * given kind already defined in the current scope. */
    int varCount(varKind kind);

    /** Returns the kind of the given identifier in
     * the current scope. */
    varKind kindOf(string name);

    /** Returns the type of the given identifier in
     * the current scope. */
    string typeOf(string name);

    /** Returns the index assigned to the named 
     * identifier. */
    int indexOf(string name);
};