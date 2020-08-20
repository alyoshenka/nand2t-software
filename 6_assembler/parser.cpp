#include "parser.h"

#include <iostream>

#include <algorithm>
#include <string>

using std::string;

parser::parser(char* fileName){

    curCmd = "";
    symAddr = 0;
    varAddr = 16; // initialize

    std::cout << "opening file " << fileName << " for reading" << std::endl;

    inFile.open(fileName);
    if(!inFile.is_open()){
        std::cout << "error opening " << fileName << " for reading" << std::endl;
    }

    string newName(fileName);
    int dotIdx = newName.find('.');
    newName.replace(dotIdx, 4, ".hack");

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
    // strip inline comments
    string comment = "/";
    int com = curCmd.find_first_of(comment);
    if(com != std::string::npos){
        curCmd = curCmd.substr(0, com);
    }
    // strip whitespace  
    string whitespace = " \n\t\r\f\v";
    int start = curCmd.find_first_not_of(whitespace);
    if(start != std::string::npos){
        curCmd = curCmd.substr(start);
    }
    int end = curCmd.find_last_not_of(whitespace);
    if(end != std::string::npos){
        curCmd = curCmd.substr(0, end + 1);
    }

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
    }else if (curCmd[0] == '('){
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
    // whatever is after = or ;

    // WTF

    string ret = "";

    // comp
    int idx = curCmd.find('=') + 1;
    if(idx > 0 && idx <= curCmd.length()){
        int len = curCmd.length();
        ret = curCmd.substr(idx, len - idx);
    }else{
        // jump
        idx = curCmd.find(';');
        if(idx >= 0 && idx < curCmd.length()){
            ret = curCmd.substr(0, idx);
        }else{
            std::cout << "COMP ERROR: " << curCmd << std::endl;
        }
    }
    return ret;
}

string parser::dest(){
    // whatever is before = or ;
    int idx = curCmd.find('=');
    if(idx < 0 || idx >= curCmd.length()){
        return "null";
    }else{
        return curCmd.substr(0, idx);
    }
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

void parser::addCurrentSymbol(){
    string sym = symbol();
    if(table.contains(sym)){
        std::cout << "duplicate symbol: " << sym << std::endl;
        return;
    }
    if(currentCommand() == commandType::L_COMMAND){ // func
        std::cout << "adding " << sym << " at ROM[" << symAddr << "]" << std::endl;
        table.addEntry(sym, symAddr);
    }else if(currentCommand() == commandType::A_COMMAND){ // var
        if(!isSymbol(sym)){ // check if number
            std::cout << "invalid symbol: " << sym << std::endl;
        }
        else{
            // add variable
            std::cout << "adding " << sym << " at RAM[" << varAddr << "]" << std::endl;
            table.addEntry(sym, varAddr);
            varAddr++;
        }
    }else{ // err
        std::cout << "SYM ERROR" << std::endl;
    }

}

bool parser::isSymbol(string sym){
    try{
        int i = std::stoi(sym);
    }catch(std::invalid_argument){
        return true;
    }
    return false;
}

int parser::getAddress(string sym){
    if(isSymbol(sym)){ // address
        return table.getAddress(sym);
    }else{ // number
        return std::stoi(sym);
    }
}

void parser::resetFile(string fileName){
    // BAD
    inFile.close();
    inFile.open(fileName);
    advance();
}

void parser::incSym(){
    symAddr++;
}