#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include "Automaton.h"

class IDAutomaton : public Automaton
{
public:
    IDAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // IDAUTOMATON_H

