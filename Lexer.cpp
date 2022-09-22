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
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "CommaAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());

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

        for (unsigned int i = 0; i < automata.size(); i++) {
            this->inputRead = automata.at(i)->Start(input);
            if (this->inputRead > maxRead) {
                maxRead = this->inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input, this->lineNumber);
            this->lineNumber += maxAutomaton->NewLinesRead();
            this->tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input, this->lineNumber);
            this->tokens.push_back(newToken);
        }
        input = input.substr(maxRead, input.size());
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
