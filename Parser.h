#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include "Lexer.h"

class Parser {
private:
    int currIndex;
    Lexer* lexer;
    DatalogProgram* datalogProgram;
    std::string currContent;
    void Match(TokenType matchType);

    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    Predicate* parseHeadPredicate();
    void parsePredicate();
    void parsePredicate(Rule* newRule);
    void parsePredicateList(Rule* newRule);
    void parseParameterList(Predicate* newPredicate);
    void parseStringList(Predicate* newPredicate);
    void parseIdList(Predicate* newPredicate);
    void parseParameter(Predicate* newPredicate);

    void Fail(int failIndex);


public:
    Parser();
    ~Parser();

    DatalogProgram* parse(Lexer* lexer);
};


#endif // PARSER_H