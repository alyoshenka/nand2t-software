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
        "   D=M-D // sub\n"
        "   M=D // store\n"
        "   A=A+1 // get top value\n"
        "   M=0 // clear\n";

    const string neg = 
        "(NEG)\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to top value of stack\n"
        "   M=-M // negate value\n";

    const string eq = 
        "(EQ)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value\n"
        "   A=M // go to top of stack\n"
        "   D=M // store value in D\n"
        "   M=0 // clear value\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to next value\n"
        "   D=D-M // subtract\n"
        "   @TRUE // set dest for true\n"
        "   D;JEQ // jump if 0\n"
        "   @FALSE // set dest for false\n"
        "   D;JNE // jump if not 0\n"
        "(TRUE)\n"
        "   @true\n"
        "   D=M // get true value\n"
        "   @eq_val\n"
        "   M=D // store value\n"
        "   @AFTER_SET\n"
        "   0;JMP // return control\n"
        "(FALSE)\n"
        "   @false\n"
        "   D=M // get false value\n"
        "   @eq_val\n"
        "   M=D // store value\n"
        "   @AFTER_SET\n"
        "   0;JMP // return control\n"
        "(AFTER_SET)\n"
        "   @eq_val\n"
        "   D=M // take value\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to top value\n"
        "   M=D; // set value\n";

    const string gt = 
        "(GT)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value\n"
        "   A=M // go to top of stack\n"
        "   D=M // store value in D\n"
        "   M=0 // clear value\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to next value\n"
        "   D=M-D // subtract\n"
        "   @TRUE // set dest for true\n"
        "   D;JGT // jump if 0\n"
        "   @FALSE // set dest for false\n"
        "   D;JLE // jump if not 0\n";

    const string lt = 
        "(LT)\n"
        "   @SP // go to stack pointer\n"
        "   M=M-1 // decrement value\n"
        "   A=M // go to top of stack\n"
        "   D=M // store value in D\n"
        "   M=0 // clear value\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to next value\n"
        "   D=M-D // subtract\n"
        "   @TRUE // set dest for true\n"
        "   D;JLT // jump if 0\n"
        "   @FALSE // set dest for false\n"
        "   D;JGE // jump if not 0\n";

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
        "   M=M+1 // increment value;\n"
        "   A=M // go to top of stack\n"
        "   M=0 // clear value\n";

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
        "// push the value at pp_val to the stack\n"
        "// (assumes pp_val has been set)\n"
        "(PUSH)\n"  
        "   @pp_val\n"
        "   D=M // store value\n"
        "   @SP\n"
        "   A=M // go to top of stack\n"
        "   M=D // set value\n"
        "   @SP\n"
        "   M=M+1 // incr\n";

    const string pop =
        "// pop from stack to pp_addr\n"
        "// (assumes pp_addr has been set)\n"
        "(POP)\n"
        "   @SP\n"
        "   M=M-1 // decr\n"
        "   A=M // top of stack\n"
        "   D=M // top value\n"
        "   M=0 // clear\n"
        "   @pp_addr\n"
        "   A=M // new address\n"
        "   M=D // set value\n";

    const string ret =
        "   @cur_func\n"
        "   M=M+1 // increment\n"
        "   @MAIN\n"
        "   0;JMP // return control to main\n";

    const string incr =
        "   @line_num\n"
        "   M=M+1 // increment\n";

    const string runCurFunc =
        "   @cur_func\n"
        "   D=M // store value\n"
        "   @line_num\n"
        "   A=M // store value\n"
        "   D=D-A // check to run next func\n";
};