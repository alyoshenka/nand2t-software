#include "codeWriter.h"

#include <iostream>

codeWriter::codeWriter(string fileName){
    std::cout << "opening " << fileName << " for writing" << std::endl;

    outFile.open(fileName);

    // initialize SP to 256
    string line =
        "@256\n" // import 256
        "D=A\n" // set D to 256
        "@SP\n" // import SP(0)
        "M=D\n"; // set mem to 256
    outFile << line;

    // eq function
    // subtract and check if answer is 0
        line = 
            "\n// EQ\n\n"

            "// equality compare value\n"
            "@eq_val // setup\n"
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
            "(BEFORE_EQ)\n"
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
        outFile << line;
}

codeWriter::~codeWriter(){
    close();
}

void codeWriter::setFileName(string fileName){
    std::cout << "now parsing " << fileName << std::endl;
}

void codeWriter::writeArithmetic(string command){
    std::cout << "writing " << command << std::endl;

    string line = "";

    if(command.compare("add") == 0){
        line = 
            "@SP\n" // go to stack pointer
            "M=M-1\n" // decrement stack
            "A=M\n" // go to top of stack
            "D=M\n" // store top value
            "A=A-1\n" // get address of next value
            "D=D+M\n" // add
            "M=D\n" // store
            "A=A+1\n" // get top value
            "M=0\n"; // clear
    } else if(command.compare("sub") == 0){
        line = 
            "@SP\n" // go to stack pointer
            "M=M-1\n" // decrement stack
            "A=M\n" // go to top of stack
            "D=M\n" // store top value
            "A=A-1\n" // get address of next value
            "D=D-M\n" // sub
            "M=D\n" // store
            "A=A+1\n" // get top value
            "M=0\n"; // clear
    }else if(command.compare("neg") == 0){
        line = 
            "@SP\n" // go to stack pointer
            "A=M-1\n" // go to top value of stack
            "M=-M\n"; // negate value
    }else if(command.compare("eq") == 0){
        line = 
            "@BEFORE_EQ // equality check function\n"
            "0;JMP\n";
    }else if(command.compare("gt") == 0){
        // subtract, test > 0
        line = "\n";
    }else if(command.compare("lt") == 0){
        // subtract, test < 0
        line = "\n";
    }else if(command.compare("and") == 0){
        line = 
            "@SP\n" // go to stack pointer
            "M=M-1\n" // decrement value to get first number
            "A=M\n" // go to stack
            "D=M\n" // store first number
            "@SP\n" // go to stack pointer
            "M=M-1\n" // decrement value
            "@SP\n" // go to stack pointer
            "A=M\n" // go to stack
            "M=M&D\n" // calculate value
            "@SP\n" // go to stack pointer
            "M=M+1\n"; // increment value
    }else if(command.compare("or") == 0){
        line = 
            "@SP\n" // go to stack pointer
            "M=M-1\n" // decrement value to get first number
            "A=M\n" // go to stack
            "D=M\n" // store first number
            "@SP\n" // go to stack pointer
            "M=M-1\n" // decrement value
            "@SP\n" // go to stack pointer
            "A=M\n" // go to stack
            "M=M|D\n" // calculate value
            "@SP\n" // go to stack pointer
            "M=M+1\n"; // increment value
    }else if(command.compare("not") == 0){
        line = 
            "@SP\n" // go to stack pointer
            "A=M-1\n" // go to top value of stack
            "M=!M\n"; // bitwise negation
    } else{
        std::cout << "ERROR PARSING ARITHMETIC COMMAND" << std::endl;
        return;
    }

    // write to file
    outFile << "\n";
    outFile << line;
}

void codeWriter::writePushPop(commandType command, string segment, int index){
    std::cout << "writing push/pop to " << segment << " " << index << std::endl;

    string line = "";

    if(command == commandType::C_PUSH 
        && segment.compare("constant") == 0){
            
        string idx = std::to_string(index);
        // push index to stack
        line = 
            "// import number constant\n"
            "@";
        line.append(idx);
        line.append( 
            "\n"          
            "D=A // set register D to number\n"
            "@SP // get stack value as address\n"
            "A=M // go to addres (top of stack)\n"
            "M=D // set top of stack to number\n"
            "@SP // get SP address\n"
            "M=M+1 // increment stack pointer\n"
        );
    } else{
        std::cout << "ERROR WRITING PUSHPOP" << std::endl;
        return;
    }

    outFile << "\n";
    outFile << line;
}

void codeWriter::close(){
    // closing loop
    outFile << 
        "(END)\n"
        "   @END\n"
        "   0;JMP\n";

    std::cout << "closing output file" << std::endl;
    outFile.close();
}