#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string &input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S3(input);
    }
}

void CommentAutomaton::S2(const std::string &input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S4(input);
    }
    else if (static_cast<unsigned long>(index) == input.size()){
        Sundefined();
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void CommentAutomaton::S3(const std::string &input) {
    if (input[index] == '\n' || static_cast<unsigned long>(index) == input.size()) {

    }
    else {
        inputRead++;
        index++;
        S3(input);
    }
}

void CommentAutomaton::S4(const std::string &input) {
    if (input[index] == '#') {
        inputRead++;
    }
    else if (input[index] == '|'){
        inputRead++;
        index++;
        S4(input);
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        S2(input);
        newLines++;
    }
    else if (static_cast<unsigned long>(index) == input.size()) {
        Sundefined();
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void CommentAutomaton::Sundefined() {
    inputRead = 0 - inputRead;
}