#include "codeWriter.h"

#include <iostream>

codeWriter::codeWriter(const string file){
    fileName = std::string(file);
    std::cout << "opening " << fileName << " for writing" << std::endl;

    outFile.open(fileName);

    int left = file.find_last_of("/") + 1;
    int right = file.find_last_of(".");
    fileName = fileName.substr(0, right);
    fileName = fileName.substr(left, right - left);

    // setup
    string line =
        "// initialize SP to 256\n"
        "@256 // import 256\n"
        "D=A // set D to 256\n"
        "@SP // import SP(0)\n"
        "M=D // set mem to 256\n"
        "// VM segment allocation\n"
        "// Local\n"
        "@300\n"
        "D=A\n"
        "@LCL\n"
        "M=D\n"
        "// Argument\n"
        "@400\n"
        "D=A\n"
        "@ARG\n"
        "M=D\n"
        "// This\n"
        "@3000\n"
        "D=A\n"
        "@THIS\n"
        "M=D\n"
        "// That\n"
        "@3010\n"
        "D=A\n"
        "@THAT\n"
        "M=D\n"
        "\n"
        "// initialize variables\n"
        "@cur_func // current function, NO reset\n"
        "@line_num // line function couter, DOES reset\n"
        "@eq_val // value of equality check\n"
        "@pp_val // the pushed/popped value\n"
        "@pp_addr // the address of the pushed/popped value\n"
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

string codeWriter::getFileName(){
    return fileName;
}

void codeWriter::setFileName(string fileName){
    std::cout << "now parsing " << fileName << std::endl;
}

void codeWriter::writeArithmetic(string command){
    std::cout << "writing " << command << std::endl;

    string line = functions::runCurFunc;
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
    string line = "";
    outFile << "\n";

    if(command == commandType::C_PUSH){
        std::cout << "writing push from " << segment << " " << index << std::endl;
        
        if(segment.compare("constant") == 0){
            line = "    @";
            line.append(std::to_string(index));
            line.append(
                " // import number constant\n"
                "   D=A // save\n"
            );
        } else if(segment.compare("temp") == 0){
            line =
                "   @R5 // temp location\n"
                "   D=A // store address\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "   // import index\n"
                "   A=D+A // offset from base\n"
                "   D=M // save val\n"
            );
        } else if(segment.compare("pointer") == 0){
            line =
                "   @THIS\n"
                "   D=A // store address\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                " // import index\n"
                "   A=D+A // offset from base\n"
                "   D=M // save val\n"
            );
        } else if(segment.compare("static") == 0){
            line = "   @";
            line.append(getFileName());
            line.append(".");
            line.append(std::to_string(index));
            line.append(    
                "\n"
                "   D=M\n"
            );
        } else if(segment.compare("local") == 0){
            line =
                "   @LCL\n"
                "   D=M // store argument base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                " // import index\n"
                "   A=D+A // offset from base\n"
                "   D=M // save val\n"
            );
        } else if(segment.compare("argument") == 0){
            line =
                "   @ARG\n"
                "   D=M // store argument base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                " // import index\n"
                "   A=D+A // offset from base\n"
                "   D=M // save val\n"
            );
        } else if(segment.compare("this") == 0){
            line =
                "   @THIS\n"
                "   D=M // store argument base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                " // import index\n"
                "   A=D+A // offset from base\n"
                "   D=M // save val\n"
            );
        } else if(segment.compare("that") == 0){
            line =
                "   @THAT\n"
                "   D=M // store argument base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                " // import index\n"
                "   A=D+A // offset from base\n"
                "   D=M // save val\n"
            );
        } else{
            std::cout << "INVALID SEGMENT: " << segment << std::endl;
            return;
        }
        
        line.append(
            "   @SP\n"
            "   A=M // get address\n"
            "   M=D // set value\n"
            "   @SP\n"
            "   M=M+1 // incr\n"
        );

    } else if (command == commandType::C_POP){
        std::cout << "writing pop to " << segment << " " << index << std::endl;
        
        // START HERE
        // i'm just not gonna fucking do it

        if(segment.compare("local") == 0){
            line = "   @LCL\n";
        } else if(segment.compare("argument") == 0){
            line = "    @ARG\n";
        } else if(segment.compare("this") == 0){
            line = "    @THIS\n";
        } else if(segment.compare("that") == 0){
            line = "    @THAT\n";
        } else if(segment.compare("temp") == 0){
            line = "   @R5\n";
        } else if(segment.compare("pointer") == 0){
            line =
                "   @THIS\n"
                "   D=A\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                " // import number constant\n"
                "   D=D+A // add offset\n"
                "   @pp_addr\n"
                "   M=D // set value\n"
            );
            line.append(functions::runCurFunc);
            line.append("   @POP\n");
        } else if(segment.compare("static") == 0){
            line = "   @";
            line.append(fileName);
            line.append(".");
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   D=A\n"
                "   @pp_addr\n"
                "   M=D\n"
            );
            line.append(functions::runCurFunc);
            line.append("   @POP\n");
        } else{
            std::cout << "INVALID SEGMENT: " << segment << std::endl;
            return;
        }

        if(segment.compare("temp") != 0
            && segment.compare("pointer") != 0
            && segment.compare("static") != 0){
            line.append(
                "   D=M // base of segment\n"
                "   @"
            );
            line.append(std::to_string(index));
            line.append(
                " // import index\n"
                "   D=D+A // calc RAM address\n"
                "   @pp_addr\n"
                "   M=D // set address\n"
            );
            line.append(functions::runCurFunc);
            line.append("   @POP\n");
        }

    } else {
        std::cout << "INVALID COMMANDTYPE: " << command << std::endl;
        return;
    }

    outFile << line;
    outFile << "\n";
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

void codeWriter::writeInit(){
    std::cout << "writing init" << std::endl;

    outFile << 
        "@256\n"
        "D=A\n"
        "@SP\n"
        "M=D\n"
        "@sys.init\n"
        "0;JMP\n";

    // BAD
}

void codeWriter::writeLabel(string label){
    std::cout << "writing label " << label << std::endl;

    outFile << "\n(";
    outFile << label;
    outFile << ")\n";

    // MORE
}

void codeWriter::writeGoto(string label){
    std::cout << "writing goto " << label << std::endl;

    outFile <<
        "   // goto label\n"
        "   @";
    outFile << label;
    outFile <<
        "\n";
        "   0;JMP";
}

void codeWriter::writeIf(string label){
    std::cout << "writing if-goto " << label << std::endl;

    outFile <<
        "\n   // if-goto label\n"
        "   @SP\n"
        "   A=M-1\n"
        "   D=M // top value\n"
        "   @";
    outFile << label;
    outFile <<
        "\n"
        "   D;JNE";
}

void codeWriter::writeCall(string label, int numArgs){
    std::cout << "writing call " << label << " " << numArgs << std::endl;

    outFile << "// call function {label} after {numLocals} ";
    outFile << "arguments have been pushed to the stack\n";

    // return address
    string ret = std::string(label);
    ret.append("-return-address");

    outFile << 
        "   // ret-addr = SP - numArgs\n"
        "   @SP\n"
        "   D=M\n"
        "   @";
    outFile << numArgs;
    outFile << 
        "   // import numArgs\n"
        "   D=D-A // calc\n"
        "   @";
    outFile << ret;
    outFile <<
        "   M=D // set\n";
        "   // push return address\n"
        "   D=A // save return address address\n" // ???
        "   @SP\n"
        "   A=M\n"
        "   M=D // push ret addr"
        "   @SP\n"
        "   M=M+1 // incr/n";
    outFile << "// save state\n";
    {
    outFile << "//      push LCL\n";
    outFile << 
        "   @LCL\n"
        "   D=M\n"
        "   @SP\n"
        "   A=M\n"
        "   M=D // set SP to LCL\n"
        "   @SP\n"
        "   M=M+1 // incr/n";
    outFile << "//      push ARG\n";
    outFile << 
        "   @ARG\n"
        "   D=M\n"
        "   @SP\n"
        "   A=M\n"
        "   M=D // set SP to ARG\n"
        "   @SP\n"
        "   M=M+1 // incr/n";
    outFile << "//      push THIS\n";
    outFile << 
        "   @THIS\n"
        "   D=M\n"
        "   @SP\n"
        "   A=M\n"
        "   M=D // set SP to THIS\n"
        "   @SP\n"
        "   M=M+1 // incr/n";
    outFile << "//      push THAT\n";
    outFile << 
        "   @THAT\n"
        "   D=M\n"
        "   @SP\n"
        "   A=M\n"
        "   M=D // set SP to THAT\n"
        "   @SP\n"
        "   M=M+1 // incr/n";
    }   
    
    outFile << "// setup for function\n";
    {
    outFile << 
        "//      reposition ARG\n"
        "// arg = sp - n - 5\n"
        "   @SP\n"
        "   D=M // store address\n"
        "   @";
    outFile << numArgs;
    outFile << 
        "   // import numArgs\n"
        "   D=D-A // SP - n\n"
        "   @5 // import constant offset\n"
        "   D=D-A // SP - n - 5\n"
        "   @ARG\n"
        "   M=D // set\n";
    outFile << 
        "//      reposition LCL\n"
        "//      LCL = SP"
        "   @SP\n"
        "   A=M-1 // top value\n"
        "   D=M // store value\n"
        "   @LCL\n"
        "   M=D // set value\n";
    }  
    
    outFile << "   // transfer control\n";
    writeGoto(label);

    outFile << "// declare label for return address\n";
    outFile << "(" << ret << ")\n";
}

void codeWriter::writeReturn(){ 
    std::cout << "writing return" << std::endl;

    outFile <<
        "   // *ARG = pop()\n"
        "   @SP\n"
        "   A=M-1 // top val\n"
        "   D=M // store\n"
        "   @ARG\n"
        "   A=M // *\n"
        "   M=D // set\n"
        "   @SP\n"
        "   M=M-1 // decr\n";
    outFile <<
        "   // SP = ARG + 1\n"
        "   @ARG\n"
        "   D=M\n"
        "   D=D+1\n"
        "   @SP\n"
        "   M=D\n";
    outFile <<
        "   // THAT = *(LCL - 1)\n"
        "   @LCL\n"
        "   D=M\n"
        "   @1 // import offset\n"
        "   D=D-A\n"
        "   @THAT\n"
        "   M=D\n";
    outFile <<
        "   // THIS = *(LCL - 2)\n"
        "   @LCL\n"
        "   D=M\n"
        "   @2 // import offset\n"
        "   D=D-A\n"
        "   @THIS\n"
        "   M=D\n";
    outFile <<
        "   // ARG = *(LCL - 3)\n"
        "   @LCL\n"
        "   D=M\n"
        "   @3 // import offset\n"
        "   D=D-A\n"
        "   @ARG\n"
        "   M=D\n";
    outFile <<
        "   // LCL = *(LCL - 4)\n"
        "   @LCL\n"
        "   D=M\n"
        "   @4 // import offset\n"
        "   D=D-A\n"
        "   @LCL\n"
        "   M=D\n";
    outFile <<
        "   // goto LCL\n"
        "   @LCL\n"
        "   D=A // addr of LCL\n"
        "   @5 // import constant\n"
        "   A=D-A // sub\n"
        "   0;JMP // goto\n";
}

void codeWriter::writeFunction(string label, int numLocals){
    std::cout << "writing function " << label << " " << numLocals << std::endl;

    outFile <<
        "// declare function label\n"
        "(";
    outFile << label;
    outFile <<
        ")\n"
        "   // initialize all local variables to 0\n";
    for(int i = 0; i < numLocals; i++){
        outFile <<
            "   @SP\n"
            "   A=M\n"
            "   M=0 // push 0\n"
            "   @SP\n"
            "   M=M+1 // incr";
    }
}