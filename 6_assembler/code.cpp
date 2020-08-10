#include "code.h"

#include <iostream>

int* dest(string mnem){
    int* ret = new int[3];
    if(mnem.compare("null") == 0){
        ret[0] = 0;
        ret[1] = 0;
        ret[2] = 0;
    }else if(mnem.compare("M") == 0){
        ret[0] = 0;
        ret[1] = 0;
        ret[2] = 1;
    }else if(mnem.compare("D") == 0){
        ret[0] = 0;
        ret[1] = 1;
        ret[2] = 0;
    }else if(mnem.compare("MD") == 0){
        ret[0] = 0;
        ret[1] = 1;
        ret[2] = 1;
    }else if(mnem.compare("A") == 0){
        ret[0] = 1;
        ret[1] = 0;
        ret[2] = 0;
    }else if(mnem.compare("AM") == 0){
        ret[0] = 1;
        ret[1] = 0;
        ret[2] = 1;
    }else if(mnem.compare("AD") == 0){
        ret[0] = 1;
        ret[1] = 1;
        ret[2] = 0;
    }else if(mnem.compare("AMD") == 0){
        ret[0] = 1;
        ret[1] = 1;
        ret[2] = 1;
    }else{
        ret[0] = -1;
        ret[1] = -1;
        ret[2] = -1;
    }
    std::cout << "dest:" << std::endl;
    for(int i = 0; i < 3; i++){
        std::cout << ret[i];
    }
    std::cout << std::endl;
    return ret;
}

int* comp(string mnem){
    int* ret = new int[7];
    ret[0] = mnem.find('M') < mnem.length() ? 1 : 0; // a
    if(mnem.compare("0") == 0){
        ret[1] = 1;
        ret[2] = 0;
        ret[3] = 1;
        ret[4] = 0;
        ret[5] = 1;
        ret[6] = 0;
    }else if(mnem.compare("1") == 0){
        ret[1] = 1;
        ret[2] = 1;
        ret[3] = 1;
        ret[4] = 1;
        ret[5] = 1;
        ret[6] = 1;
    }else if(mnem.compare("-1") == 0){
        ret[1] = 1;
        ret[2] = 1;
        ret[3] = 1;
        ret[4] = 0;
        ret[5] = 1;
        ret[6] = 0;
    }else if(mnem.compare("D") == 0){
        ret[1] = 0;
        ret[2] = 0;
        ret[3] = 1;
        ret[4] = 1;
        ret[5] = 0;
        ret[6] = 0;
    }else if(mnem.compare("A") == 0
        || mnem.compare("M") == 0){
        ret[1] = 1;
        ret[2] = 1;
        ret[3] = 0;
        ret[4] = 0;
        ret[5] = 0;
        ret[6] = 0;
    }else if(mnem.compare("!D") == 0){
        ret[1] = 0;
        ret[2] = 0;
        ret[3] = 1;
        ret[4] = 1;
        ret[5] = 0;
        ret[6] = 1;
    }else if(mnem.compare("!A") == 0
        || mnem.compare("!M") == 0){
        ret[1] = 1;
        ret[2] = 1;
        ret[3] = 0;
        ret[4] = 0;
        ret[5] = 0;
        ret[6] = 1;
    }else if(mnem.compare("-D") == 0){
        ret[1] = 0;
        ret[2] = 0;
        ret[3] = 1;
        ret[4] = 1;
        ret[5] = 1;
        ret[6] = 1;
    }else if(mnem.compare("-A") == 0
        || mnem.compare("-M") == 0){
        ret[1] = 1;
        ret[2] = 1;
        ret[3] = 0;
        ret[4] = 0;
        ret[5] = 1;
        ret[6] = 1;
    }else if(mnem.compare("D+1") == 0){
        ret[1] = 0;
        ret[2] = 1;
        ret[3] = 1;
        ret[4] = 1;
        ret[5] = 1;
        ret[6] = 1;
    }else if(mnem.compare("A+1") == 0
        || mnem.compare("M+1") == 0){
        ret[1] = 1;
        ret[2] = 1;
        ret[3] = 0;
        ret[4] = 1;
        ret[5] = 1;
        ret[6] = 1;
    }else if(mnem.compare("D-1") == 0){
        ret[1] = 0;
        ret[2] = 0;
        ret[3] = 1;
        ret[4] = 1;
        ret[5] = 1;
        ret[6] = 0;
    }else if(mnem.compare("A-1") == 0
        || mnem.compare("M-1") == 0){
        ret[1] = 1;
        ret[2] = 1;
        ret[3] = 0;
        ret[4] = 0;
        ret[5] = 1;
        ret[6] = 0;
    }else if(mnem.compare("D+A") == 0
        || mnem.compare("D+M") == 0){
        ret[1] = 0;
        ret[2] = 0;
        ret[3] = 0;
        ret[4] = 0;
        ret[5] = 1;
        ret[6] = 0;
    }else if(mnem.compare("D-A") == 0
        || mnem.compare("D-M") == 0){
        ret[1] = 0;
        ret[2] = 1;
        ret[3] = 0;
        ret[4] = 0;
        ret[5] = 1;
        ret[6] = 1;
    }else if(mnem.compare("A-D") == 0
        || mnem.compare("M-D") == 0){
        ret[1] = 0;
        ret[2] = 0;
        ret[3] = 0;
        ret[4] = 1;
        ret[5] = 1;
        ret[6] = 1;
    }else if(mnem.compare("D&A") == 0
        || mnem.compare("D&M") == 0){
        ret[1] = 0;
        ret[2] = 0;
        ret[3] = 0;
        ret[4] = 0;
        ret[5] = 0;
        ret[6] = 0;
    }else if(mnem.compare("D|A") == 0
        || mnem.compare("D|M") == 0){
        ret[1] = 0;
        ret[2] = 1;
        ret[3] = 0;
        ret[4] = 1;
        ret[5] = 0;
        ret[6] = 1;
    }else{
        ret[1] = -1;
        ret[2] = -1;
        ret[3] = -1;
        ret[4] = -1;
        ret[5] = -1;
        ret[6] = -1;
    }
    std::cout << "comp:" << std::endl;
    for(int i = 0; i < 7; i++){
        std::cout << ret[i];
    }
    std::cout << std::endl;
    return ret;
}

int* jump(string mnem){
    int* ret = new int[3];
    if(mnem.compare("null") == 0){
        ret[0] = 0;
        ret[1] = 0;
        ret[2] = 0;
    }else if(mnem.compare("JGT") == 0){
        ret[0] = 0;
        ret[1] = 0;
        ret[2] = 1;
    }else if(mnem.compare("JEQ") == 0){
        ret[0] = 0;
        ret[1] = 1;
        ret[2] = 0;
    }else if(mnem.compare("JGE") == 0){
        ret[0] = 0;
        ret[1] = 1;
        ret[2] = 1;
    }else if(mnem.compare("JLT") == 0){
        ret[0] = 1;
        ret[1] = 0;
        ret[2] = 0;
    }else if(mnem.compare("JNE") == 0){
        ret[0] = 1;
        ret[1] = 0;
        ret[2] = 1;
    }else if(mnem.compare("JLE") == 0){
        ret[0] = 1;
        ret[1] = 1;
        ret[2] = 0;
    }else if(mnem.compare("JMP") == 0){
        ret[0] = 1;
        ret[1] = 1;
        ret[2] = 1;
    }else{
        ret[0] = -1;
        ret[1] = -1;
        ret[2] = -1;
    }
    std::cout << "jump:" << std::endl;
    for(int i = 0; i < 3; i++){
        std::cout << ret[i];
    }
    std::cout << std::endl;
    return ret;
}