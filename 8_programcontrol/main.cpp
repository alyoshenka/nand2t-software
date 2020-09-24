#include <iostream>
#include <string>

#include "parser.h"
#include "codeWriter.h"

using std::string;

using std::cout;
using std::endl;

// .vm file extention?
bool vmFile(string fileName){
    return fileName.substr(fileName.length() - 3, 3).compare(".vm") == 0;
}

// change .vm filename to .asm
string inFileToOutFile(string inFile){
    string outFile = inFile.substr(0, inFile.length() - 3);
    outFile.append(".asm");
    return outFile;
}

int main(int cnt, char* args[]){

    // if no argument specified
    if(cnt < 2){
        cout << "no input file/directory specified" << endl;
        return -1;
    }
    // if > 1 argument given
    if(cnt > 2){
        cout << "too many arguments given" << endl;
        return -2;
    }

    // get cli input
    string inFile = string(args[1]); 

    // if file
    if(vmFile(inFile)){
        cout << "file" << endl;

        parser p(inFile);
        codeWriter cw(inFileToOutFile(inFile));

        while(p.hasMoreCommands()){
            commandType t = p.currentCommand();
            if(t != commandType::C_RETURN){
                string arg1 = p.arg1();
                // 3 arguments
                if(t == commandType::C_PUSH 
                    || t == commandType::C_POP
                    || t == commandType::C_FUNCTION
                    || t == commandType::C_CALL){
                    
                    int arg2 = p.arg2();
                    
                    if(t == commandType::C_PUSH
                        || t == commandType::C_POP){
                        
                        cw.writePushPop(t, arg1, arg2);
                    }else if(t == commandType::C_CALL){
                        cw.writeCall(arg1, arg2);
                    } else if(t == commandType::C_FUNCTION){
                        cw.writeFunction(arg1, arg2);
                    } else {
                        std::cout << "ERROR WRITING 2 ARGS" << std::endl;
                    }
                }else{
                    if(t == commandType::C_ARITHMETIC){
                        cw.writeArithmetic(arg1);
                    } else if(t == commandType::C_GOTO){
                        cw.writeGoto(arg1);
                    } else if(t == commandType::C_IF){
                        cw.writeIf(arg1);
                    } else if(t == commandType::C_LABEL){
                        cw.writeLabel(arg1);
                    } else {
                        std::cout << "ERROR WRITING 1 ARG" << std::endl;
                    }
                }
            } else{
                if(t == commandType::C_RETURN){
                    cw.writeReturn();
                } else{
                    std::cout << "ERROR WRITING 0 ARGS" << std::endl;
                }
            }

            p.advance();
        }
    } else { // else dir
        cout << "dir" << endl;
        // iterate over all files in dir
        // if isVMFile
            // new parser to handle
    }

    return 0;
}