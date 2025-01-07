#pragma once

#include <boost\any.hpp>
#include <iostream>

using namespace std;

enum TokenType {
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	EOF_TOKEN
};

class Token {

public:
	const TokenType m_type;
	const string m_lexeme;
	const boost::any m_literal;
	const int m_line;

	Token(const TokenType& type, const string& lexeme, const boost::any literal, const int line);
};

// Overload << operator for TokenType
ostream& operator<<(ostream& os, const TokenType type);

// Overload << operator for Token
ostream& operator<< (ostream& os, const Token& token);