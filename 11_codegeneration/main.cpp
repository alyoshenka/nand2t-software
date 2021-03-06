
// 1. create a JackTokenizer from the xxx.jack input file
// 2. create and output file called xxx.xml
//      and prepare it for writing
// 3. use the CompilationEngine to compile the input
//      JackTokenizer into the output file

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#include "jackTokenizer.h"
#include "compilationEngine.h"

using std::ifstream;
using std::string;

/** Is the given string a valid .jack file? */
bool isJackFile(string inFile)
{
    if (inFile.length() <= 4)
    {
        return false;
    }
    return inFile.substr(inFile.length() - 5, 5).compare(".jack") == 0;
}

/** Compiles an individual .jack file. */
void compileFile(string fileName)
{
    string outFile = (fileName.substr(0, fileName.length() - 5)).append("_out.xml");
    std::cout << "opening " << fileName << " for reading" << std::endl;
    std::cout << "opening " << outFile << " for writing" << std::endl;

    jackTokenizer *tokenizer = new jackTokenizer(fileName);
    compilationEngine compEng(tokenizer, outFile);
}

/** Main application method, takes cl input. */
int main(int cnt, char *args[])
{
    // if no argument specified
    if (cnt < 2)
    {
        std::cout << "no input file/directory specified" << std::endl;
        return -1;
    }
    // if > 1 argument given
    if (cnt > 2)
    {
        std::cout << "too many arguments given" << std::endl;
    }
    // get cli input
    string inFile = string(args[1]);

    // if file
    if (isJackFile(inFile))
    {
        compileFile(inFile);
    }
    else
    { // else dir
        // for all .jack files inFile/
        //      compileFile(filename.jack);

        std::string pattern(inFile);
        pattern.append("\\*.jack");
        std::cout << "scaning directory " << pattern << std::endl;
        WIN32_FIND_DATA data;
        HANDLE hFind;
        if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
        {
            do
            {
                std::cout << data.cFileName << std::endl;
            } while (FindNextFile(hFind, &data) != 0);
            FindClose(hFind);
        }
    }

    return 0;
}