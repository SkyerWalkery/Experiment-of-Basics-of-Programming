#include "Token.h"


Token::Token(string _content) : type(TokenType::UNKNOWN), content(std::move(_content)) {}

Token::Token(TokenType _type, string _content) : type(_type), content(std::move(_content)) {}

TokenType Token::getType() const {
    return type;
}

string Token::getCont() const {
    return content;
}

void Token::setType(TokenType _type) {
    this->type = _type;
}
