#include "codeWriter.h"

#include <iostream>

codeWriter::codeWriter(const string file){
   cmpCnt = 0;

    fileName = std::string(file);
    std::cout << "opening " << fileName << " for writing" << std::endl;

    outFile.open(fileName);

    int left = file.find_last_of("/") + 1;
    int right = file.find_last_of(".");
    fileName = fileName.substr(0, right);
    fileName = fileName.substr(left, right - left);

    // setup
    string line = functions::setup;       
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

    string line = "\n";
    outFile << line;

    if(command.compare("add") == 0){ 
        line = functions::add;
    } 
    else if(command.compare("sub") == 0){
        line = functions::sub;
    }
    else if(command.compare("neg") == 0){
        line = functions::neg;
    }
    else if(command.compare("eq") == 0){
        cmpCnt++;
        line = 
            "// Eq\n"
            "   @cmp";
        line.append(std::to_string(cmpCnt));
        line.append(
            "\n"
            "   D=A\n"
            "   @cmp_addr\n"
            "   M=D // save return address\n"
        );
        line.append(functions::eq);
        line.append("   (cmp");
        line.append(std::to_string(cmpCnt));
        line.append(")\n");
    }
    else if(command.compare("gt") == 0){
        cmpCnt++;
        line = "   @cmp";
        line.append(std::to_string(cmpCnt));
        line.append(
            "\n"
            "   D=A\n"
            "   @cmp_addr\n"
            "   M=D // save return address\n"
        );
        line.append(functions::gt);
        line.append("   (cmp");
        line.append(std::to_string(cmpCnt));
        line.append(")\n");
    }
    else if(command.compare("lt") == 0){
        cmpCnt++;
        line = "   @cmp";
        line.append(std::to_string(cmpCnt));
        line.append(
            "\n"
            "   D=A\n"
            "   @cmp_addr\n"
            "   M=D // save return address\n"
        );
        line.append(functions::lt);
        line.append("   (cmp");
        line.append(std::to_string(cmpCnt));
        line.append(")\n");
    }
    else if(command.compare("and") == 0){
        line = functions::and_func;
    }
    else if(command.compare("or") == 0){
        line = functions::or_func;
    }
    else if(command.compare("not") == 0){
        line = functions::not_func;
    } 
    else{
        std::cout << "ERROR PARSING ARITHMETIC COMMAND: " << command << std::endl;
        return;
    }

    // write to file
    outFile << line;
}

void codeWriter::writePushPop(commandType command, string segment, int index){
    string line = "";
    outFile << "\n";

    if(command == commandType::C_PUSH){
        std::cout << "writing push from " << segment << " " << index << std::endl;

        if(segment.compare("constant") == 0){
            line = 
                "// import number constant\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   D=A\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );
        } 
        else if(segment.compare("temp") == 0){
            assert(index <= 7);
            line = 
                "// push from temp (R5)\n"
                "   @R";
            line.append(std::to_string(5+index));
            line.append(
                "\n"
                "   D=M\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );
        } 
        else if(segment.compare("pointer") == 0){
            assert(index <= 1);
            line = 
                "// push from pointer (R3)\n"
                "   @R";
            line.append(std::to_string(3+index));
            line.append(
                "\n"
                "   D=M\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );
        } 
        else if(segment.compare("static") == 0){
            line =
                "// static\n"
                "   @";
            line.append(fileName.substr(fileName.find_last_of('\\')+1));
            line.append(".");
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   D=M\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );
        } 
        else if(segment.compare("local") == 0){
            line = 
                "// local\n"
                "   @LCL\n"
                "   D=M\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   A=A+D\n"
                "   D=M\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );
        } 
        else if(segment.compare("argument") == 0){
            line = 
                "// argument\n"
                "   @ARG\n"
                "   D=M\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   A=A+D\n"
                "   D=M\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );   
        } 
        else if(segment.compare("this") == 0){
            line = 
                "// this\n"
                "   @THIS\n"
                "   D=M\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   A=A+D\n"
                "   D=M\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );
        } 
        else if(segment.compare("that") == 0){
            line = 
                "// that\n"
                "   @THAT\n"
                "   D=M\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   A=A+D\n"
                "   D=M\n"
                "   @SP\n"
                "   A=M\n"
                "   M=D\n"
                "   @SP\n"
                "   M=M+1\n"
            );
        }
        else{
            std::cout << "INVALID SEGMENT: " << segment << std::endl;
            return;
        }
    } 
    else if (command == commandType::C_POP){
        std::cout << "writing pop to " << segment << " " << index << std::endl;
        
        if(segment.compare("local") == 0){
            line =
                "// pop to local\n"
                "   @LCL\n"
                "   D=M // base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   D=D+A\n"
                "   @R13\n"
                "   M=D\n"
                "   @SP\n"
                "   AM=M-1\n"
                "   D=M\n"
                "   @R13\n"
                "   A=M\n"
                "   M=D // set\n"
            );
        } 
        else if(segment.compare("argument") == 0){
            line =
                "// pop to arg\n"
                "   @ARG\n"
                "   D=M // base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   D=D+A\n"
                "   @R13\n"
                "   M=D\n"
                "   @SP\n"
                "   AM=M-1\n"
                "   D=M\n"
                "   @R13\n"
                "   A=M\n"
                "   M=D // set\n"
            );
        } 
        else if(segment.compare("this") == 0){
            line =
                "// pop to this\n"
                "   @THIS\n"
                "   D=M // base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   D=D+A\n"
                "   @R13\n"
                "   M=D\n"
                "   @SP\n"
                "   AM=M-1\n"
                "   D=M\n"
                "   @R13\n"
                "   A=M\n"
                "   M=D // set\n"
            );
        } 
        else if(segment.compare("that") == 0){
            line =
                "// pop to that\n"
                "   @THAT\n"
                "   D=M // base\n"
                "   @";
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   D=D+A\n"
                "   @R13\n"
                "   M=D\n"
                "   @SP\n"
                "   AM=M-1\n"
                "   D=M\n"
                "   @R13\n"
                "   A=M\n"
                "   M=D // set\n"
            );
        } 
        else if(segment.compare("temp") == 0){
            assert(index <= 7);           
            line =
                "// pop to temp(R5)\n"
                "   @SP\n"               
                "   AM=M-1\n"
                "   D=M\n"
                "   @R";
            line.append(std::to_string(5+index));
            line.append(
                "\n"
                "   M=D\n"
            );
        } 
        else if(segment.compare("pointer") == 0){
            assert(index <= 1);           
            line =
                "// pop to pointer(R3)\n"
                "   @SP\n"               
                "   AM=M-1\n"
                "   D=M\n"
                "   @R";
            line.append(std::to_string(3+index));
            line.append(
                "\n"
                "   M=D\n"
            );
        } 
        else if(segment.compare("static") == 0){           
            line =
                "// pop to static\n"
                "   @SP\n"               
                "   AM=M-1\n"
                "   D=M\n"
                "   @";
            line.append(fileName.substr(fileName.find_last_of('\\') +1));
            line.append(".");
            line.append(std::to_string(index));
            line.append(
                "\n"
                "   M=D\n"
            );
        } 
        else{
            std::cout << "INVALID SEGMENT: " << segment << std::endl;
            return;
        }
    } 
    else {
        std::cout << "INVALID COMMANDTYPE: " << command << std::endl;
        return;
    }

    outFile << line;
}

void codeWriter::close(){
    outFile << "\n(END)\n";
    outFile << "@END\n";
    outFile << "0;JMP\n";
    std::cout << "closing output file" << std::endl;
    outFile.close();
}

void codeWriter::writeInit(){
    std::cout << "writing init" << std::endl;
    outFile <<
        "// initialize global stack\n"
        "@256\n"
        "D=A\n"
        "@SP\n"
        "M=D\n"
        "// call sys.init";
        // more?
}

void codeWriter::writeLabel(string label){
    std::cout << "writing label " << label << std::endl;

    outFile << "(" << label << ")\n";
}

void codeWriter::writeGoto(string label){
    std::cout << "writing goto " << label << std::endl;

    outFile << "@" << label << "\n";
    outFile << "0;JMP\n";
}

void codeWriter::writeIf(string label){
    std::cout << "writing if-goto " << label << std::endl;

    outFile << "// if-goto " << label << "\n";
    outFile <<
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@";
    outFile << label << "\n";
    outFile << "D;JNE\n";
}

void codeWriter::writeCall(string func, int args){
    std::cout << "writing call: " << func << " " << args << std::endl;

    string retAddr = "";

    outFile << "// push return address, using label below\n";
    outFile << "@" << retAddr << "\n";
    outFile <<
        "D=A\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    outFile << "// save LCL, ARG, THIS, THAT\n";
    outFile << 
        "@LCL\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@ARG\n"
        "D=M\n"
        "@SP\n"
        "AM=M+1\n"
        "M=D\n"
        "@THIS\n"
        "D=M\n"
        "@SP\n"
        "AM=M+1\n"  
        "M=D\n"
        "@THAT\n"
        "D=M\n"
        "@SP\n"
        "AM=M+1\n" 
        "@SP\n"
        "M=M+1\n";

    outFile << "// reposition ARG, LCL\n";
    outFile << "// arg=sp-n-5\n";
    outFile << "@" << args - 5 << "\n";
    outFile <<
        "D=A\n"
        "@SP\n"
        "D=A-D\n"
        "@ARG\n"
        "M=D\n";
    outFile << "// lcl=sp\n";
    outFile <<
        "@SP\n"
        "D=M\n"
        "@LCL\n"
        "M=D\n";

    outFile << "// transfer control\n";
    outFile << "@" << func << "\n";
    outFile << "0;JMP\n";

    outFile << "// label return address\n";
    outFile << "(" << func << ")\n";
}

void codeWriter::writeReturn(){
    std::cout << "writing return" << std::endl;

    outFile << "// frame = r14\n";
    outFile << 
        "@LCL\n"
        "D=M\n"
        "@R14 // lcl\n"
        "M=D\n";

    outFile << "// ret = *(lcl-5)\n";
    outFile << 
        "@5\n"
        "D=A\n"
        "@R14\n"
        "D=M-D\n"
        "@R15 // ret\n"
        "M=D\n";

    outFile << "// *arg=pop()\n";
    outFile <<
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@ARG\n"
        "A=M\n"
        "M=D\n";

    outFile << "// sp=arg+1\n";
    outFile <<
        "@ARG\n"
        "D=A+1\n"
        "@SP\n"
        "M=D\n";

    outFile << "// that=*(frame-1)\n";
    outFile << 
        "@R14\n"
        "D=A-1\n"
        "@THAT\n"
        "M=D\n";

    outFile << "// this=*(frame-2)\n";
    outFile <<
        "@2\n"
        "D=A\n"
        "@R14\n"
        "D=M-D\n"
        "@THIS\n"
        "M=D\n";

    outFile << "// arg=*(frame-3)\n";
    outFile <<
        "@3\n"
        "D=A\n"
        "@R14\n"
        "D=M-D\n"
        "@ARG\n"
        "M=D\n";

    outFile << "// lcl=*(frame-4)\n";
    outFile <<
        "@4\n"
        "D=A\n"
        "@R14\n"
        "D=M-D\n"
        "@LCL\n"
        "M=D\n";

    outFile << "// goto ret\n";
    outFile <<
        "@R15\n"
        "M;JMP";
}

void codeWriter::writeFunction(string func, int args){
    std::cout << "writing func: " << func << " " << args << std::endl;

    outFile << "// label function entry\n";
    outFile << "(" << func << ")\n";

    outFile << "    // repeat " << args << "times\n";
    outFile << "    // initialze args to 0 (push to stack\n";
    for(int i = 0; i < args; i++){
        outFile << 
            "   @SP\n"
            "   A=M\n"
            "   M=0\n"
            "   @SP\n"
            "   M=M+1\n";
    }
}