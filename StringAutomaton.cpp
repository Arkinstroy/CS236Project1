#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        S1(input);
    }
    else if (static_cast<unsigned long>(index) == input.size()) {
        Sundefined();
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::Sundefined() {
    isUndefined = true;
}

Token *StringAutomaton::CreateToken(std::string input, int lineNumber) {
    return new Token(isUndefined ? TokenType::UNDEFINED : type, input, lineNumber);
}
