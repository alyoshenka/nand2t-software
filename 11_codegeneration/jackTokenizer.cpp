
#include "jackTokenizer.h"

string jackTokenizer::stripComment(string text)
{

    int com, com2;
    com = text.find_first_of('/');
    if (string::npos != com)
    {
        // if comment opening
        if ('*' == text[com + 1])
        {
            // find comment closing
            com2 = text.substr(com + 1).find_first_of('/');
            // if no closing '/'
            if (string::npos == com2)
            {
                std::cout << "ERROR: NO CLOSING COMMENT '/'" << std::endl;
                return text;
            }
            com2 += com + 1; // add offset back

            while ('*' != text[com2 - 1])
            {

                int comHold = com2;
                com2 = text.substr(com2 + 1).find_first_of('/');

                if (string::npos == com2)
                {
                    std::cout << "ERROR: NO CLOSING COMMENT '*'" << std::endl;
                    return text;
                }
                com2 += comHold + 1; // add offset back
            }
        }

        // cut out comment
        string left = text.substr(0, com);
        string right = text.substr(com2 + 1);
        left.append(right);
        return left;
    }
    return text;
}

jackTokenizer::jackTokenizer(string inFile)
{

    std::cout << "preparing to tokenize " << inFile << std::endl;

    inputFile.open(inFile);
    if (!inputFile.is_open() || inputFile.bad())
    {
        std::cout << "ERROR OPENING FILE FOR READING" << std::endl;
        return;
    }

    string line;
    int com;
    fileContents = "";
    // read in full file contents
    while (!inputFile.eof())
    {
        std::getline(inputFile, line);

        // strip inline "//" comments
        com = line.find_first_of("/");
        // if "/"
        while (string::npos != com)
        {
            // if next = "/"
            if ('/' == line[com + 1])
            {
                // strip inline comment
                line = line.substr(0, com);
                break;
            }
            else
            {
                int hold = com + 1;
                com = line.substr(com + 1).find_first_of('/');
                if (string::npos == com)
                {
                    break;
                }
                com += hold;
                if (line[com - 1] == '*')
                {
                    break;
                }
            }
        }

        // std::cout << line << std::endl;
        fileContents.append(line);
    }
    // remove all whitespace(?)

    // remove block "/* */" and api "/** */"comments
    do
    {
        fileContents = stripComment(fileContents);
        com = fileContents.find_first_of('/');
    } while (string::npos != com && '*' == fileContents[com + 1]);
}

bool jackTokenizer::hasMoreTokens()
{
    return !fileContents.empty();
}

void jackTokenizer::advance()
{
    // go to next symbol
    // erase whitespace in string before symbol
    // check if resulting string is a keyword
    // else it is a variable

    fileContents = fileContents.substr(fileContents.find_first_not_of(" \t"));

    // if string constant
    if ('"' == fileContents[fileContents.find_first_not_of(' ')])
    {
        // strip space
        fileContents = fileContents.substr(fileContents.find_first_not_of(' '));

        int end = fileContents.substr(1).find_first_of('"') + 2;
        currentToken = fileContents.substr(0, end);
        fileContents = fileContents.substr(end);

        // std::cout << "t: " << currentToken << std::endl;
        // std::cout << "f: " << fileContents << std::endl;
        return;
    }

    int nextToken = fileContents.find_first_of(symbolString);
    // if it doesn't start with a symbol
    if (nextToken > 0)
    {
        string beforeString = fileContents.substr(0, nextToken);

        // if fileContents[nextToken] is a token itself
        if (string::npos == beforeString.find_first_not_of(' '))
        {
            currentToken = fileContents[nextToken];
            nextToken++;
        }
        else
        { // if fileContents(0, nextToken) is a string
            // strip whitespace
            int ws;
            // left
            ws = beforeString.find_first_not_of(" \t");

            nextToken = ws;
            beforeString = beforeString.substr(ws);

            // get first word and reset nextToken
            ws = beforeString.find_first_of(' ');
            if (string::npos == ws)
            {
                ws = beforeString.length();
            }
            beforeString = beforeString.substr(0, ws);

            nextToken += ws;
            currentToken = beforeString;
        }
    }
    else if (nextToken == 0)
    {
        currentToken = fileContents[nextToken];
        nextToken = 1;
    }
    else
    {
        std::cout << "ERROR: TOKEN ERROR" << std::endl;
    }
    // std::cout << "token: " << currentToken << std::endl;
    fileContents = fileContents.substr(nextToken);

    return;
}

tokentype jackTokenizer::tokenType()
{
    if (string::npos != currentToken.find_first_of(symbolString))
    {
        // std::cout << "'" << currentToken << "' type: symbol" << std::endl;
        return tokentype::SYMBOL;
    }

    // if keywords.contains(currentToken)
    //      keyword
    // keywords.length() = 21
    for (int i = 0; i < 21; i++)
    {
        if (keywords[i].compare(currentToken) == 0)
        {
            // std::cout << "'" << currentToken << "' type: keyword" << std::endl;
            return tokentype::KEYWORD;
        }
    }

    // check constraints for identifiers and string constants

    // if enclosed with double quotes ("")
    // and no newline (\n) or double quote (")
    //      string const
    if ('"' == currentToken[0] && '"' == currentToken[currentToken.length() - 1])
    {
        if (string::npos == currentToken.find_first_of('\n') && string::npos == currentToken
                                                                                    .substr(1, currentToken.length() - 2)
                                                                                    .find_first_of('"'))
        {

            // std::cout << "'" << currentToken << "' type: string_const" << std::endl;
            return tokentype::STRING_CONST;
        }
        else
        {
            std::cout << "ERROR: INVALID STRING: " << currentToken << std::endl;
            return tokentype::INVALID;
        }
    }

    // if stoi succeeds
    //      int const???
    try
    {
        int ret = std::stoi(currentToken);
        if (ret >= 0)
        {
            // std::cout << "'" << currentToken << "' type: int_const" << std::endl;
            return tokentype::INT_CONST;
        }
    }
    catch (std::exception e)
    {
    } // fail check

    // check that only A-Z, a-z, 0-9, _
    // and first char != _

    // std::cout << "'" << currentToken << "' type: identifier" << std::endl;
    return tokentype::IDENTIFIER;

    return tokentype::INVALID;
}

keyword jackTokenizer::keyWord()
{
    if (currentToken.compare("null") == 0)
    {
        return keyword::NULLVALUE;
    }
    // optimally this would find the index of
    // currentToken in keywords array and return
    // the keyword enum value of the same index
    // however i do not know how to do indexOf()
    // in raw c++

    // return (keyword)(keywords->find(currentToken));

    if (currentToken.compare("class") == 0)
    {
        return keyword::CLASS;
    }
    else if (currentToken.compare("constructor") == 0)
    {
        return keyword::CONSTRUCTOR;
    }
    else if (currentToken.compare("function") == 0)
    {
        return keyword::FUNCTION;
    }
    else if (currentToken.compare("method") == 0)
    {
        return keyword::METHOD;
    }
    else if (currentToken.compare("field") == 0)
    {
        return keyword::FIELD;
    }
    else if (currentToken.compare("static") == 0)
    {
        return keyword::STATIC;
    }
    else if (currentToken.compare("var") == 0)
    {
        return keyword::VAR;
    }
    else if (currentToken.compare("int") == 0)
    {
        return keyword::INT;
    }
    else if (currentToken.compare("char") == 0)
    {
        return keyword::CHAR;
    }
    else if (currentToken.compare("boolean") == 0)
    {
        return keyword::BOOLEAN;
    }
    else if (currentToken.compare("void") == 0)
    {
        return keyword::_VOID;
    }
    else if (currentToken.compare("true") == 0)
    {
        return keyword::_TRUE;
    }
    else if (currentToken.compare("false") == 0)
    {
        return keyword::_FALSE;
    }
    else if (currentToken.compare("this") == 0)
    {
        return keyword::_THIS;
    }
    else if (currentToken.compare("let") == 0)
    {
        return keyword::LET;
    }
    else if (currentToken.compare("do") == 0)
    {
        return keyword::DO;
    }
    else if (currentToken.compare("if") == 0)
    {
        return keyword::IF;
    }
    else if (currentToken.compare("else") == 0)
    {
        return keyword::_ELSE;
    }
    else if (currentToken.compare("while") == 0)
    {
        return keyword::_WHILE;
    }
    else if (currentToken.compare("return") == 0)
    {
        return keyword::RETURN;
    }
    else
    {
        std::cout << "ERROR: INVALID KEYWORD: " << currentToken << std::endl;
        return keyword::NULLVALUE;
    }
}

char jackTokenizer::symbol()
{
    return currentToken[0];
}

string jackTokenizer::identifier()
{
    // check for validity

    return currentToken;
}

int jackTokenizer::intVal()
{
    return std::stoi(currentToken);
}

string jackTokenizer::stringVal()
{
    // check for validity(?)

    // strip ""
    return currentToken.substr(1, currentToken.length() - 2);
}

string jackTokenizer::getCurrentToken() const
{
    return currentToken;
}

string jackTokenizer::getFileContents() const
{
    return fileContents;
}