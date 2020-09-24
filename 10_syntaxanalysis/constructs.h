#pragma once

#include <string>
using std::string;

enum tokentype{
    INVALID,
    KEYWORD,
    SYMBOL,
    IDENTIFIER,
    INT_CONST,
    STRING_CONST
};

enum keyword{
    NULLVALUE,
    CLASS,
    CONSTRUCTOR,
    FUNCTION,
    METHOD,
    FIELD,
    STATIC,
    VAR,   
    INT,
    CHAR,
    BOOLEAN,     
    VOID,
    TRUE,
    FALSE,
    THIS,   
    LET,
    DO,
    IF,
    ELSE,
    WHILE,
    RETURN,          
};

const string keywords[] = {
    "null", "class", "constructor", "function", "method", 
    "field", "static", "var", "int", "char", "boolean", 
    "void", "true", "false", "this", "let", 
    "do", "if", "else", "while", "return"
};

const int int_max = 32767;

const char symbols[] = { 
    '{', '}', '(', ')', '[', ']', '.',
    ',', ';', '+', '-', '*', '/', '&',
    '|', '<', '>', '=', '~'
};

const string symbolString =
    "{}()[].,;+-*/&|<>=~";

const char ops[] = {
    '+', '-', '*', '/', '&', '|',
    '<', '>', '='
};

const char unaryOps[] = {
    '~', '-'
};

const string keywordConstants[] = {
    "true", "false", "null", "this"
};

const char tab = '\t';