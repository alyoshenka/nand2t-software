
#include "compilationEngineXML.h"

compilationEngineXML::compilationEngineXML(jackTokenizer* _tokenizer, string outputFile){
    tokenizer = _tokenizer;
    outStream.open(outputFile);
    compileClass();
    outStream.close();
}

void compilationEngineXML::compileClass(){
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
        kw = tokenizer->keyWord();
    }
    

    // symbol } 


    outStream << "</class>";
}

void compilationEngineXML::compileClassVarDec(){
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
}

// NOT DONE
void compilationEngineXML::compileParameterList(){
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
}

void compilationEngineXML::compileStatements(){   
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
        assert(tokentype::KEYWORD == tt);
        kw = tokenizer->keyWord();
    }

    compileReturn();
    tokenizer->advance();
}

void compilationEngineXML::compileDo(){
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
    // 'if' '(' expression ')' '{' statements '}'
    // ('else' '{' statements '}')?

    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::IF == tokenizer->keyWord());
    outStream << indentation << "<keyword> if </keyword>\n";
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
    return;
}

void compilationEngineXML::compileTerm(){
    return;
}

void compilationEngineXML::compileExpressionList(){
    return;
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