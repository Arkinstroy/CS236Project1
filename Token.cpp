#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    this->type = type;
    this->description = description;
    this->line = line;
}

std::string Token::toString() {
    std::string type = "";
    switch(this->type) {
        case TokenType::COMMA:
            type = "COMMA";
            break;
        case TokenType::PERIOD:
            type = "PERIOD";
            break;
        case TokenType::Q_MARK:
            type = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN:
            type = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            type = "RIGHT_PAREN";
            break;
        case TokenType::COLON:
            type = "COLON";
            break;
        case TokenType::COLON_DASH:
            type = "COLON_DASH";
            break;
        case TokenType::MULTIPLY:
            type = "MULTIPLY";
            break;
        case TokenType::ADD:
            type = "ADD";
            break;
        case TokenType::SCHEMES:
            type = "SCHEMES";
            break;
        case TokenType::FACTS:
            type = "FACTS";
            break;
        case TokenType::RULES:
            type = "RULES";
            break;
        case TokenType::QUERIES:
            type = "QUERIES";
            break;
        case TokenType::ID:
            type = "ID";
            break;
        case TokenType::STRING:
            type = "STRING";
            break;
        case TokenType::COMMENT:
            type = "COMMENT";
            break;
        case TokenType::UNDEFINED:
            type = "UNDEFINED";
            break;
        case TokenType::EOF_TOKEN:
            type = "EOF";
            break;
    }
    return "(" + type + ",\"" + this->description + "\"," + std::to_string(this->line) + ")";
}
