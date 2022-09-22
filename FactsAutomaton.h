#ifndef FACTSAUTOMATON_H
#define FACTSAUTOMATON_H

#include "Automaton.h"

class FactsAutomaton : public Automaton
{
public:
    FactsAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // FACTSAUTOMATON_H

