#ifndef QUESTIONMARKAUTOMATON_H
#define QUESTIONMARKAUTOMATON_H

#include "Automaton.h"

class QuestionMarkAutomaton : public Automaton
{
public:
    QuestionMarkAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // QUESTIONMARKAUTOMATON_H

