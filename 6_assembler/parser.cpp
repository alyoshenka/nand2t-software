#include "parser.h"

#include <iostream>

#include <algorithm>
#include <string>

using std::string;

parser::parser(char* inFile){

    curCmd = "";

    compMapNotA["0"]="101010";
    compMapNotA["1"]="111111";
    compMapNotA["-1"]="111010";
    compMapNotA["D"]="001100";
    compMapNotA["A"]="110000";
    compMapNotA["!D"]="001101";
    compMapNotA["!A"]="110001";
    compMapNotA["-D"]="001111";
    compMapNotA["-A"]="110011";
    compMapNotA["D+1"]="011111";
    compMapNotA["A+1"]="110111";
    compMapNotA["D-1"]="001110";
    compMapNotA["A-1"]="110010";
    compMapNotA["D+A"]="000010";
    compMapNotA["D-A"]="010011";
    compMapNotA["A-D"]="000111";
    compMapNotA["D&A"]="000000";
    compMapNotA["D|A"]="010101";

    compMapA["M"]="110000";
    compMapA["!M"]="110001";
    compMapA["-M"]="110011";
    compMapA["M+1"]="110111";
    compMapA["M-1"]="110010";
    compMapA["D+M"]="000010";
    compMapA["D-M"]="010011";
    compMapA["M-D"]="000111";
    compMapA["D&M"]="000000";
    compMapA["D|M"]="010101";

    std::cout << "opening file " << inFile << std::endl;

    myFile.open(inFile);
    if(!myFile.is_open()){
        std::cout << "error opening " << inFile << " for reading" << std::endl;
    }

    // initialize
    advance();
}

parser::~parser(){
    std::cout << "closing file" << std::endl;
    myFile.close();
}

string parser::getCurCmd(){
    return curCmd;
}

bool parser::hasMoreCommands(){
    return !curCmd.empty();
}

void parser::advance(){
    // try
    if(myFile.eof()) { curCmd.clear(); }
    else { getline(myFile, curCmd); }
    // catch: curCmd = empty

    if(curCmd[0] == '/' && curCmd[1] == '/'){ advance(); }
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

string parser::comp(){
    if(currentCommand()==commandType::C_COMMAND){
        // notA
        return compMapNotA[curCmd];
    }else{
        // A
        return compMapA[curCmd];
    }
}

string parser::dest(){
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

