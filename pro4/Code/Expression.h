#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "ASTnode.h"
#include "Token.h"
#include "Function.h"
#include "Variate.h"
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>

using std::string; using std::list; using std::ostream; 
using std::transform; using std::set; using std::cout;


class Expression {
private:
    list<Token> lstToken;
    bool isGood;
    string errMsg;

public:
    Expression();

    explicit Expression(const string &inStr);

    int check(vector<Function> &vecFunc, vector<Variate> &vecVari);//初始化后检查, 检查内容见定义

    void def(vector<Function> &vecFunc, vector<Variate> &vecVari);

    void update(vector<Function> &vecFunc, vector<Variate> &vecVari);

    void show(vector<Function> &vecFunc, vector<Variate> &vecVari);

    void help();//用户帮助

    list<Token> getMathExpr();

    static bool isCh(char ch);//是否是构成变量名或关键字的字符
    static bool isDigit(char ch);//是否是数字类型, 包括'.'
    static bool isSymb(char ch);//是否为符号
    static bool isKeyword(string str);

    string getErrMsg() const;

    bool good() const;
};


#endif // !EXPRESSION_H

