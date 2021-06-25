#include "ASTnode.h"



//无变量初始化
ASTnode::ASTnode() : ASTnode(NodeType::UNKNOWN, 0, "", nullptr, nullptr) {}

ASTnode::ASTnode(NodeType type_, double value_, string op_, ASTnode *left, ASTnode *right) : type(type_), value(value_),
                                                                                             op(std::move(op_)), leftChild(left),
                                                                                             rightChild(right) {}


NodeType ASTnode::getType() const {
    return this->type;
}


double ASTnode::getValue() const {
    return this->value;
}


string ASTnode::getOp() const {
    return this->op;
}


ASTnode *ASTnode::getLeft() const {
    return this->leftChild;
}


ASTnode *ASTnode::getRight() const {
    return this->rightChild;
}
