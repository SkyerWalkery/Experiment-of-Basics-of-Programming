#ifndef EVALUATE_H
#define EVALUATE_H

#include "Parser.h"
#include <cmath>


class Evaluate {
    bool isGood;
    string errMsg;
public:
    Evaluate();

    double eval(ASTnode *ast);//分析AST树, 计算
    void delAST(ASTnode *ast);//释放AST树占用内存

    string getErrMsg() const;

    bool good() const;
};


#endif // !EVALUATE_H
