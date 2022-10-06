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
    for (auto & i : automata) {
        delete i;
    }
    for (auto & token : tokens) {
        delete token;
    }
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
}

void Lexer::Run(std::string& input) {
    this->lineNumber = 1;
    int maxRead;
    Automaton* maxAutomaton;
    
    if (input.size() > 1 || std::isspace(input[0])) {
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
                if (newToken->GetType() != TokenType::COMMENT) {
                    this->tokens.push_back(newToken);
                }
            }
            else {
                maxRead = 1;
                Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), this->lineNumber);
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
    }

    Token* newToken = new Token(TokenType::EOF_TOKEN, "", this->lineNumber);
    this->tokens.push_back(newToken);
}

void Lexer::OutputResults() {
    for (unsigned int i = 0; i < this->tokens.size(); i++) {
        std::cout << this->tokens.at(i)->toString() << std::endl;
    }
    std::cout << "Total Tokens = " << std::to_string(this->tokens.size());
}
