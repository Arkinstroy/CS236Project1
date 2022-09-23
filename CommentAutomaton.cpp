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
    else if (input[index] == input.size()){
        Serr();
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
    if (input[index] == '\n' || index == input.size()) {

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
    else if (index == input.size()) {
        Serr();
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}