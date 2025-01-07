#include <iostream>
#include <string>
#include "boost\any.hpp"
#include "Scanner.h"

using namespace std;


Token::Token(const TokenType& type, const string& lexeme, const boost::any literal, const int line)
        : m_type(type), m_lexeme(lexeme), m_literal(literal), m_line(line)
    {
    }

ostream& operator<< (ostream& os, const Token& token) {
    // overloading to print Token
    os << token.m_type << " " << token.m_lexeme << " " << token.m_line;
    return os;
}

ostream& operator<<(ostream& os, const TokenType type)
{
    // Overaloading to print TokenType
    switch (type) {
    case LEFT_PAREN: os << "LEFT_PAREN"; break;
    case RIGHT_PAREN: os << "RIGHT_PAREN"; break;
    case LEFT_BRACE: os << "LEFT_BRACE"; break;
    case RIGHT_BRACE: os << "RIGHT_BRACE"; break;
    case COMMA: os << "COMMA"; break;
    case DOT: os << "DOT"; break;
    case MINUS: os << "MINUS"; break;
    case PLUS: os << "PLUS"; break;
    case SEMICOLON: os << "SEMICOLON"; break;
    case SLASH: os << "SLASH"; break;
    case STAR: os << "STAR"; break;
    case BANG: os << "BANG"; break;
    case BANG_EQUAL: os << "BANG_EQUAL"; break;
    case EQUAL: os << "EQUAL"; break;
    case EQUAL_EQUAL: os << "EQUAL_EQUAL"; break;
    case GREATER: os << "GREATER"; break;
    case GREATER_EQUAL: os << "GREATER_EQUAL"; break;
    case LESS: os << "LESS"; break;
    case LESS_EQUAL: os << "LESS_EQUAL"; break;
    case IDENTIFIER: os << "IDENTIFIER"; break;
    case STRING: os << "STRING"; break;
    case NUMBER: os << "NUMBER"; break;
    case AND: os << "AND"; break;
    case CLASS: os << "CLASS"; break;
    case ELSE: os << "ELSE"; break;
    case FALSE: os << "FALSE"; break;
    case FUN: os << "FUN"; break;
    case FOR: os << "FOR"; break;
    case IF: os << "IF"; break;
    case NIL: os << "NIL"; break;
    case OR: os << "OR"; break;
    case PRINT: os << "PRINT"; break;
    case RETURN: os << "RETURN"; break;
    case SUPER: os << "SUPER"; break;
    case THIS: os << "THIS"; break;
    case TRUE: os << "TRUE"; break;
    case VAR: os << "VAR"; break;
    case WHILE: os << "WHILE"; break;
    case EOF_TOKEN: os << "EOF"; break;
    default: os << "UNKNOWN_TOKEN"; break;
    }
    return os;
}
