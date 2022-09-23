#include <iostream>
#include "Lexer.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "RightParenAutomaton.h"
#include "LeftParenAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QuestionMarkAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());

    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code

    this->lineNumber = 1;
    unsigned int maxRead;
    Automaton* maxAutomaton;

    while (input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata.at(0);

        int nextNonSpaceIndex = 0;
        while(std::isspace(input[nextNonSpaceIndex])) {
            if (input[nextNonSpaceIndex] == '\n') {
                this->lineNumber++;
            }
            nextNonSpaceIndex++;
        }
        input = input.substr(nextNonSpaceIndex, input.size());

        for (unsigned int i = 0; i < automata.size(); i++) {
            this->inputRead = automata.at(i)->Start(input);
            if (this->inputRead > maxRead) {
                maxRead = this->inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), this->lineNumber);
            this->lineNumber += maxAutomaton->NewLinesRead();
            this->tokens.push_back(newToken);
        }
        else if (maxRead < 0) {
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, 0 - maxRead), this->lineNumber);
            this->lineNumber += maxAutomaton->NewLinesRead();
            this->tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, 1), this->lineNumber);
            this->tokens.push_back(newToken);
        }
        input = input.substr(maxRead, input.size());
        nextNonSpaceIndex = 0;
        while(std::isspace(input[nextNonSpaceIndex])) {
            if (input[nextNonSpaceIndex] == '\n') {
                this->lineNumber++;
            }
            nextNonSpaceIndex++;
        }
        input = input.substr(nextNonSpaceIndex, input.size());
    }
    Token* newToken = new Token(TokenType::EOF_TOKEN, "", this->lineNumber);
    this->tokens.push_back(newToken);

    /*

    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
}

void Lexer::OutputResults() {
    for (unsigned int i = 0; i < this->tokens.size(); i++) {
        std::cout << this->tokens.at(i)->toString() << std::endl;
    }
    std::cout << "Total Tokens = " << std::to_string(this->tokens.size());
}
