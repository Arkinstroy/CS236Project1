#ifndef PERIODAUTOMATON_H
#define PERIODAUTOMATON_H

#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // PERIODAUTOMATON_H

