#ifndef SCHEMESAUTOMATON_H
#define SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton
{
public:
    SchemesAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // SCHEMESAUTOMATON_H

