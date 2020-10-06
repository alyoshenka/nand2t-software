#pragma once

#include <string>
using std::string;

enum varKind{
    NONE,
    STATIC,
    FIELD,
    ARG,
    VAR
};

enum segment{
    CONST,
    ARG,
    LOCAL,
    STATIC,
    THIS,
    THAT,
    POINTER,
    TEMP
};

const char* segmentStrings[] = {
    "const", "arg", "local", "static", 
    "this", "that", "pointer", "temp"
};

enum command{
    ADD,
    SUB,
    NEG,
    EQ,
    GT,
    LT,
    AND,
    OR,
    NOT
};

const char* commandStrings[] = {
    "add", "sub", "neg", "eq", 
    "gt", "lt", "and", "or", "not"
}

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

const string ops = {
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