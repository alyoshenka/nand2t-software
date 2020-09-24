
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
    outStream << indentation << "<subroutineBody>\n";
    indentation.push_back(tab);

    // {
    // varDec*
    // statements
    // }    

    indentation.pop_back();
    outStream << indentation << "</subroutineBody>\n";
}

void compilationEngineXML::compileParameterList(){
    return;
}

void compilationEngineXML::compileVarDec(){
    return;
}

void compilationEngineXML::compileStatements(){
    return;
}

void compilationEngineXML::compileDo(){
    return;
}

void compilationEngineXML::compileLet(){
    return;
}

void compilationEngineXML::compileWhile(){
    return;
}

void compilationEngineXML::compileReturn(){
    return;
}

void compilationEngineXML::compileIf(){
    return;
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

bool compilationEngineXML::isClassVarDec(keyword kw){
    return keyword::STATIC == kw || keyword::FIELD == kw;
}

bool compilationEngineXML::isSubroutineDec(keyword kw){
    return keyword::CONSTRUCTOR == kw || keyword::METHOD == kw
        || keyword::FUNCTION == kw;
}