#ifndef UNDEFINEDAUTOMATON_H
#define UNDEFINEDAUTOMATON_H

#include "Automaton.h"

class UndefinedAutomaton : public Automaton
{
public:
    UndefinedAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // UNDEFINEDAUTOMATON_H

