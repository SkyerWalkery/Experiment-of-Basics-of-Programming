#ifndef ASTNODE_H
#define ASTNODE_H

#include <utility>
#include "Token.h"

enum class NodeType {
    UNKNOWN, ERROR, OPERATOR, SIGN, NUMBER, MATH
};
/*
UNKNOWN: 初始状态
ERROR: 该节点有一些莫名其妙的错误
OPERATOR: =,-,/,*
SYMBOL: 变量名，函数名
SIGN: 前置正负号+,-
NUMBER: 只含0-9以及小数点.的常数
*/


//AST树的节点
class ASTnode {
private:
    NodeType type;//节点类型
    double value;//当节点type为NUMBER时，为数据大小
    string op;//表示操作符和名字, 如"+", "*", "x", "sin", 也储存错误信息
    ASTnode *leftChild;
    ASTnode *rightChild;

public:
    //建立节点的函数
    ASTnode();

    ASTnode(NodeType type_, double value_, string op_, ASTnode *left, ASTnode *right);

    NodeType getType() const;

    double getValue() const;

    string getOp() const;

    ASTnode *getLeft() const;

    ASTnode *getRight() const;

};


#endif // !ASTNODE_H
