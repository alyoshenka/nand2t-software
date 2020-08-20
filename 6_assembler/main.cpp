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
    commandType cmdType;

    std::cout << "first pass" << std::endl;
    // read
    while(p.hasMoreCommands()){
        commandType cmdType = p.currentCommand();
        std::cout << "parsing " << p.getCurCmd() << std::endl;
        cmdType = p.currentCommand();
        switch(cmdType){
            case commandType::C_COMMAND:
                // increment symbol counter
                p.incSym();
                break;
            case commandType::A_COMMAND:
                // do not add variable
                // increment symbol counter
                p.incSym();
                break;
            case commandType::L_COMMAND:
                // add symbol
                p.addCurrentSymbol();
                // do not increment counter
                break;
            default:
                std::cout << "COMMAND ERROR" << std::endl;
                break;
        }
        p.advance();
    }
    p.resetFile(inFile);

    std::cout << "\nsecond pass" << std::endl;
    // write
    while(p.hasMoreCommands()){
        // reset bin
        std::fill_n(bin, 16, -1);

        cmdType = p.currentCommand();
        std::cout << "parsing " << p.getCurCmd() << std::endl;
        switch(cmdType){
            case commandType::C_COMMAND:{
                bin[0] = 1; // C
                bin[1] = 1; // junk    curCmd = curCmd.substr(start);
                bin[2] = 1; // junk

                int* c = comp(p.comp());
                int* d = dest(p.dest());
                int* j = jump(p.jump());

                // combine codes
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
                // check if var in table
                // if not, add var to table
                p.addCurrentSymbol();

                bin[0] = 0; // A
                string sym = p.symbol();
                int* addr = int_to_bin(p.getAddress(sym));
                for(int i = 0; i < 15; i++){
                    bin[i + 1] = addr[i];
                }
            }
                break;
            case commandType::L_COMMAND:
                // do nothing
                std::cout << "L cmd" << std::endl;
                p.advance();
                continue;
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