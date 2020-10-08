#include "parser.h"

#include <iostream>

parser::parser(string fileName){
    std::cout << "opening " << fileName << " for reading" << std::endl;

    curCmd = "";

    inFile.open(fileName);
    if(!inFile.is_open()){
        std::cout << "error opening " << fileName << std::endl;
    }

    // initialize
    advance();
}

parser::~parser(){
    std::cout << "closing input file" << std::endl;
    inFile.close();
}

bool parser::hasMoreCommands(){
    return !inFile.eof();
}

void parser::advance(){
    getline(inFile, curCmd);

    // ignore comments and empty lines
    if(curCmd[0] == '/' && curCmd[1] == '/'
        || curCmd.empty() && !inFile.eof()){
        advance();
    }

    // strip inline comments
    int com = curCmd.find_first_of('/');
    if(com != string::npos){
        curCmd = curCmd.substr(0, com);
    }
    // strip whitespace
    int start = curCmd.find_first_not_of(whitespace);
    if(start != string::npos){
        curCmd = curCmd.substr(start);
    }
    int end = curCmd.find_last_not_of(whitespace);
    if(end != string::npos){
        curCmd = curCmd.substr(0, end + 1);
    }
}

commandType parser::currentCommand(){
    // get first word
    int end = curCmd.find_first_of(" ");
    string first = curCmd.substr(0, end);
    if(first.compare("push") == 0){
        return commandType::C_PUSH;
    } else if(first.compare("pop") == 0){
        return commandType::C_POP;
    } else if(first.compare("label") == 0){
        return commandType::C_LABEL;
    } else if(first.compare("goto") == 0){
        return commandType::C_GOTO;
    } else if(first.compare("if-goto") == 0){
        return commandType::C_IF;
    } else if(first.compare("function") == 0){
        return commandType::C_FUNCTION;
    } else if(first.compare("call") == 0){
        return commandType::C_CALL;
    } else if(first.compare("return") == 0){
        return commandType::C_RETURN;
    } else {
        // check validity

        return commandType::C_ARITHMETIC;
    }
}

string parser::arg1(){
    int l = curCmd.find_first_of(" ");
    int r = curCmd.find_last_of(" ");
    // if last word
    if(r == string::npos){
        return curCmd.substr(l + 1, curCmd.length() - l);
    }
    // check
    return curCmd.substr(l + 1, r - l - 1);
}

int parser::arg2(){
    int l = curCmd.find_last_of(" ");
    string num = curCmd.substr(l, curCmd.length() - l);
    return std::stoi(num);
}