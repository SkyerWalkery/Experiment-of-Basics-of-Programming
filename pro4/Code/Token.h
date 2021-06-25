#ifndef TOKEN_H
#define TOKEN_H

#include<string>

using std::string;


enum class TokenType {
    VARIATE, FUNCTION, UNDEFINED, CONSTANT, SYMBOL, KEYWORD, UNKNOWN
};

/*
VARIATE:变量   CONSTANT:常量,如3, 5.66, 12  
SYMBOL:符号, 如+,-,*,(,=   KEYWORD:关键字, 如Var, Func
*/

class Token {
private:
    TokenType type;
    string content;

public:
    explicit Token(string content);

    Token(TokenType type, string content);

    TokenType getType() const;

    string getCont() const;

    void setType(TokenType type);
};


#endif