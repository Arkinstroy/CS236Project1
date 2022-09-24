#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {
private:
    void S1(const std::string &input);

    void S2(const std::string &input);

    void S3(const std::string &input);

    void S4(const std::string &input);

    void Sundefined();

    bool isUndefined = false;

public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string &input);

    Token *CreateToken(std::string input, int lineNumber);
};

#endif // COMMENTAUTOMATON_H

