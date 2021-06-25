#include "Evaluate.h"


Evaluate::Evaluate() : isGood(true) {}

double Evaluate::eval(ASTnode *ast) {
    if (ast == nullptr) {
        isGood = false;
        errMsg += "Error: Invalid expression\n";
        return 0;
    }

    NodeType nodeType = ast->getType();
    string nodeOp = ast->getOp();

    if (nodeType == NodeType::NUMBER) {
        return ast->getValue();
    }

    else if (nodeType == NodeType::SIGN) {
        if (nodeOp == "-")
            return -eval(ast->getLeft());
        else
            return eval(ast->getLeft());
    }//前置正负号

    else if (nodeType == NodeType::MATH) {
        if (nodeOp == "sin")
            return sin(eval(ast->getLeft()));
        else if(nodeOp == "cos")
            return cos(eval(ast->getLeft()));
        else if (nodeOp == "tan")
            return tan(eval(ast->getLeft()));
        else if (nodeOp == "sqrt")
            return sqrt(eval(ast->getLeft()));
        else if (nodeOp == "lg")
            return log10(eval(ast->getLeft()));
        else if (nodeOp == "abs")
            return abs(eval(ast->getLeft()));
        else 
            return eval(ast->getLeft());
    }

    else if (nodeType == NodeType::OPERATOR) {
        double num1 = eval(ast->getLeft()), num2 = eval(ast->getRight());
        if (nodeOp == "+") {
            return num2 + num1;
        }
        else if (nodeOp == "-") {
            return num2 - num1;
        }
        else if (nodeOp == "*") {
            return num2 * num1;
        }
        else if (nodeOp == "/") {
            if (num1 < 1e-6 && num1 > -1e-6) {
                isGood = false;
                errMsg += "Error: Arithmetic Exception / by zero\n";
                return 0;
            }
            return num2 / num1;
        }
        
        else {
            /*

            Under Construction...

            */
            return 0.0;
        }
    }

    else { //if (nodeType == NodeType::ERROR) 
        isGood = false;
        errMsg += "ERROR: " + nodeOp + "\n";
        return 0;
    }

    return 0;
}


void Evaluate::delAST(ASTnode *ast) {
    if (ast->getLeft() != nullptr)
        delAST(ast->getLeft());
    if (ast->getRight() != nullptr)
        delAST(ast->getRight());

    delete ast;
}

string Evaluate::getErrMsg() const {
    return this->errMsg;
}

bool Evaluate::good() const {
    return this->isGood;
}


