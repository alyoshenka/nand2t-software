#include "vmWriter.h"

vmWriter::vmWriter(string outFile){
    std::cout << "opening " << outFile << " for writing" << std::endl;

    outStream.open(outFile);

    assert(outStream.is_open());

    // continue
}

void vmWriter::writePush(segment seg, int idx){
    outStream << "push " << segToStr(seg) << " " << idx << "\n";
}

void vmWriter::writePop(segment seg, int idx){
    outStream << "pop " << segToStr(seg) << " " << idx << "\n";
}

void vmWriter::writeArithmetic(command com){
    outStream << comToStr(com) << "\n";
}

void vmWriter::writeLabel(string label){
    outStream << "label " << label << "\n";
}

void vmWriter::writeGoto(string label){
    outStream << "goto " << label << "\n";
}

void vmWriter::writeIf(string label){
    outStream << "if-goto " << label << "\n";
}

void vmWriter::writeCall(string name, int argCnt){
    outStream << "call " << name << " " << argCnt << "\n";
}

void vmWriter::writeFunction(string name, int argCnt){
    outStream << "function " << name << " " << argCnt << "\n";
}

void vmWriter::writeReturn(){
    outStream << "return\n";
}

void vmWriter::close(){
    outStream.close();
    std::cout << "closed output stream" << std::endl;
}

string vmWriter::segToStr(segment seg){
    return segmentStrings[seg];
}

string vmWriter::comToStr(command com){
    return commandStrings[com];
}