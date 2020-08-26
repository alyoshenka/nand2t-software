#pragma once

#include <string>
using std::string;

enum commandType{
    // all the arithmetic command
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL
};

// ASM function implementation
namespace functions{

    const string add = 
        "(ADD)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement stack\n"
        "   A=M // go to top of stack\n"
        "   D=M // store top value\n"
        "   A=A-1 // get address of next value\n"
        "   D=D+M // add\n"
        "   M=D // store\n"
        "   A=A+1 // get top value\n"
        "   M=0 // clear\n";

    const string sub = 
        "(SUB)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement stack\n"
        "   A=M // go to top of stack\n"
        "   D=M // store top value\n"
        "   A=A-1 // get address of next value\n"
        "   D=D-M // sub\n"
        "   M=D // store\n"
        "   A=A+1 // get top value\n"
        "   M=0 // clear\n";

    const string neg = 
        "(NEG)\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to top value of stack\n"
        "   M=-M // negate value\n";

    const string eq = 
        "// equality function (true)\n"
        "(IS_EQ)\n"
        "   @eq_val // get value\n"
        "   M=-1 // true\n"
        "   @AFTER_EQ // post set function\n"
        "   0;JMP\n"
        "// equality function (false)\n"
        "(NOT_EQ)\n"
        "   @eq_val // get value\n"
        "   M=0 // false\n"
        "   @AFTER_EQ // post set function\n"
        "   0;JMP\n"
        "// setup function\n"
        "(EQ)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value\n"
        "   A=M // go to top of stack\n"
        "   D=M // store value in D\n"
        "   M=0 // clear value\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to next value\n"
        "   D=D-M // subtract\n"
        "   @IS_EQ // set dest for true\n"
        "   D;JEQ // jump if 0\n"
        "   @NOT_EQ // set dest for false\n"
        "   D;JNE // jump if not 0\n"
        "// cleanup function\n"
        "(AFTER_EQ) // after set value\n"
        "   @eq_val // load return val\n"
        "   D=M // store val\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to top value\n"
        "   M=D; // set value\n";

    const string gt = "(GT)\n";

    const string lt = "(LT)\n";

    const string and_func = 
        "(AND)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value to get first number\n"
        "   A=M // go to stack\n"
        "   D=M // store first number\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value\n"
        "   @SP // go to stack pointer\n"
        "   A=M // go to stack\n"
        "   M=M&D // calculate value\n"
        "   @SP // go to stack pointer\n"
        "   M=M+1 // increment value;\n";

    const string or_func = 
        "(OR)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value to get first number\n"
        "   A=M // go to stack\n"
        "   D=M // store first number\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value\n"
        "   @SP // go to stack pointer\n"
        "   A=M // go to stack\n"
        "   M=M|D // calculate value\n"
        "   @SP // go to stack pointer\n"
        "   M=M+1 // increment value\n";

    const string not_func = 
        "(NOT)\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to top value of stack\n"
        "   M=!M // bitwise negation\n";


    const string push =
        "(PUSH)\n"  
        "   @push_val\n"        
        "   D=M // set register D to number\n"
        "   @SP // get stack value as address\n"
        "   A=M // go to addres (top of stack)\n"
        "   M=D // set top of stack to number\n"
        "   @SP // get SP address\n"
        "   M=M+1 // increment stack pointer\n";

    const string ret =
        "   @MAIN\n"
        "   0;JMP // return control to main\n";

    const string incr =
        "   @line_num\n"
        "   M=M+1 // increment\n";
};