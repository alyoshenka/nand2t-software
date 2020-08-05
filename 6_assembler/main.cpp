#include <iostream>

#include "parser.h"


int main(int cnt, char* args[]) {
    if(cnt > 2){
        std::cout << cnt << " arguments" << std::endl;
        return -1;
    }
    char* inFile = args[1];

    parser p(inFile);

    while(p.hasMoreCommands()){
        std::cout << "c: " << p.getCurCmd() << std::endl;
        p.advance();
    }

    return 0;
}
