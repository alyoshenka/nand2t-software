
#include "compilationEngineXML.h"

compilationEngineXML::compilationEngineXML(jackTokenizer* _tokenizer, string outputFile){
    tokenizer = _tokenizer;
    outStream.open(outputFile);
    compileClass();
    outStream.close();
}

void compilationEngineXML::compileClass(){
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
    outStream << indentation << "<identifier> " << 
        tokenizer->identifier() << " </identifier>\n";
    
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
    while(isClassVarDec(kw)){
        compileClassVarDec();
        kw = tokenizer->keyWord();
    }
    while(isSubroutineDec(kw)){
        compileSubroutine();
        if(tokentype::KEYWORD != tokenizer->tokenType()) { break; }
        kw = tokenizer->keyWord();
    }
    
    // symbol } 
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert('}' == tokenizer->symbol());
    outStream << "<symbol> } </symbol>\n";

    outStream << "</class>";
}

void compilationEngineXML::compileClassVarDec(){
    std::cout << "compiling classVarDec" << std::endl;
    outStream << indentation << "<classVarDec>\n";
    indentation.push_back(tab);

    // static | field
    outStream << indentation << "<keyword> " <<
        (keyword::STATIC == tokenizer->keyWord() ? "static" : "field")
        << " </keyword>\n";
    // type, identifier or keyword
    tokenizer->advance();
    tokentype tt = tokenizer->tokenType();
    if(tokentype::KEYWORD == tt){
        keyword kw = tokenizer->keyWord();
        outStream << indentation << "<keyword> ";
        // int | char | bool
        if(keyword::INT == kw){
            outStream << "int";
        } else if(keyword::CHAR == kw){
            outStream << "char";
        } else if(keyword::BOOLEAN == kw){
            outStream << "boolean";
        } else { assert(false); }
        outStream << " </keyword>\n";
    } else if(tokentype::IDENTIFIER == tt){
        string id = tokenizer->identifier();
        outStream << indentation << "<identifier> " <<
            id << " </identifier>\n";
    } else { assert(false); }

    // varName
    tokenizer->advance();
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " << 
        tokenizer->identifier() << " </identifier>\n";
    
    // (, type varName)*
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    while(',' == tokenizer->symbol()){
        tokenizer->advance();
        tokentype tt = tokenizer->tokenType();
        if(tokentype::KEYWORD == tt){
            keyword kw = tokenizer->keyWord();
            outStream << indentation << "<keyword> ";
            // int | char | bool
            if(keyword::INT == kw){
                outStream << "int";
            } else if(keyword::CHAR == kw){
                outStream << "char";
            } else if(keyword::BOOLEAN == kw){
                outStream << "boolean";
            } else { assert(false); }
            outStream << " </keyword>\n";
        } else if(tokentype::IDENTIFIER == tt){
            string id = tokenizer->identifier();
            outStream << indentation << "<identifier> " <<
                id << " </identifier>\n";
        } else { assert(false); }

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

void compilationEngineXML::compileSubroutine(){ 
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
    if(keyword::CONSTRUCTOR == kw){ outStream << "constructor"; }
    else if(keyword::FUNCTION == kw){ outStream << "function"; }
    else if(keyword::METHOD == kw){ outStream << "method"; }
    else { assert(false); }
    outStream << " </keyword>\n";

    tokenizer->advance();
    kw = tokenizer->keyWord();
    tt = tokenizer->tokenType();
    // keyword type | identifier type    
    if(tt == tokentype::KEYWORD){
        assert(isFundamentalType(kw));
        outStream << indentation << "<keyword> "
            << kwToString(kw) << " </keyword>\n";
    } else if(tt == tokentype::IDENTIFIER){
        outStream << indentation << "<identifier> "
            << tokenizer->identifier() << " </identifier>\n";
    } else { assert(false); }

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
    outStream << indentation << "<symbol> ) </symbol>\n";

    indentation.pop_back();
    outStream << indentation << "</subroutineDec>\n";   

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
    while(tokentype::KEYWORD == tokenizer->tokenType()
     && keyword::VAR == tokenizer->keyWord()){
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
    tokenizer->advance();
}

// NOT DONE
void compilationEngineXML::compileParameterList(){
    std::cout << "compiling parameter list" << std::endl;
    indentation.push_back(tab);
    // ((type varName) (, type varName)*)?

    // no parameters
    if(tokentype::SYMBOL == tokenizer->tokenType()){
        assert(')' == tokenizer->symbol());
        return;
    }

    // first parameter
    // type
    if(tokentype::KEYWORD == tokenizer->tokenType()){
        keyword kw = tokenizer->keyWord();
        assert(isFundamentalType(kw));
        outStream << indentation << "<keyword> " <<
            kwToString(kw) << " </keyword>\n";
    } else if(tokentype::IDENTIFIER == tokenizer->tokenType()){
        outStream << indentation << "<identifier> " <<
            tokenizer->identifier() << " </identifier>\n";
    } else { assert(false); }

    tokenizer->advance();
    // name
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " <<
        tokenizer->identifier() << " </identifier>\n";

    tokenizer->advance();
    // any other parameters

    // come back to this!

    indentation.pop_back();
}

void compilationEngineXML::compileVarDec(){
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
    if(tokentype::KEYWORD == tt){
        keyword kw = tokenizer->keyWord();
        outStream << indentation << "<keyword> ";
        // int | char | bool
        if(keyword::INT == kw){
            outStream << "int";
        } else if(keyword::CHAR == kw){
            outStream << "char";
        } else if(keyword::BOOLEAN == kw){
            outStream << "boolean";
        } else { assert(false); }
        outStream << " </keyword>\n";
    } else if(tokentype::IDENTIFIER == tt){
        string id = tokenizer->identifier();
        outStream << indentation << "<identifier> " <<
            id << " </identifier>\n";
    } else { assert(false); }

    tokenizer->advance();
    // name
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " <<
        tokenizer->identifier() << " </identifier>\n";

    tokenizer->advance();   
    // (, name)*
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    while(',' == tokenizer->symbol()){
        outStream << indentation << "<symbol> , </symbol>\n";
        tokenizer->advance();
        assert(tokentype::IDENTIFIER == tokenizer->tokenType());
        outStream << indentation << "<identifier> " <<
            tokenizer->identifier() << " </identifier>\n";
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

void compilationEngineXML::compileStatements(){   
    std::cout << "compiling statements" << std::endl;
    // compile until reach return

    tokentype tt = tokenizer->tokenType();
    assert(tokentype::KEYWORD == tt);
    keyword kw = tokenizer->keyWord();
    while(keyword::RETURN != kw){
        // compile statement
        switch(kw){
            case keyword::DO:
                compileDo();
                break;
            case keyword::LET:
                compileLet();
                break;
            case keyword::WHILE:
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
        if(tokentype::SYMBOL == tt && '}' == tokenizer->symbol()) { return; }
        assert(tokentype::KEYWORD == tt);
        kw = tokenizer->keyWord();
    }

    compileReturn();
}

void compilationEngineXML::compileDo(){
    std::cout << "compiling do" << std::endl;
    // 'do' subroutineCall ';'
    //      subroutineName '(' expressionList ')' | ( className | varName )
    //      '.' subroutineName '(' expressionList ')'


    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::DO == tokenizer->keyWord());
    outStream << indentation << "<keyword> do </keyword>\n";

    tokenizer->advance();
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " <<
        tokenizer->identifier() << " </identifier>\n";
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    
    if('.' == tokenizer->symbol()){
        outStream << indentation << "<symbol> . </symbol>\n";
        tokenizer->advance();
        assert(tokentype::IDENTIFIER == tokenizer->tokenType());
        outStream << indentation << "<identifier> " <<
            tokenizer->identifier() << " </identifier>\n";
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
}

void compilationEngineXML::compileLet(){
    std::cout << "compiling let" << std::endl;
    // 'let' varName ('[' expression ']')?  '=' expression ';'

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::LET == tokenizer->keyWord());
    outStream << indentation << "<keyword> let </keyword>\n";
    tokenizer->advance();
    assert(tokentype::IDENTIFIER == tokenizer->tokenType());
    outStream << indentation << "<identifier> " <<
        tokenizer->identifier() << " </identifier>\n";
    tokenizer->advance();
    
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    if('[' == tokenizer->symbol()){
        outStream << indentation << "<symbol> [ </symbol>\n";
        tokenizer->advance();
        compileExpression();
        assert(tokentype::SYMBOL == tokenizer->tokenType());
        assert(']' == tokenizer->symbol());
        outStream << indentation << "<symbol> ] </symbol>\n";
        tokenizer->advance();
        assert(tokentype::SYMBOL == tokenizer->tokenType());
    }
    assert('=' == tokenizer->symbol());
    outStream << indentation << "<symbol> = </symbol>\n";
    tokenizer->advance();
    compileExpression();
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(';' == tokenizer->symbol());
    outStream << indentation << "<symbol> ; </symbol>\n";
    tokenizer->advance();
}

void compilationEngineXML::compileWhile(){
    std::cout << "compiling while" << std::endl;
    // 'while' '(' expression ')' '{' statements '}'
    
    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::WHILE == tokenizer->keyWord());
    outStream << indentation << "<keyword> while </keyword>\n";
    tokenizer->advance();
    assert(tokentype::SYMBOL == tokenizer->symbol());
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
}

void compilationEngineXML::compileReturn(){
    std::cout << "compiling return" << std::endl;
    // 'return' expression? ';'

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::RETURN == tokenizer->keyWord());
    outStream << indentation << "<keyword> return </keyword>\n";
    tokenizer->advance();
    if(tokentype::SYMBOL != tokenizer->tokenType()){
        compileExpression();
    }
    assert(tokentype::SYMBOL == tokenizer->tokenType());
    assert(';' == tokenizer->symbol());
    outStream << indentation << "<symbol> ; </symbol>\n";
    tokenizer->advance();
}

void compilationEngineXML::compileIf(){
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
    if(tokentype::KEYWORD == tokenizer->tokenType() &&
        keyword::ELSE == tokenizer->keyWord()){

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
}

void compilationEngineXML::compileExpression(){
    std::cout << "compiling expression" << std::endl;
    // term (op term)*
    compileTerm();
    std::cout << "post term1: " << tokenizer->token() << std::endl;
    if(tokentype::SYMBOL != tokenizer->tokenType()) { return; }
    while(tokentype::SYMBOL == tokenizer->tokenType() 
        && string::npos != ops.find(tokenizer->symbol())) {
        std::cout << "term: (op term)*" << std::endl;
        // op
        outStream << indentation << "<symbol> " <<
            tokenizer->symbol() << " </symbol>\n";
        tokenizer->advance();
        // term
        compileTerm();  
    }
}

void compilationEngineXML::compileTerm(){
    std::cout << "compiling term" << std::endl;
    // integerConstant | stringConstant | keywordConstant
    // | varName | varName '[' expression ']' | subroutineCall
    // | '(' expression ')' | unaryOp term

    tokentype tt = tokenizer->tokenType();
    if(tokentype::INT_CONST == tt){ // int const
        std::cout << "term: int const" << std::endl;
        outStream << indentation << "<integerConstant> " 
            << tokenizer->intVal() << " <integerConstant>\n";
    } else if(tokentype::STRING_CONST == tt){ // str const
        std::cout << "term: str const" << std::endl;
        outStream << indentation << "<stringConstant> " 
            << tokenizer->stringVal() << " <stringConstant>\n";
    } else if(tokentype::KEYWORD == tt // kw const
        && keywordConstants->find(kwToString(tokenizer->keyWord()))){

        std::cout << "term: kw const" << std::endl;
        outStream << indentation << "<keywordConstant> " 
            << kwToString(tokenizer->keyWord()) << " <keywordConstant>\n";
    } else if(tokentype::SYMBOL == tt){
        if(')' == tokenizer->symbol()) { return; } // empty
        if ('(' == tokenizer->symbol()){ // '(' expression ')'   
            std::cout << "term: (expression)" << std::endl;
            outStream << indentation << "<symbol> ( </symbol>\n";
            tokenizer->advance();
            compileExpression();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert(')' == tokenizer->symbol());
            outStream << indentation << "<symbol> ) </symbol>\n";
        } else if(unaryOps[0] == tokenizer->symbol() // (sorry)
            || unaryOps[1] == tokenizer->symbol()){ // unaryOp term
            
            std::cout << "term: unaryOp term" << std::endl;
            outStream << indentation << "<unaryOp> " <<
                tokenizer->symbol() << " </unaryOp>\n";
            tokenizer->advance();
            compileTerm();
        } else { assert(false); }
    } else{ // varName | varName[expression] | subroutineCall()
        std::cout << "term: varName" << std::endl;
        assert(tokentype::IDENTIFIER == tokenizer->tokenType());
        // varName
        outStream << indentation << "<identifier> " << 
            tokenizer->identifier() << " </identifier>\n";
        
        tokenizer->advance();

        if(tokentype::SYMBOL != tokenizer->tokenType()){ assert(false); }
        char s = tokenizer->symbol();
        if('[' == s){ // varName[expression]
            std::cout << "term: varName[expression]" << std::endl;
            outStream << indentation << "<symbol> [ </symbol>\n";
            tokenizer->advance();
            compileExpression();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert('[' == tokenizer->symbol());
            outStream << indentation << "<symbol> ] </symbol>\n";
        } else if('(' == s){ // subroutineCall()
            std::cout << "term: subroutineName(expressionList)" << std::endl;
            // subroutineName '(' expressionList ')' 
            outStream << indentation << "<symbol> ( </symbol>\n";
            tokenizer->advance();
            compileExpressionList();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert(')' == tokenizer->symbol());
            outStream << indentation << "<symbol> ) </symbol>\n";
        } else if('.' == s){ // subroutineCall()
            std::cout << "term: (className|varName).subroutineName(expressionList)" << std::endl;
            // (className | varName) '.' subroutineName '(' expressionList ')'
            outStream << indentation << "<symbol> . </symbol>\n";
            tokenizer->advance();
            assert(tokentype::IDENTIFIER == tokenizer->tokenType());
            outStream << indentation << "<identifier> " << 
                tokenizer->identifier() << " </identifier>\n";
            tokenizer->advance();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert('(' == tokenizer->symbol());
            outStream << indentation << "<symbol> ( </symbol>\n";
            tokenizer->advance();
            compileExpressionList();
            assert(tokentype::SYMBOL == tokenizer->tokenType());
            assert(')' == tokenizer->symbol());
            outStream << indentation << "<symbol> ) </symbol>\n";
        } else { return; } // ?
    }
    tokenizer->advance(); // ';'
}

void compilationEngineXML::compileExpressionList(){
    std::cout << "compiling expression list" << std::endl;
    // (expression (',' expression)*)?
    compileExpression();
    while(tokentype::SYMBOL == tokenizer->tokenType()
        && ',' == tokenizer->symbol()){

        compileExpression();
    }
}

string compilationEngineXML::kwToString(keyword kw){
    switch (kw)
    {
    case keyword::INT:
        return "int";
        break;
    case keyword::CHAR:
        return "char";
        break;
    case keyword::BOOLEAN:
        return "boolean";
        break;
    case keyword::VOID:
        return "void";
        break;
    default:
        assert(false);
        break;
    }
}

bool compilationEngineXML::isClassVarDec(keyword kw){
    return keyword::STATIC == kw || keyword::FIELD == kw;
}

bool compilationEngineXML::isSubroutineDec(keyword kw){
    return keyword::CONSTRUCTOR == kw || keyword::METHOD == kw
        || keyword::FUNCTION == kw;
}

bool compilationEngineXML::isFundamentalType(keyword kw){
    return keyword::VOID == kw || keyword::INT == kw
        || keyword::BOOLEAN == kw || keyword::CHAR == kw;
}