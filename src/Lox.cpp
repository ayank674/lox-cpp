#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Scanner.h"

using namespace std;

bool hadError = false;

void runFile(const string& path);
void runPrompt();

int main(int argc, char* argv[]) {

    if (argc > 2) { // Incorrect use of arguments
        cout << "Usage: jlox [script]" << endl;
        exit(64);
    }
    else if (argc == 2) {
        runFile(argv[1]);
    }
    else { 
        // run in REPL
        runPrompt();
    }
}

void run(const string& source) {
    Scanner sc(source);

    // Test by printing the tokens
    for (const Token& token : sc.m_tokens) {
        cout << token << endl;
    }
}

void runFile(const string& path) {
    // Read file in binary mode
    ifstream file(path, ios::binary);

    if (!file) {
        throw ios_base::failure("Error occurred while accessing file");
    }

    ostringstream oss;
    oss << file.rdbuf();

    if (hadError) { exit(65); }
}

void runPrompt() {
    // REPL mode (interactive)
    string prompt;
    while (getline(cin, prompt)) {
        run(prompt);
    }

    hadError = false;
}

void report(const int line, const string& where, const string& message) {
    cout << "[line " << line << "] Error" << where << ": " << message << endl;
    hadError = true;
}

void error(const int line, const string& message) {
    report(line, string(), message);
}