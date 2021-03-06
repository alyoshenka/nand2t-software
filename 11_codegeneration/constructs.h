#pragma once

#ifndef _constructs
#define _constructs

#include <string>
using std::string;

enum class varKind
{
    NONE,
    STATIC,
    FIELD,
    ARG,
    VAR
};

enum class segment
{
    _CONST,
    ARG,
    LOCAL,
    STATIC,
    _THIS,
    _THAT,
    _POINTER,
    TEMP
};

const string segmentStrings[] = {
    "const", "arg", "local", "static",
    "this", "that", "pointer", "temp"};

enum class command
{
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

const string commandStrings[] = {
    "add", "sub", "neg", "eq",
    "gt", "lt", "and", "or", "not"};

enum class tokentype
{
    INVALID,
    KEYWORD,
    SYMBOL,
    IDENTIFIER,
    INT_CONST,
    STRING_CONST
};

enum class keyword
{
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
    _VOID,
    _TRUE,
    _FALSE,
    _THIS,
    LET,
    DO,
    IF,
    _ELSE,
    _WHILE,
    RETURN
};

const string keywords[] = {
    "null", "class", "constructor", "function", "method",
    "field", "static", "var", "int", "char", "boolean",
    "void", "true", "false", "this", "let",
    "do", "if", "else", "while", "return"};

const int int_max = 32767;

const char symbols[] = {
    '{', '}', '(', ')', '[', ']', '.',
    ',', ';', '+', '-', '*', '/', '&',
    '|', '<', '>', '=', '~'};

const string symbolString =
    "{}()[].,;+-*/&|<>=~";

const string ops = {
    '+', '-', '*', '/', '&', '|',
    '<', '>', '='};

const char unaryOps[] = {
    '~', '-'};

const string keywordConstants[] = {
    "true", "false", "null", "this"};

const char tab = '\t';

#endif