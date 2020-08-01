#include "parser.h"

#include <iostream>

#include <string>

using std::string;

parser::parser(char* inFile){

    curCmd = "";

    std::cout << "opening file " << inFile << std::endl;

    myFile.open(inFile);
    if(!myFile.is_open()){
        std::cout << "error opening " << inFile << " for reading" << std::endl;
    }
}

parser::~parser(){
    std::cout << "closing file" << std::endl;
    myFile.close();
}

bool parser::hasMoreCommands(){
    return !curCmd.empty();
}

void parser::advance(){
    // try
    getline(myFile, curCmd);
    // catch: curCmd = empty
    return;
}

commandType parser::currentCommand(){
    if(curCmd == "@"){
        return commandType::A_COMMAND;
    }else if (curCmd == "("){
        return commandType::L_COMMAND;
    }else{
        return commandType::C_COMMAND;
    }
}

string parser::symbol(){
    // @100 -> 100
    // (100) -> 100

    string sym = string(curCmd);
    sym.erase(std::remove(sym.begin(), sym.end(), '('), sym.end());
    sym.erase(std::remove(sym.begin(), sym.end(), ')'), sym.end());
    sym.erase(std::remove(sym.begin(), sym.end(), '@'), sym.end());
    return sym;
}

string parser::dest(){
    return "";
}

string parser::comp(){
    if(curCmd.compare("null")){
        return "000";
    }else if(curCmd.compare("M")){
        return "001";
    }else if(curCmd.compare("D")){
        return "010";
    }else if(curCmd.compare("MD")){
        return "011";
    }else if(curCmd.compare("A")){
        return "100";
    }else if(curCmd.compare("AM")){
        return "101";
    }else if(curCmd.compare("AD")){
        return "110";
    }else if(curCmd.compare("AMD")){
        return "111";
    }else{
        return "";
    }
}

string parser::jump(){
    if(curCmd.compare("null")){
        return "000";
    }else if(curCmd.compare("JGT")){
        return "001";
    }else if(curCmd.compare("JEQ")){
        return "010";
    }else if(curCmd.compare("JGE")){
        return "011";
    }else if(curCmd.compare("JLT")){
        return "100";
    }else if(curCmd.compare("JNE")){
        return "101";
    }else if(curCmd.compare("JLE")){
        return "110";
    }else if(curCmd.compare("JMP")){
        return "111";
    }else{
        return "";
    }
}

