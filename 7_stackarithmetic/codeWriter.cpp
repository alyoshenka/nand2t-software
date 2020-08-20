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
            "@SP\n"
            "A=A-1\n"
            "M=-M\n";
    }else if(command.compare("eq") == 0){
        // subtract and check if answer is 0
        line = 
            "@SP\n"
            "D=M-1\n"
            "@SP\n"
            "M=M-1\n"
            "@SP\n"
            "A=M-1\n"
            "D=D-A\n"
            "A=-1\n"
            "D;JEQ\n";
            "A=0\n"
            "D;JNE\n"
            "D=A\n"
            "@SP\n"
            "A=A-1\n"
            "M=D\n";
    }else if(command.compare("gt") == 0){
        // subtract, test > 0
        line = 
            "@SP\n"
            "D=M-1\n"
            "@SP\n"
            "M=M-1\n"
            "@SP\n"
            "A=M-1\n"
            "D=D-A\n"
            "A=-1\n"
            "D;JGT\n";
            "A=0\n"
            "D;JLE\n"
            "D=A\n"
            "@SP\n"
            "A=A-1\n"
            "M=D\n";
    }else if(command.compare("lt") == 0){
        // subtract, test < 0
        line = 
            "@SP\n"
            "D=M-1\n"
            "@SP\n"
            "M=M-1\n"
            "@SP\n"
            "A=M-1\n"
            "D=D-A\n"
            "A=-1\n"
            "D;JLT\n";
            "A=0\n"
            "D;JGE\n"
            "D=A\n"
            "@SP\n"
            "A=A-1\n"
            "M=D\n";
    }else if(command.compare("and") == 0){
        line = 
            "@SP\n"
            "A=A-1\n"
            "D=M\n"
            "@SP\n"
            "M=M-1\n"
            "@SP\n"
            "A=A-1\n"
            "M=M&D\n";
    }else if(command.compare("or") == 0){
        line = 
            "@SP\n"
            "A=A-1\n"
            "D=M\n"
            "@SP\n"
            "M=M-1\n"
            "@SP\n"
            "A=A-1\n"
            "M=M|D\n";
    }else if(command.compare("not") == 0){
        line = 
            "@SP\n"
            "A=A-1\n"
            "M=!M\n";
    } else{
        std::cout << "ERROR PARSING ARITHMETIC COMMAND" << std::endl;
        return;
    }

    // write to file
    outFile << line;
}

void codeWriter::writePushPop(commandType command, string segment, int index){
    std::cout << "writing push/pop to " << segment << " " << index << std::endl;

    string line = "";

    if(command == commandType::C_PUSH 
        && segment.compare("constant") == 0){
            
        string idx = std::to_string(index);
        // push index to stack
        line = "@";
        line.append(idx);
        line.append(
            "\n" // import number constant
            "D=A\n" // set register D to number
            "@SP\n" // get stack value as address
            "A=M\n" // go to addres (top of stack)
            "M=D\n" // set top of stack to number
            "@SP\n" // get SP address
            "M=M+1\n" // increment stack pointer
        );
    } else{
        std::cout << "ERROR WRITING PUSHPOP" << std::endl;
        return;
    }

    outFile << line;
}

void codeWriter::close(){
    std::cout << "closing output file" << std::endl;
    outFile.close();
}