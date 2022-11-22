#include "Parser.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

#include <iostream>

Parser::Parser() {

}

Parser::~Parser() {

}

DatalogProgram* Parser::parse(Lexer* lexerInstance) {
    lexer = lexerInstance;
    currIndex = 0;
    currContent = "";
    datalogProgram = new DatalogProgram();

    this->parseDatalogProgram();

    return datalogProgram;
}

void Parser::Match(TokenType matchType) {
    if (lexer->tokens.at(this->currIndex)->GetType() == matchType) {
        currContent = lexer->tokens.at(this->currIndex)->GetDescription();
        currIndex++;
    }
    else {
        throw currIndex;
    }
}

void Parser::Fail(int failIndex) {
    datalogProgram->setFailMessage(lexer->tokens.at(failIndex)->toString());
}

void Parser::parseDatalogProgram() {
    try {
        this->Match(TokenType::SCHEMES);
        this->Match(TokenType::COLON);
        this->parseScheme();
        this->parseSchemeList();
        this->Match(TokenType::FACTS);
        this->Match(TokenType::COLON);
        this->parseFactList();
        this->Match(TokenType::RULES);
        this->Match(TokenType::COLON);
        this->parseRuleList();
        this->Match(TokenType::QUERIES);
        this->Match(TokenType::COLON);
        this->parseQuery();
        this->parseQueryList();
        this->Match(TokenType::EOF_TOKEN);
    }
    catch(int e) {
        this->Fail(e);
    }
}

void Parser::parseSchemeList() {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::ID) {
        this->parseScheme();
        this->parseSchemeList();
    }
}

void Parser::parseFactList() {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::ID) {
        this->parseFact();
        this->parseFactList();
    }
}

void Parser::parseRuleList() {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::ID) {
        this->parseRule();
        this->parseRuleList();
    }
}

void Parser::parseQueryList() {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::ID) {
        this->parseQuery();
        this->parseQueryList();
    }
}

void Parser::parseScheme() {
    this->Match(TokenType::ID);
    Predicate* newPredicate = new Predicate(currContent);
    this->Match(TokenType::LEFT_PAREN);
    this->Match(TokenType::ID);
    newPredicate->addParameter(new Parameter(currContent));
    this->parseIdList(newPredicate);
    this->Match(TokenType::RIGHT_PAREN);
    datalogProgram->schemeList.push_back(newPredicate);
}

void Parser::parseFact() {
    this->Match(TokenType::ID);
    Predicate* newPredicate = new Predicate(currContent);
    this->Match(TokenType::LEFT_PAREN);
    this->Match(TokenType::STRING);
    datalogProgram->domain.insert(currContent);
    newPredicate->addParameter(new Parameter(currContent));
    this->parseStringList(newPredicate);
    this->Match(TokenType::RIGHT_PAREN);
    this->Match(TokenType::PERIOD);
    datalogProgram->factList.push_back(newPredicate);
}

void Parser::parseRule() {
    Rule* newRule = new Rule(this->parseHeadPredicate());
    this->Match(TokenType::COLON_DASH);
    this->parsePredicate(newRule);
    this->parsePredicateList(newRule);
    this->Match(TokenType::PERIOD);
    datalogProgram->ruleList.push_back(newRule);
}

void Parser::parseQuery() {
    this->parsePredicate();
    this->Match(TokenType::Q_MARK);
}

Predicate* Parser::parseHeadPredicate() {
    this->Match(TokenType::ID);
    Predicate* newPredicate = new Predicate(currContent);
    this->Match(TokenType::LEFT_PAREN);
    this->Match(TokenType::ID);
    newPredicate->addParameter(new Parameter(currContent));
    this->parseIdList(newPredicate);
    this->Match(TokenType::RIGHT_PAREN);
    currContent = newPredicate->toString();
    return newPredicate;
}

void Parser::parsePredicate() {
    this->Match(TokenType::ID);
    Predicate* newPredicate = new Predicate(currContent);
    this->Match(TokenType::LEFT_PAREN);
    this->parseParameter(newPredicate);
    this->parseParameterList(newPredicate);
    this->Match(TokenType::RIGHT_PAREN);
    datalogProgram->queryList.push_back(newPredicate);
}

void Parser::parsePredicate(Rule* newRule) {
    this->Match(TokenType::ID);
    Predicate* newPredicate = new Predicate(currContent);
    this->Match(TokenType::LEFT_PAREN);
    this->parseParameter(newPredicate);
    this->parseParameterList(newPredicate);
    this->Match(TokenType::RIGHT_PAREN);
    newRule->addPredicate(newPredicate);
}

void Parser::parsePredicateList(Rule* newRule) {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::COMMA) {
        this->Match(TokenType::COMMA);
        this->parsePredicate(newRule);
        this->parsePredicateList(newRule);
    }
}

void Parser::parseParameterList(Predicate* newPredicate) {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::COMMA) {
        this->Match(TokenType::COMMA);
        this->parseParameter(newPredicate);
        this->parseParameterList(newPredicate);
    }
}

void Parser::parseStringList(Predicate* newPredicate) {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::COMMA) {
        this->Match(TokenType::COMMA);
        this->Match(TokenType::STRING);
        datalogProgram->domain.insert(currContent);
        newPredicate->addParameter(new Parameter(currContent));
        this->parseStringList(newPredicate);
    }
}

void Parser::parseIdList(Predicate* newPredicate) {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::COMMA) {
        this->Match(TokenType::COMMA);
        this->Match(TokenType::ID);
        newPredicate->addParameter(new Parameter(currContent));
        this->parseIdList(newPredicate);
    }
}

void Parser::parseParameter(Predicate* newPredicate) {
    if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::STRING) {
        this->Match(TokenType::STRING);
        newPredicate->addParameter(new Parameter(currContent));
    }
    else if (lexer->tokens.at(this->currIndex)->GetType() == TokenType::ID) {
        this->Match(TokenType::ID);
        newPredicate->addParameter(new Parameter(currContent));
    }
}
