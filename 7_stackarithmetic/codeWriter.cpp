#include "codeWriter.h"

#include <iostream>

codeWriter::codeWriter(string fileName){
    std::cout << "opening " << fileName << " for writing" << std::endl;

    outFile.open(fileName);

    // setup
    string line =
        "// initialize SP to 256\n"
        "@256 // import 256\n"
        "D=A // set D to 256\n"
        "@SP // import SP(0)\n"
        "M=D // set mem to 256\n"
        "\n"
        "// initialize variables\n"
        "@cur_func // current function, NO reset\n"
        "@line_num // line function couter, DOES reset\n"
        "@eq_val // value of equality check\n"
        "@push_val // the pushed value\n"
        "@true\n"
        "M=-1 // set true constant\n"
        "@false\n"
        "M=0 // set false constant\n"
        "\n"
        "@MAIN\n"
        "0;JMP // start program\n";
    outFile << line;

    line = functions::add;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::sub;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::neg;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::eq;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::gt;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::lt;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::and_func;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::or_func;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::not_func;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::push;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;
    line = functions::pop;
    outFile << "\n";
    outFile << line;
    outFile << functions::ret;

    // main function
    line = 
        "\n"
        "// main function loop\n"
        "(MAIN)\n"
        "   @line_num\n"
        "   M=0 // reset line counter\n";
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

    string line = runCurFuncStr();
    outFile << "\n";
    outFile << line;

    if(command.compare("add") == 0){
        line = "   @ADD\n";
    } else if(command.compare("sub") == 0){
        line = "   @SUB\n";
    }else if(command.compare("neg") == 0){
        line = "   @NEG\n";
    }else if(command.compare("eq") == 0){
        line = "   @EQ\n";
    }else if(command.compare("gt") == 0){
        line = "   @GT\n";
    }else if(command.compare("lt") == 0){
        line = "   @LT\n";
    }else if(command.compare("and") == 0){
        line = "   @AND\n";
    }else if(command.compare("or") == 0){
        line = "   @OR\n";
    }else if(command.compare("not") == 0){
        line = "   @NOT\n";
    } else{
        std::cout << "ERROR PARSING ARITHMETIC COMMAND" << std::endl;
        return;
    }

    // write to file
    outFile << line;
    outFile << "   D;JEQ\n";
    outFile << "\n";
    outFile << functions::incr;
}

void codeWriter::writePushPop(commandType command, string segment, int index){
    std::cout << "writing push/pop to " << segment << " " << index << std::endl;

    string line = "";
    outFile << "\n";

    if(command == commandType::C_PUSH 
        && segment.compare("constant") == 0){
            
        string idx = std::to_string(index);
        // push index to stack
        line = 
            "   // import number constant\n"
            "   @";
        line.append(idx);
        line.append(
            "\n"
            "   D=A // store address as value\n"
            "   @push_val\n"
            "   M=D // set value\n"
        );
        line.append("\n");
        line.append(runCurFuncStr());
        line.append("   @PUSH\n");
    } else{
        std::cout << "ERROR WRITING PUSHPOP" << std::endl;
        return;
    }

    outFile << line;
    outFile << "   D;JEQ\n";
    outFile << "\n";
    outFile << functions::incr;
}

void codeWriter::close(){
    // closing loop
    outFile << 
        "\n"
        "   @END\n"
        "   0;JMP // finish \n"
        "\n"
        "(END)\n"
        "   @END\n"
        "   0;JMP\n";

    std::cout << "closing output file" << std::endl;
    outFile.close();
}

string codeWriter::runCurFuncStr(){
    return 
        "   @cur_func\n"
        "   D=M // store value\n"
        "   @line_num\n"
        "   A=M // store value\n"
        "   D=D-A // check to run next func\n";
        // @NEXT_FUNC
        // D;JEQ
}