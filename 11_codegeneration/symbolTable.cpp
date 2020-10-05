#include "symbolTable.h"

symbolTable::symbolTable(){

}

void symbolTable::startSubroutine(){
    return;
}

void symbolTable::define(string name, string type, varKind kind){
    return;
}

int symbolTable::varCount(varKind kind){
    return 0;
}

varKind symbolTable::kindOf(string name){
    return varKind::NONE;
}

string symbolTable::typeOf(string name){
    return "";
}

int symbolTable::indexOf(string name){
    return 0;
}