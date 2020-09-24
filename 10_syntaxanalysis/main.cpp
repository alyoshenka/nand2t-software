
// 1. create a JackTokenizer from the xxx.jack input file
// 2. create and output file called xxx.xml
//      and prepare it for writing
// 3. use the CompilationEngine to compile the input
//      JackTokenizer into the output file

#include <iostream>
#include <string>

#include "jackTokenizer.h"
#include "compilationEngineXML.h"

using std::string;

#include <fstream>
using std::ifstream;

/** Is the given string a valid .jack file? */
bool isJackFile(string inFile){
    return inFile.substr(inFile.length() - 5, 5).compare(".jack") == 0;
}

/** Compiles an individual .jack file. */
void compileFile(string fileName){  
    string outFile = (fileName.substr(0, fileName.length() - 5)).append("_out.xml");
    std::cout << "opening " << fileName << " for reading" << std::endl;
    std::cout << "opening " << outFile << " for writing" << std::endl;
    
    jackTokenizer* tokenizer = new jackTokenizer(fileName);
    compilationEngineXML compEng(tokenizer, outFile);

    /*
    while(tokenizer->hasMoreTokens()){
        tokenizer->advance();
        tokenizer->tokenType();
    }
    */
}

/** Main application method, takes cli input. */
int main(int cnt, char* args[]){

    // if no argument specified
    if(cnt < 2){
        std::cout << "no input file/directory specified" << std::endl;
        return -1;
    }
    // if > 1 argument given
    if(cnt > 2){
        std::cout << "too many arguments given" << std::endl;
    }
    // get cli input
    string inFile = string(args[1]);

    // if file
    if(isJackFile(inFile)){
        compileFile(inFile);
    } else{ // else dir
        // for all .jack files inFile/
        //      compileFile(filename.jack);
    }

    return 0;
}