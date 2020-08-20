#include "codeWriter.h"

#include <iostream>

codeWriter::codeWriter(string outFile){
    std::cout << "opening " << outFile << " for writing" << std::endl;
}

codeWriter::~codeWriter(){
    std::cout << "closing output file" << std::endl;
}

void codeWriter::setFileName(string fileName){
    std::cout << "now parsing " << fileName << std::endl;
}

void codeWriter::writeArithmetic(string command){
    std::cout << "writing " << command << std::endl;
}

void codeWriter::writePushPop(commandType command, string segment, int index){
    std::cout << "writing push/pop to " << segment << " " << index << std::endl;
}

void codeWriter::close(){
    std::cout << "closing output file" << std::endl;
}