#ifndef RULESAUTOMATON_H
#define RULESAUTOMATON_H

#include "Automaton.h"

class RulesAutomaton : public Automaton
{
public:
    RulesAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // RULESAUTOMATON_H

