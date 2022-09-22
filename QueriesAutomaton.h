#ifndef QUERIESAUTOMATON_H
#define QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton
{
public:
    QueriesAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // QUERIESAUTOMATON_H

