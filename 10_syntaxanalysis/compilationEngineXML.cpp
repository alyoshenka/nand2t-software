
#include "compilationEngineXML.h"

compilationEngineXML::compilationEngineXML(jackTokenizer* _tokenizer, string outputFile){
    tokenizer = _tokenizer;
    outStream.open(outputFile);
    // compileClass();
    outStream.close();
}

void compilationEngineXML::compileClass(){
    outStream << "<class>\n";

    // keyword class
    indentation.push_back(tab);
    tokenizer->advance();
    assert(tokentype::KEYWORD == tokenizer->tokenType());
    assert(keyword::CLASS == tokenizer->keyWord());
    outStream << indentation << "<keyword> class </keyword\n";

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

    // ...

    // symbol } 


    outStream << "</class>";
}

void compilationEngineXML::compileClassVarDec(){
    return;
}

void compilationEngineXML::compileSubroutine(){
    return;
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