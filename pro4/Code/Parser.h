#ifndef PARSER_H
#define PARSER_H

#include "ASTnode.h"
#include "Variate.h"
#include "Function.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using std::vector; using std::list;


class Parser {
private:
    bool isGood;
    string errMsg;
    vector<Variate> vecVari;
    vector<Function> vecFunc;
    list<Token> mathExpr;//用户输入表达式的部分拷贝, 即可以计算的部分
    list<Token>::iterator itToken;//遍历mathExpr用

public:
    Parser(list<Token> mathExpr_, vector<Variate> vecVari_, vector<Function> vecFunc_);

    /***************构造AST树*****************/
    ASTnode *parse();

private:
    ASTnode *expression0();

    ASTnode *expression1();

    ASTnode *term0();

    ASTnode *term1();

    ASTnode *factor();

    /***************构造AST树*****************/

    bool variSubst();//将变量按其定义展开使其可计算

    bool funcSubst();

public:
    bool good() const;

    string getErrMsg();


};


#endif // !PARSER_H
