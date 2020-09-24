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
        // set pp_val to segment[index]

        if(segment.compare("constant") == 0){
            line = "   @";
            line.append(std::to_string(index));
            line.append(
                " // import number constant\n"
                "   D=A\n"
                "   @pp_val\n"
                "   M=D // set\n"
            );
        } else if(segment.compare("temp") == 0){
            line =
                "   @R5\n"
                "   D=A // store address\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                " // import index\n"
                "   A=D+A // offset from base\n"
                "   D=M // save val\n"
                "   @pp_val\n"
                "   M=D // set val\n"
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
                "   @pp_val\n"
                "   M=D // set val\n"
            );
        } else if(segment.compare("static") == 0){
            line = "   @";
            line.append(getFileName());
            line.append(".");
            line.append(std::to_string(index));
            line.append(    
                "\n"
                "   D=M\n"
                "   @pp_val\n"
                "   M=D // set value\n"
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
                "   @pp_val\n"
                "   M=D // set val\n"
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
                "   @pp_val\n"
                "   M=D // set val\n"
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
                "   @pp_val\n"
                "   M=D // set val\n"
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
                "   @pp_val\n"
                "   M=D // set val\n"
            );
        } else{
            std::cout << "INVALID SEGMENT: " << segment << std::endl;
            return;
        }
        line.append(functions::runCurFunc);
        line.append("   @PUSH\n");

    } else if (command == commandType::C_POP){
        std::cout << "writing pop to " << segment << " " << index << std::endl;
        // set pp_addr to segment + index
        if(segment.compare("local") == 0){
            line = "   @LCL\n";
        } else if(segment.compare("argument") == 0){
            line = "    @ARG\n";
        } else if(segment.compare("this") == 0){
            line = "    @THIS\n";
        } else if(segment.compare("that") == 0){
            line = "    @THAT\n";
        } else if(segment.compare("temp") == 0){
            line =
                "   @R5\n"
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