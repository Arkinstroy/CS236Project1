#ifndef EOFAUTOMATON_H
#define EOFAUTOMATON_H

#include "Automaton.h"

class EOFAutomaton : public Automaton
{
public:
    EOFAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // EOFAUTOMATON_H

