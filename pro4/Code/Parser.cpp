#include "Parser.h"



Parser::Parser(list<Token> mathExpr_, vector<Variate> vecVari_, vector<Function> vecFunc_) : isGood(true),
                                                                                             mathExpr(std::move(mathExpr_)),
                                                                                             vecVari(std::move(vecVari_)),
                                                                                             vecFunc(std::move(vecFunc_)) {

    this->mathExpr.emplace_back(Token("#"));
    //EOF符号，解决itToken到达end()时尝试读取的问题. 使用emplace_back而非push_back, 基于CLion的建议
    itToken = mathExpr.begin();
}


ASTnode *Parser::parse() {
    return expression0();
}


ASTnode *Parser::expression0() {
    ASTnode *t0_node = term0();
    ASTnode *e1_node = expression1();

    return new ASTnode(NodeType::OPERATOR, 0, "+", t0_node, e1_node);
}


ASTnode *Parser::expression1() {
    ASTnode *t0_node, *e1_node;
    string tokCont = itToken->getCont();

    if (tokCont == "+") {
        ++itToken;
        t0_node = term0(), e1_node = expression1();
        return new ASTnode(NodeType::OPERATOR, 0, "+", t0_node, e1_node);
    }

    else if (tokCont == "-") {
        ++itToken;
        t0_node = term0(), e1_node = expression1();
        return new ASTnode(NodeType::OPERATOR, 0, "-", t0_node, e1_node);
    }

    else {
        return new ASTnode(NodeType::NUMBER, 0, "", nullptr, nullptr);
    }

}


ASTnode *Parser::term0() {
    ASTnode *f_node = factor();
    ASTnode *t1_node = term1();
    return new ASTnode(NodeType::OPERATOR, 0, "*", f_node, t1_node);
}


ASTnode *Parser::term1() {
    ASTnode *f_node, *t1_node;
    string tokCont = itToken->getCont();

    if (tokCont == "*") {
        ++itToken;
        f_node = factor(), t1_node = term1();
        return new ASTnode(NodeType::OPERATOR, 0, "*", f_node, t1_node);
    }

    else if (tokCont == "/") {
        ++itToken;
        f_node = factor(), t1_node = term1();
        return new ASTnode(NodeType::OPERATOR, 0, "/", f_node, t1_node);
    }

    else {
        return new ASTnode(NodeType::NUMBER, 1, "", nullptr, nullptr);
    }
}


ASTnode *Parser::factor() {
    ASTnode *node;
    string tokCont = itToken->getCont();
    TokenType tokTp = itToken->getType();

    if (tokTp == TokenType::CONSTANT) {
        ++itToken;
        double value = stod(tokCont);
        return new ASTnode(NodeType::NUMBER, value, "", nullptr, nullptr);
    }

    else if (tokTp == TokenType::VARIATE) {
        if (!variSubst())
            return new ASTnode(NodeType::ERROR, 0, "Variate Error", nullptr, nullptr);

        return factor();//因为插入的是"(...)"形式, 故转factor()处理
    }

    else if (tokTp == TokenType::FUNCTION) {
        if (!funcSubst())
            return new ASTnode(NodeType::ERROR, 0, "Funtion Error", nullptr, nullptr);

        return factor();//因为插入的是"(...)"形式, 故转factor()处理
    }

    else if (tokCont == "(") {
        ++itToken;
        node = expression0();

        //匹配括号
        if (itToken->getCont() == ")")
            ++itToken;
        else {
            isGood = false;
            errMsg += "Error: Mismatched parentheses\n";
            return new ASTnode(NodeType::ERROR, 0, "Mismatched parentheses", nullptr, nullptr);
        }

        return node;
    }

    else if (tokCont == "-") {
        ++itToken;
        node = factor();
        return new ASTnode(NodeType::SIGN, 0, "-", node, nullptr);
    }

    else if (tokCont == "+") {
        ++itToken;
        node = factor();
        return new ASTnode(NodeType::SIGN, 0, "+", node, nullptr);
    }

    else if (tokTp == TokenType::KEYWORD) {
        std::transform(tokCont.begin(), tokCont.end(), tokCont.begin(), ::tolower);
        if (tokCont == "sin") {
            ++itToken;
            node = factor();
            return new ASTnode(NodeType::MATH, 0, "sin", node, nullptr);
        }
        else if (tokCont == "cos") {
            ++itToken;
            node = factor();
            return new ASTnode(NodeType::MATH, 0, "cos", node, nullptr);
        }
        else if (tokCont == "tan") {
            ++itToken;
            node = factor();
            return new ASTnode(NodeType::MATH, 0, "tan", node, nullptr);
        }
        else if (tokCont == "sqrt") {
            ++itToken;
            node = factor();
            return new ASTnode(NodeType::MATH, 0, "sqrt", node, nullptr);
        }
        else if (tokCont == "lg") {
            ++itToken;
            node = factor();
            return new ASTnode(NodeType::MATH, 0, "lg", node, nullptr);
        }
        else if (tokCont == "abs") {
            ++itToken;
            node = factor();
            return new ASTnode(NodeType::MATH, 0, "abs", node, nullptr);
        }
        else {
            this->isGood = false;
            errMsg += "Error: Wrong format\n";
            return new ASTnode(NodeType::ERROR, 0, tokCont, nullptr, nullptr);
        }//出现识别范围外的字符, ERROR
    }

    else {
        this->isGood = false;
        errMsg += "Error: Wrong format\n";
        return new ASTnode(NodeType::ERROR, 0, "Cannot identify" + tokCont, nullptr, nullptr);
    }//出现识别范围外的字符, ERROR
}


bool Parser::good() const{
    return this->isGood;
}


string Parser::getErrMsg() {
    return this->errMsg;
}

bool Parser::variSubst() {
    list<Token> sub;
    for (const auto &vari0 : vecVari)
        if (itToken->getCont() == vari0.getName()) {
            sub = vari0.getBody();
            break;
        }
    if (sub.empty()) {
        isGood = false;
        errMsg += "Error: \"" + itToken->getCont() + "\"has not been defined \n";
        return false;
    }

    sub.emplace_front(Token(TokenType::SYMBOL, "("));
    sub.emplace_back(Token(TokenType::SYMBOL, ")"));

    //对变量进行替换处理
    auto it0 = sub.begin();
    itToken = mathExpr.erase(itToken);
    mathExpr.splice(itToken, sub);
    itToken = it0;

    return true;
}

bool Parser::funcSubst() {
    list<Token> sub;
    auto funcBeg = itToken;//存储函数开始的地方

    //获取参数列表
    list<Token> arguments;
    auto arguBeg = ++itToken;
    if (itToken->getCont() != "(")
        return false;
    unsigned closed = 0, open = 1;//俩种括号数量
    while (open > closed) {
        ++itToken;
        if (itToken->getCont() == "(")
            open++;
        else if (itToken->getCont() == ")")
            closed++;
    }
    auto arguEnd = ++itToken, funcEnd = itToken;
    arguments.assign(arguBeg, arguEnd);

    //传递实参, 获取表达式
    itToken = funcBeg;
    for (const auto &func0 : vecFunc)
        if (itToken->getCont() == func0.getName()) {
            sub = func0.getBody(arguments);
            break;
        }
    if (sub.empty()) {
        isGood = false;
        errMsg += "Error: Argument(s) match failure\n";
        return false;
    }

    sub.emplace_front(Token(TokenType::SYMBOL, "("));
    sub.emplace_back(Token(TokenType::SYMBOL, ")"));


    //对变量进行替换处理
    auto it0 = sub.begin();
    itToken = mathExpr.erase(funcBeg, funcEnd);
    mathExpr.splice(itToken, sub);
    itToken = it0;

    return true;
}

