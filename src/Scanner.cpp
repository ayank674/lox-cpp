#include <boost\any.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include "Lox.h"
#include "Scanner.h"
#include "Token.h"

using namespace std;

bool Scanner::isAtEnd() {
	// Checks if the whole source is parsed
	return m_current >= m_source.length();
}

char  Scanner::advance() {
	// Reads the current char and move one char forward
	return m_source[m_current++];
}

void Scanner::addToken(const TokenType type, const boost::any literal) {
	// Adds token to m_tokens
	const string& text = m_source.substr(m_start, m_current - m_start); 
	m_tokens.emplace_back(type, text, literal, m_line);
}

void Scanner::addToken(const TokenType type) {
	// add token without literal
	addToken(type, NULL);
}

bool Scanner::match(const char expected) {
	// Check current char and advance
	if (isAtEnd()) return false;
	if (m_source[m_current] != expected) return false;

	m_current++;
	return true;
}

char Scanner::peek() {
	// Get current char without advancing
	if (isAtEnd()) return '\0';
	return m_source[m_current];
}

void Scanner::scanString() {
	// Scan a string literal

	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') m_line++;
		advance();
	}

	// Never reached closing "
	if (isAtEnd()) {
		error(m_line, "Unterminated string.");
	}

	// closing "
	advance();

	// The string literal slicing
	const string& value = m_source.substr(m_start + 1, m_current - m_start - 2);
	addToken(STRING, value);
}

bool Scanner::isDigit(const char c) {
	return c >= '0' && c <= '9';
}

char Scanner::peekNext() {
	// Get next char withour advancing
	if (m_current + 1 >= m_source.length()) return '\0';
	return m_source[m_current + 1];
}

void Scanner::scanNumber() {
	// Scan a number
	while (isDigit(peek())) advance();

	// If it's a double, it contains .
	if (peek() == '.' && isDigit(peekNext())) {
		advance();

		while (isDigit(peek())) advance();
	}

	addToken(NUMBER, stod(m_source.substr(m_start, m_current - m_start)));
}

bool Scanner::isAlpha(const char c) {
	return (c >= 'a' && c <= 'z') ||
		   (c >= 'A' && c <= 'Z') ||
			c == '_';
}

bool Scanner::isAlphaNumeric(const char c) {
	return isAlpha(c) || isDigit(c);
}

void Scanner::scanIdentifier() {
	// Scan for an identifier

	while (isAlphaNumeric(peek())) advance();

	const string& text = m_source.substr(m_start, m_current - m_start);
	
	// Check if it matches a reserved keyword
	auto it = keywords.find(text);
	TokenType type;
	if (it == keywords.end()) type = IDENTIFIER; // No value in our unordered_map
	else type = it->second;

	addToken(type);
}

void Scanner::scanToken() {
	char c = advance();
	switch (c) {
	case '(': addToken(LEFT_PAREN); break;
	case ')': addToken(RIGHT_PAREN); break;
	case '{': addToken(LEFT_BRACE); break;
	case '}': addToken(RIGHT_BRACE); break;
	case ',': addToken(COMMA); break;
	case '.': addToken(DOT); break;
	case '-': addToken(MINUS); break;
	case '+': addToken(PLUS); break;
	case ';': addToken(SEMICOLON); break;
	case '*': addToken(STAR); break;
	case '!':
	addToken(match('=') ? BANG_EQUAL : BANG);
		break;
	case '=':
		addToken(match('=') ? EQUAL_EQUAL : EQUAL);
		break;
	case '<':
		addToken(match('=') ? LESS_EQUAL : LESS);
		break;
	case '>':
		addToken(match('=') ? GREATER_EQUAL : GREATER);
		break;
	case '/':
		if (match('/')) {
			// A comment goes until the end of the line.
			while (peek() != '\n' && !isAtEnd()) advance();
		}
		else if (match('*')) {
			// Until end of block comment
			while (peek() != '*' && !isAtEnd() && peekNext() != '/') advance();

			// Last two */ chars
			advance();
			advance();
		} else {
			addToken(SLASH);
		}
		break;
	case ' ':
	case '\r':
	case '\t':
		// Ignore whitespace.
		break;

	case '\n':
		m_line++;
		break;
	case '"': scanString(); break;
	default: 

		// Either number or identifier

		if (isDigit(c)) {
			scanNumber();
		}
		else if (isAlpha(c)) {
			scanIdentifier();
		} else {
			error(m_line, "Unexpected character.");
		}
		break;
	}
}

void Scanner::scanTokens() {
	// Scanning tokens
	while (!isAtEnd()) {
		m_start = m_current;
		scanToken();
	}

	// Last EOF token
	m_tokens.emplace_back(EOF_TOKEN, "", NULL, m_line);
}

Scanner::Scanner(const string& source)
		: m_source(source)
	{
		scanTokens();
	}

const unordered_map<string, TokenType> Scanner::keywords = {
	// Reserved keywords
		{ "and", AND },
		{ "class" ,  CLASS },
		{ "else" ,   ELSE },
		{ "false",  FALSE },
		{ "for",    FOR },
		{ "fun",    FUN },
		{ "if",     IF },
		{ "nil",    NIL },
		{ "or",     OR },
		{ "print",  PRINT },
		{ "return", RETURN },
		{ "super",  SUPER },
		{ "this",   THIS },
		{ "true",   TRUE },
		{ "var",    VAR },
		{ "while",  WHILE },
	};