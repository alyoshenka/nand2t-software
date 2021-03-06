
#include "compilationEngine.h"

compilationEngine::compilationEngine(jackTokenizer *_tokenizer, string outputFile)
{
    tokenizer = _tokenizer;
    outStream.open(outputFile);
    compileClass();
    outStream.close();
}

void compilationEngine::compileClass()
{
    std::cout << "compiling class" << std::endl;
    outStream << "<class>\n";

    // keyword class
    indentation.push_back(tab);
    tokenizer->advance();
    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::CLASS == tokenizer->keyWord());
    outStream << indentation << "<keyword> class </keyword>\n";

    // identifier name
    tokenizer->advance();
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";

    // symbol {
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('{' == tokenizer->symbol());
    outStream << indentation << "<symbol> { </symbol>\n";

    // classVarDec*
    //      static | field
    // subroutineDec*
    //      constructor | function | method
    tokenizer->advance();
    assert(tokentype::KEYWORD == tokenizer->tokenType());
    keyword kw = tokenizer->keyWord();
    while (isClassVarDec(kw))
    {
        compileClassVarDec();
        kw = tokenizer->keyWord();
    }
    while (isSubroutineDec(kw))
    {
        compileSubroutine();
        if (tokentype::KEYWORD != tokenizer->tokenType())
        {
            break;
        }
        kw = tokenizer->keyWord();
    }

    // symbol }
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('}' == tokenizer->symbol());
    outStream << "<symbol> } </symbol>\n";

    outStream << "</class>";
}

void compilationEngine::compileClassVarDec()
{
    std::cout << "compiling classVarDec" << std::endl;
    outStream << indentation << "<classVarDec>\n";
    indentation.push_back(tab);

    // static | field
    outStream << indentation << "<keyword> " << (keyword::STATIC == tokenizer->keyWord() ? "static" : "field")
              << " </keyword>\n";
    // type, identifier or keyword
    tokenizer->advance();
    tokentype tt = tokenizer->tokenType();
    if (tokentype::KEYWORD == tt)
    {
        keyword kw = tokenizer->keyWord();
        outStream << indentation << "<keyword> ";
        // int | char | bool
        if (keyword::INT == kw)
        {
            outStream << "int";
        }
        else if (keyword::CHAR == kw)
        {
            outStream << "char";
        }
        else if (keyword::BOOLEAN == kw)
        {
            outStream << "boolean";
        }
        else
        {
            assert(false);
        }
        outStream << " </keyword>\n";
    }
    else if (tokentype::IDENTIFIER == tt)
    {
        string id = tokenizer->identifier();
        outStream << indentation << "<identifier> " << id << " </identifier>\n";
    }
    else
    {
        assert(false);
    }

    // varName
    tokenizer->advance();
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";

    // (, type varName)*
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    while (',' == tokenizer->symbol())
    {
        outStream << indentation << "<symbol> , </symbol>\n";
        tokenizer->advance();
        tokentype tt = tokenizer->tokenType();
        if (tokentype::KEYWORD == tt)
        {
            keyword kw = tokenizer->keyWord();
            outStream << indentation << "<keyword> ";
            // int | char | bool
            if (keyword::INT == kw)
            {
                outStream << "int";
            }
            else if (keyword::CHAR == kw)
            {
                outStream << "char";
            }
            else if (keyword::BOOLEAN == kw)
            {
                outStream << "boolean";
            }
            else
            {
                assert(false);
            }
            outStream << " </keyword>\n";
        }
        else if (tokentype::IDENTIFIER == tt)
        {
            string id = tokenizer->identifier();
            outStream << indentation << "<identifier> " << id << " </identifier>\n";
        }
        else
        {
            assert(false);
        }

        tokenizer->advance();
    }

    // ;
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(';' == tokenizer->symbol());
    outStream << indentation << "<symbol> ; </symbol>\n";

    indentation.pop_back();
    outStream << indentation << "</classVarDec>\n";

    tokenizer->advance();
}

void compilationEngine::compileSubroutine()
{
    std::cout << "compiling subroutine" << std::endl;
    // dec
    outStream << indentation << "<subroutineDec>\n";
    indentation.push_back(tab);

    // keyword constructor | function | method
    tokentype tt = tokenizer->tokenType();
    assert(tokentype::KEYWORD == tt);
    keyword kw = tokenizer->keyWord();
    assert(isSubroutineDec(kw));
    outStream << indentation << "<keyword> ";
    if (keyword::CONSTRUCTOR == kw)
    {
        outStream << "constructor";
    }
    else if (keyword::FUNCTION == kw)
    {
        outStream << "function";
    }
    else if (keyword::METHOD == kw)
    {
        outStream << "method";
    }
    else
    {
        assert(false);
    }
    outStream << " </keyword>\n";

    tokenizer->advance();
    tt = tokenizer->tokenType();
    // keyword type | identifier type
    if (tt == tokentype::KEYWORD)
    {
        kw = tokenizer->keyWord();
        assert(isFundamentalType(kw));
        outStream << indentation << "<keyword> "
                  << kwToString(kw) << " </keyword>\n";
    }
    else if (tt == tokentype::IDENTIFIER)
    {
        outStream << indentation << "<identifier> "
                  << tokenizer->identifier() << " </identifier>\n";
    }
    else
    {
        assert(false);
    }

    tokenizer->advance();
    // identifier subroutineName
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> "
              << tokenizer->identifier() << " </identifier>\n";

    tokenizer->advance();
    // symbol (
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('(' == tokenizer->symbol());
    outStream << indentation << "<symbol> ( </symbol>\n";

    tokenizer->advance();
    // parameterList
    compileParameterList();

    // symbol )
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(')' == tokenizer->symbol());
    indentation.pop_back();
    outStream << indentation << "<symbol> ) </symbol>\n";

    // subroutineBody
    outStream << indentation << "<subroutineBody>\n";

    // {
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('{' == tokenizer->symbol());
    outStream << indentation << "<symbol> { </symbol>\n";
    indentation.push_back(tab);

    tokenizer->advance();
    // varDec*
    while (tokentype::KEYWORD == tokenizer->tokenType() && keyword::VAR == tokenizer->keyWord())
    {
        compileVarDec();
    }

    // statements
    compileStatements();

    // }
    indentation.pop_back();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('}' == tokenizer->symbol());
    outStream << indentation << "<symbol> } </symbol>\n";

    outStream << indentation << "</subroutineBody>\n";
    outStream << indentation << "</subroutineDec>\n";
    tokenizer->advance();
}

void compilationEngine::compileParameterList()
{
    outStream << indentation << "<parameterList>\n";
    std::cout << "compiling parameter list" << std::endl;
    indentation.push_back(tab);
    // ((type varName) (, type varName)*)?

    // no parameters
    if (tokentype::SYMBOL == tokenizer->tokenType())
    {
        assert(')' == tokenizer->symbol());
        outStream << indentation << "</parameterList>\n";
        return;
    }

    // first parameter
    // type
    if (tokentype::KEYWORD == tokenizer->tokenType())
    {
        keyword kw = tokenizer->keyWord();
        assert(isFundamentalType(kw));
        outStream << indentation << "<keyword> " << kwToString(kw) << " </keyword>\n";
    }
    else if (tokentype::IDENTIFIER == tokenizer->tokenType())
    {
        outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
    }
    else
    {
        assert(false);
    }

    tokenizer->advance();
    // name
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";

    tokenizer->advance();
    // any other parameters
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    while (',' == tokenizer->symbol())
    {
        outStream << indentation << "<symbol> , </symbol>\n";
        tokenizer->advance();
        // type
        if (tokentype::KEYWORD == tokenizer->tokenType())
        {
            keyword kw = tokenizer->keyWord();
            assert(isFundamentalType(kw));
            outStream << indentation << "<keyword> " << kwToString(kw) << " </keyword>\n";
        }
        else if (tokentype::IDENTIFIER == tokenizer->tokenType())
        {
            outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
        }
        else
        {
            assert(false);
        }

        tokenizer->advance();
        // name
        assert(tokentype::IDENTIFIER == tokenizer->tokenType());
        outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
        tokenizer->advance();

        assert(tokentype::SYMBOL == tokenizer->tokenType());
    }

    indentation.pop_back();
    outStream << indentation << "</parameterList>\n";
}

void compilationEngine::compileVarDec()
{
    std::cout << "compiling var dec" << std::endl;
    outStream << indentation << "<varDec>\n";
    indentation.push_back(tab);

    // var
    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::VAR == tokenizer->keyWord());
    outStream << indentation << "<keyword> var </keyword>\n";

    tokenizer->advance();
    // type
    tokentype tt = tokenizer->tokenType();
    if (tokentype::KEYWORD == tt)
    {
        keyword kw = tokenizer->keyWord();
        outStream << indentation << "<keyword> ";
        // int | char | bool
        if (keyword::INT == kw)
        {
            outStream << "int";
        }
        else if (keyword::CHAR == kw)
        {
            outStream << "char";
        }
        else if (keyword::BOOLEAN == kw)
        {
            outStream << "boolean";
        }
        else
        {
            assert(false);
        }
        outStream << " </keyword>\n";
    }
    else if (tokentype::IDENTIFIER == tt)
    {
        string id = tokenizer->identifier();
        outStream << indentation << "<identifier> " << id << " </identifier>\n";
    }
    else
    {
        assert(false);
    }

    tokenizer->advance();
    // name
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";

    tokenizer->advance();
    // (, name)*
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    while (',' == tokenizer->symbol())
    {
        outStream << indentation << "<symbol> , </symbol>\n";
        tokenizer->advance();
        assert(tokentype::IDENTIFIER == tokenizer->tokenType());
        outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
        tokenizer->advance();
    }

    // ;
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(';' == tokenizer->symbol());
    outStream << indentation << "<symbol> ; </symbol>\n";

    indentation.pop_back();
    outStream << indentation << "</varDec>\n";

    tokenizer->advance();
}

void compilationEngine::compileStatements()
{
    std::cout << "compiling statements" << std::endl;
    outStream << indentation << "<statements>\n";
    // compile until reach return

    tokentype tt = tokenizer->tokenType();
    assert(tokentype::KEYWORD == tt);
    keyword kw = tokenizer->keyWord();
    while (keyword::RETURN != kw)
    {
        // compile statement
        switch (kw)
        {
        case keyword::DO:
            compileDo();
            break;
        case keyword::LET:
            compileLet();
            break;
        case keyword::_WHILE:
            compileWhile();
            break;
        case keyword::IF:
            compileIf();
            break;
        default:
            assert(false);
            break;
        }

        // check next statement
        tt = tokenizer->tokenType();
        if (tokentype::SYMBOL == tt && '}' == tokenizer->symbol())
        {
            outStream << indentation << "</statements>\n";
            return;
        }
        assert(tokentype::KEYWORD == tt);
        kw = tokenizer->keyWord();
    }

    compileReturn();
    outStream << indentation << "</statements>\n";
}

void compilationEngine::compileDo()
{
    std::cout << "compiling do" << std::endl;
    outStream << indentation << "<doStatement>\n";
    // 'do' subroutineCall ';'
    //      subroutineName '(' expressionList ')' | ( className | varName )
    //      '.' subroutineName '(' expressionList ')'

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::DO == tokenizer->keyWord());
    outStream << indentation << "<keyword> do </keyword>\n";

    tokenizer->advance();
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());

    if ('.' == tokenizer->symbol())
    {
        outStream << indentation << "<symbol> . </symbol>\n";
        tokenizer->advance();
        assert(tokentype::IDENTIFIER == tokenizer->tokenType());
        outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
        tokenizer->advance();
        assert(tokentype::SYMBOL == tokenizer->tokenType());
    }

    assert('(' == tokenizer->symbol());
    outStream << indentation << "<symbol> ( </symbol>\n";
    tokenizer->advance();
    compileExpressionList();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(')' == tokenizer->symbol());
    outStream << indentation << "<symbol> ) </symbol>\n";

    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(';' == tokenizer->symbol());
    outStream << indentation << "<symbol> ; </symbol>\n";
    tokenizer->advance();

    outStream << indentation << "</doStatement>\n";
}

void compilationEngine::compileLet()
{
    std::cout << "compiling let" << std::endl;
    outStream << indentation << "<letStatement>\n";
    // 'let' varName ('[' expression ']')?  '=' expression ';'

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::LET == tokenizer->keyWord());
    outStream << indentation << "<keyword> let </keyword>\n";
    tokenizer->advance();
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
    tokenizer->advance();

    assert(tokentype::SYMBOL == tokenizer->tokenType());
    if ('[' == tokenizer->symbol())
    {
        outStream << indentation << "<symbol> [ </symbol>\n";
        tokenizer->advance();
        compileExpression();
        assert(tokentype::SYMBOL == tokenizer->tokenType());
        assert(']' == tokenizer->symbol());
        outStream << indentation << "<symbol> ] </symbol>\n";
        tokenizer->advance();
        assert(tokentype::SYMBOL == tokenizer->tokenType());
    }
    outStream << indentation << "<symbol> = </symbol>\n";
    tokenizer->advance();
    compileExpression();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(';' == tokenizer->symbol());
    outStream << indentation << "<symbol> ; </symbol>\n";
    tokenizer->advance();

    outStream << indentation << "</letStatement>\n";
}

void compilationEngine::compileWhile()
{
    std::cout << "compiling while" << std::endl;
    outStream << indentation << "<whileStatement>\n";
    // 'while' '(' expression ')' '{' statements '}'

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::_WHILE == tokenizer->keyWord());
    outStream << indentation << "<keyword> while </keyword>\n";
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('(' == tokenizer->symbol());
    outStream << indentation << "<symbol> ( </symbol>\n";
    tokenizer->advance();
    compileExpression();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    std::cout << "sym: " << tokenizer->symbol() << std::endl;
    assert(')' == tokenizer->symbol());
    outStream << indentation << "<symbol> ) </symbol>\n";
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('{' == tokenizer->symbol());
    outStream << indentation << "<symbol> { </symbol>\n";
    tokenizer->advance();
    compileStatements();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('}' == tokenizer->symbol());
    outStream << indentation << "<symbol> } </symbol>\n";
    tokenizer->advance();

    outStream << indentation << "</whileStatement>\n";
}

void compilationEngine::compileReturn()
{
    outStream << indentation << "<returnStatement>\n";
    std::cout << "compiling return" << std::endl;
    // 'return' expression? ';'

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::RETURN == tokenizer->keyWord());
    outStream << indentation << "<keyword> return </keyword>\n";
    tokenizer->advance();
    if (tokentype::SYMBOL != tokenizer->tokenType())
    {
        compileExpression();
    }
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(';' == tokenizer->symbol());
    outStream << indentation << "<symbol> ; </symbol>\n";
    tokenizer->advance();

    outStream << indentation << "</returnStatement>\n";
}

void compilationEngine::compileIf()
{
    outStream << indentation << "<ifStatement>\n";
    std::cout << "compiling if" << std::endl;
    // 'if' '(' expression ')' '{' statements '}'
    // ('else' '{' statements '}')?

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::IF == tokenizer->keyWord());
    outStream << indentation << "<keyword> if </keyword>\n";
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('(' == tokenizer->symbol());
    outStream << indentation << "<symbol> ( </symbol>\n";
    tokenizer->advance();
    compileExpression();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(')' == tokenizer->symbol());
    outStream << indentation << "<symbol> ) </symbol>\n";
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('{' == tokenizer->symbol());
    outStream << indentation << "<symbol> { </symbol>\n";
    tokenizer->advance();
    compileStatements();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('}' == tokenizer->symbol());
    outStream << indentation << "<symbol> } </symbol>\n";

    tokenizer->advance();

    // ('else' '{' statements '}')?
    if (tokentype::KEYWORD == tokenizer->tokenType() &&
        keyword::_ELSE == tokenizer->keyWord())
    {

        outStream << indentation << "<keyword> else </keyword>\n";
        tokenizer->advance();
        assert(tokentype::SYMBOL == tokenizer->tokenType());
        assert('{' == tokenizer->symbol());
        outStream << indentation << "<symbol> { </symbol>\n";
        tokenizer->advance();
        compileStatements();
        assert(tokentype::SYMBOL == tokenizer->tokenType());
        assert('}' == tokenizer->symbol());
        outStream << indentation << "<symbol> } </symbol>\n";
        tokenizer->advance();
    }

    outStream << indentation << "</ifStatement>\n";
}

void compilationEngine::compileExpression()
{
    outStream << indentation << "<expression>\n";
    std::cout << "compiling expression" << std::endl;
    // term (op term)*
    compileTerm();

    if (tokentype::SYMBOL != tokenizer->tokenType())
    {
        return;
    }
    while (tokentype::SYMBOL == tokenizer->tokenType() && string::npos != ops.find(tokenizer->symbol()))
    {

        std::cout << "term: (op term)*" << std::endl;
        // op
        char s = tokenizer->symbol();
        if ('>' == s)
        {
            outStream << indentation << "<symbol> &gt; </symbol>\n";
        }
        else if ('<' == s)
        {
            outStream << indentation << "<symbol> &lt; </symbol>\n";
        }
        else if ('&' == s)
        {
            outStream << indentation << "<symbol> &amp; </symbol>\n";
        }
        else
        {
            outStream << indentation << "<symbol> " << tokenizer->symbol() << " </symbol>\n";
        }

        tokenizer->advance();
        // term
        compileTerm();
    }
    outStream << indentation << "</expression>\n";
}

void compilationEngine::compileTerm()
{
    outStream << indentation << "<term>\n";
    std::cout << "compiling term" << std::endl;
    // integerConstant | stringConstant | keywordConstant
    // | varName | varName '[' expression ']' | subroutineCall
    // | '(' expression ')' | unaryOp term

    tokentype tt = tokenizer->tokenType();
    if (tokentype::INT_CONST == tt)
    { // int const
        std::cout << "term: int const" << std::endl;
        outStream << indentation << "<integerConstant> "
                  << tokenizer->intVal() << " </integerConstant>\n";
    }
    else if (tokentype::STRING_CONST == tt)
    { // str const
        std::cout << "term: str const" << std::endl;
        outStream << indentation << "<stringConstant> "
                  << tokenizer->stringVal() << " </stringConstant>\n";
    }
    else if (tokentype::KEYWORD == tt)
    { // kw const
        std::cout << "term: kw const" << std::endl;
        outStream << indentation << "<keyword> "
                  << kwToString(tokenizer->keyWord()) << " </keyword>\n";
    }
    else if (tokentype::SYMBOL == tt)
    {
        if (')' == tokenizer->symbol())
        { // empty
            outStream << indentation << "</term>\n";
            return;
        }
        if ('(' == tokenizer->symbol())
        { // '(' expression ')'
            std::cout << "term: (expression)" << std::endl;
            outStream << indentation << "<symbol> ( </symbol>\n";
            tokenizer->advance();
            compileExpression();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            if (';' == tokenizer->symbol())
            {
                return;
            } // HERE
            assert(')' == tokenizer->symbol());
            outStream << indentation << "<symbol> ) </symbol>\n";
        }
        else if (unaryOps[0] == tokenizer->symbol() // (sorry)
                 || unaryOps[1] == tokenizer->symbol())
        { // unaryOp term

            std::cout << "term: unaryOp term" << std::endl;
            outStream << indentation << "<symbol> " << tokenizer->symbol() << " </symbol>\n";
            tokenizer->advance();
            compileTerm();
            outStream << indentation << "</term>\n";
            return; // do not advance
        }
        else
        {
            assert(false);
        }
    }
    else
    { // varName | varName[expression] | subroutineCall()
        std::cout << "term: varName" << std::endl;
        assert(tokentype::IDENTIFIER == tokenizer->tokenType());
        // varName
        outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";

        tokenizer->advance();

        if (tokentype::SYMBOL != tokenizer->tokenType())
        {
            assert(false);
        }
        char s = tokenizer->symbol();
        if ('[' == s)
        { // varName[expression]
            std::cout << "term: varName[expression]" << std::endl;
            outStream << indentation << "<symbol> [ </symbol>\n";
            tokenizer->advance();
            compileExpression();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert(']' == tokenizer->symbol());
            outStream << indentation << "<symbol> ] </symbol>\n";
        }
        else if ('(' == s)
        { // subroutineCall()
            std::cout << "term: subroutineName(expressionList)" << std::endl;
            // subroutineName '(' expressionList ')'
            outStream << indentation << "<symbol> ( </symbol>\n";
            tokenizer->advance();
            compileExpressionList();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert(')' == tokenizer->symbol());
            outStream << indentation << "<symbol> ) </symbol>\n";
        }
        else if ('.' == s)
        { // subroutineCall()
            std::cout << "term: (className|varName).subroutineName(expressionList)" << std::endl;
            // (className | varName) '.' subroutineName '(' expressionList ')'
            outStream << indentation << "<symbol> . </symbol>\n";
            tokenizer->advance();
            assert(tokentype::IDENTIFIER == tokenizer->tokenType());
            outStream << indentation << "<identifier> " << tokenizer->identifier() << " </identifier>\n";
            tokenizer->advance();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert('(' == tokenizer->symbol());
            outStream << indentation << "<symbol> ( </symbol>\n";
            tokenizer->advance();
            compileExpressionList();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert(')' == tokenizer->symbol());
            outStream << indentation << "<symbol> ) </symbol>\n";
        }
        else
        {
            outStream << indentation << "</term>\n";
            return;
        } // ?
    }

    tokenizer->advance(); // ;
    outStream << indentation << "</term>\n";
}

void compilationEngine::compileExpressionList()
{
    outStream << indentation << "<expressionList>\n";
    std::cout << "compiling expression list" << std::endl;

    // if empty (only to conform to cmp file)
    if (tokentype::SYMBOL == tokenizer->tokenType() && ')' == tokenizer->symbol())
    {

        outStream << indentation << "</expressionList>\n";
        return;
    }

    // (expression (',' expression)*)?
    compileExpression();
    while (tokentype::SYMBOL == tokenizer->tokenType() && ',' == tokenizer->symbol())
    {

        outStream << indentation << "<symbol> , </symbol>\n";

        tokenizer->advance();
        compileExpression();
    }

    outStream << indentation << "</expressionList>\n";
}

string compilationEngine::kwToString(keyword kw)
{
    switch (kw)
    {
    case keyword::INT:
        return "int";
    case keyword::CHAR:
        return "char";
    case keyword::BOOLEAN:
        return "boolean";
    case keyword::_VOID:
        return "void";
    case keyword::_THIS:
        return "this";
    case keyword::_TRUE:
        return "true";
    case keyword::_FALSE:
        return "false";
    case keyword::NULLVALUE:
        return "null";
    default:
        assert(false);
        break;
    }
}

bool compilationEngine::isClassVarDec(keyword kw)
{
    return keyword::STATIC == kw || keyword::FIELD == kw;
}

bool compilationEngine::isSubroutineDec(keyword kw)
{
    return keyword::CONSTRUCTOR == kw || keyword::METHOD == kw || keyword::FUNCTION == kw;
}

bool compilationEngine::isFundamentalType(keyword kw)
{
    return keyword::_VOID == kw || keyword::INT == kw || keyword::BOOLEAN == kw || keyword::CHAR == kw;
}