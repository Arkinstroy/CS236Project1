#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <cctype>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    unsigned int lineNumber;
    int inputRead;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    void OutputResults();
    
    // TODO: add other public methods here

};

#endif // LEXER_H

