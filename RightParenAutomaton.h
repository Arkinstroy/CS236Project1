#ifndef RIGHTPARENAUTOMATON_H
#define RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton
{
public:
    RightParenAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // RIGHTPARENAUTOMATON_H

