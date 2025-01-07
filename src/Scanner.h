#pragma once

#include <unordered_map>
#include <vector>
#include "Token.h"

class Scanner {
private:
	static const unordered_map<string, TokenType> keywords;
	const string m_source;
	int m_start = 0;
	int m_current = 0;
	int m_line = 1;

	bool isAtEnd();
	char advance();
	void addToken(const TokenType type, const boost::any literal);
	void addToken(const TokenType type);
	bool match(const char expected);
	char peek();
	void scanString();
	bool isDigit(const char c);
	char peekNext();
	void scanNumber();
	bool isAlpha(const char c);
	bool isAlphaNumeric(const char c);
	void scanIdentifier();
	void scanToken();
	void scanTokens();


public:
	vector<Token> m_tokens = vector<Token>();

	Scanner(const string& source);
};