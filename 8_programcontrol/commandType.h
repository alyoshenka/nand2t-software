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
        "// Add\n"
        "   @SP\n"
        "   M=M-1 // decr\n"
        "   A=M // top value\n"
        "   D=M\n"
        "   A=A-1\n"
        "   M=M+D\n";

    const string sub = 
        "// Sub\n"
        "   @SP\n"
        "   M=M-1 // decr\n"
        "   A=M // top value\n"
        "   D=M\n"
        "   A=A-1\n"
        "   M=M-D\n"; // might need to switch

    const string neg = 
        "// Neg\n"
        "   @SP // go to stack pointer\n"
        "   A=M-1 // go to top value of stack\n"
        "   M=-M // negate value\n";

    const string eq_sub = 
        "   // sub\n"
        "   @SP\n"
        "   M=M-1 // decr\n"
        "   A=M\n"
        "   D=M // top value\n"
        "   A=A-1\n"
        "   MD=M-D // sub, result in MD\n";

    const string eq =  
        eq_sub +        
        "   // check against 0\n"
        "   @SET_TRUE\n"
        "   D;JEQ\n"
        "   @SET_FALSE\n"
        "   D;JNE\n";

    const string gt = 
        eq_sub + 
        "   // check against 0\n"
        "   @SET_TRUE\n"
        "   D;JGT\n"
        "   @SET_FALSE\n"
        "   D;JLE\n";

    const string lt = 
        eq_sub + 
        "   // check against 0\n"
        "   @SET_TRUE\n"
        "   D;JLT\n"
        "   @SET_FALSE\n"
        "   D;JGE\n";

    const string and_func = 
        "// And\n"
        "   @SP\n"
        "   M=M-1 // decr\n"
        "   A=M // top value\n"
        "   D=M\n"
        "   A=A-1\n"
        "   M=M&D\n";

    const string or_func = 
        "// Or\n"
        "   @SP\n"
        "   M=M-1 // decr\n"
        "   A=M // top value\n"
        "   D=M\n"
        "   A=A-1\n"
        "   M=M|D\n";

    const string not_func = 
        "// Not\n"
        "   @SP\n"
        "   A=M-1\n"
        "   M=!M\n";

    const string setup =
        "// initialize variables\n"
        "   @eq_val // value of equality check\n"
        "   @cmp_addr // address to return to after comparing\n"
        "   @true\n"
        "   M=-1 // set true constant\n"
        "   @false\n"
        "   M=0 // set false constant\n"
        "   @frame // frame variable\n"
        "   @current_return\n"
        "\n"
        "@MAIN\n"
        "0;JMP\n"
        "\n"
        "(SET_TRUE)\n"
        "   @true\n"
        "   D=M\n"
        "   @eq_val\n"
        "   M=D\n"
        "   @RETURN_EQ\n"
        "   0;JMP\n"
        "\n"
        "(SET_FALSE)\n"
        "   @false\n"
        "   D=M\n"
        "   @eq_val\n"
        "   M=D\n"
        "   @RETURN_EQ\n"
        "   0;JMP\n"
        "\n"
        "(RETURN_EQ)\n"
        "   @eq_val\n"
        "   D=M\n"
        "   @SP\n"
        "   A=M-1\n"
        "   M=D\n"
        "   @cmp_addr\n"
        "   A=M\n"
        "   0;JMP\n"
        "\n"
        "(MAIN)\n";
};