#include <iostream>

#include "parser.h"
#include "code.h"


int main(int cnt, char* args[]) {
    if(cnt > 2){
        std::cout << cnt << " arguments" << std::endl;
        return -1;
    }
    char* inFile = args[1];

    parser p(inFile);

    int* bin = new int[16];

    while(p.hasMoreCommands()){
        // reset 
        std::fill_n(bin, 16, -1);

        commandType cmdType = p.currentCommand();
        std::cout << "parsing " << p.getCurCmd() << std::endl;
        switch(cmdType){
            case commandType::C_COMMAND:{
                bin[0] = 1; // C
                bin[1] = 1; // junk    curCmd = curCmd.substr(start);
                bin[2] = 1; // junk

                int* c = comp(p.comp());
                int* d = dest(p.dest());
                int* j = jump(p.jump());

                for(int i = 0; i < 7; i++){
                    bin[i + 3] = c[i];
                }
                for(int i = 0; i < 3; i++){
                    bin[i + 10] = d[i];
                    bin[i + 13] = j[i];
                }
            }
                break;
            case commandType::A_COMMAND:{
                bin[0] = 0; // A
                string sym = p.symbol();
                int* addr = sym_to_bin(sym);
                for(int i = 0; i < 15; i++){
                    bin[i + 1] = addr[i];
                }
            }
                break;
            case commandType::L_COMMAND:
                std::cout << "L cmd" << std::endl;
                // symbol table
                break;
            default:
                std::cout << "UNKNOWN COMMAND" << std::endl;
                break;
        }

        string line = "";
        for(int i = 0; i < 16; i++){
            line.append(std::to_string(bin[i]));
            if(i % 4 == 0){std::cout << " ";}
            std::cout << bin[i];
        }
        std::cout << std::endl;
        p.push(line);
        p.advance();
    }

    return 0;
}
