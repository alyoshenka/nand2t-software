#include "parser.h"

#include <iostream>

#include <algorithm>
#include <string>

using std::string;

parser::parser(char* fileName){

    curCmd = "";

    std::cout << "opening file " << fileName << " for reading" << std::endl;

    inFile.open(fileName);
    if(!inFile.is_open()){
        std::cout << "error opening " << fileName << " for reading" << std::endl;
    }

    string newName(fileName);
    int dotIdx = newName.find('.');
    newName.replace(dotIdx, 4, "_out.hack");

    std::cout << "opening file " << newName << " for writing" << std::endl;
    outFile.open(newName);

    // initialize
    advance();
}

parser::~parser(){
    std::cout << "closing files" << std::endl;
    inFile.close();
    outFile.close();
}

string parser::getCurCmd(){
    return curCmd;
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

    return;
}

commandType parser::currentCommand(){
    if(curCmd[0] == '@'){
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

string parser::comp(){
    // whatever is after =
    int idx = curCmd.find('=') + 1;
    int len = curCmd.length();
    string ret = curCmd.substr(idx, len - idx);
    return ret;
}

string parser::dest(){
    // whatever is before = or ;
    int idx = curCmd.find('=');
    if(idx == -1){
        idx = curCmd.find(';');
    }
    if(idx == -1){
        std::cout << "invalid dest" << std::endl;
    }
    string ret = curCmd.substr(0, idx);
    return ret;
}

string parser::jump(){
    // whatever is after ;
    // null if =
    int idx = curCmd.find(';') + 1;
    if(idx == 0){
        return "null";
    }
    int len = curCmd.length();
    string ret = curCmd.substr(idx, len - idx);
    return ret;
}

void parser::push(string line){
    outFile << line + "\n";
}

