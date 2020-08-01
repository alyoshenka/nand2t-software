#include "parser.h"

#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::string;

parser::parser(char* inFile){
    std::cout << "opening file " << inFile << std::endl;

    ifstream myFile;
    myFile.open(inFile);
    if(myFile.is_open()){
        string line;
        while(getline(myFile, line)){
            std::cout << line << std::endl;
        }
        myFile.close();
    }else{
        std::cout << "error opening " << inFile << " for reading" << std::endl;
    }


}

bool parser::hasMoreCommands(){
    return false;
}

void parser::advance(){
    return;
}

commandType parser::currentCommand(){
    return commandType::A_COMMAND;
}

string parser::symbol(){
    return nullptr;
}

string parser::dest(){
    return nullptr;
}

string parser::comp(){
    return nullptr;
}

string parser::jump(){
    return nullptr;
}

