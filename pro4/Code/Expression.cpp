#include "Expression.h"


Expression::Expression() : Expression(string("")) {}

Expression::Expression(const string &inStr) : isGood(true) {
    auto cit = inStr.cbegin();
    while (cit != inStr.cend()) {
        string content;
        TokenType type = TokenType::UNKNOWN;

        if (isCh(*cit)) {
            auto tokBeg = cit, tokEnd = cit;
            for (; tokEnd != inStr.cend() && isCh(*tokEnd); ++tokEnd);
            content.assign(tokBeg, tokEnd);
            cit = tokEnd;
        }//包含字母的token

        else if (isDigit(*cit)) {
            auto tokBeg = cit, tokEnd = cit;
            for (; tokEnd != inStr.cend() && isDigit(*tokEnd); ++tokEnd);
            content.assign(tokBeg, tokEnd);
            type = TokenType::CONSTANT;
            cit = tokEnd;
        }//数字

        else if (isSymb(*cit)) {
            content = *cit;
            type = TokenType::SYMBOL;
            ++cit;
        }//符号

        else if (*cit == ' ') {
            ++cit;
            continue;
        }//空格跳过

        else {
            isGood = false;
            string unIdentChar;
            unIdentChar.push_back(*cit);
            errMsg += "Error: Cannot identify \"" + unIdentChar + "\"\n";
            ++cit;
            continue;
        }//出现了奇怪的字符

        Token token0(type, content);
        lstToken.push_back(token0);
    }

}


int Expression::check(vector<Function> &vecFunc, vector<Variate> &vecVari) {
    /*
    检查内容:
    1.括号的匹配
    2.常数格式的正确性, 例如3.3.2会报错
    3.顺便认认变量和函数，读进来时没认
    4.表达式中只允许含有一个"="
    5.是否输入为空
    */
    if (lstToken.begin() == lstToken.end()) {
        isGood = false;
    }

    unsigned numEqualSign = 0;//'='数量
    unsigned numOpenParenthesis = 0, numCloseParenthesis = 0;//'(' ')'数量
    bool isParenthesisMatch = true;//括号是否匹配
    bool isComma = false;//读的上一个是否是逗号

    for (auto it = lstToken.begin(); it != lstToken.end(); ++it) {
        if (it->getType() == TokenType::CONSTANT) {
            isComma = false;
            string cont = it->getCont();
            if (cont.find_first_of('.') != cont.find_last_of('.')) {
                isGood = false;
                errMsg += "Error: Cannot identify \"" + cont + "\"\n";
            }
        }//常数格式的正确性(多个'.')

        else if (it->getType() == TokenType::SYMBOL) {
            if (isComma && it->getCont() != "+" && it->getCont() != "-") {
                isGood = false;
                errMsg += "Error: Wrong use of \",\"\n";
            }//","之后不能加正负号之外的符号
            if (it->getCont() == "(")
                ++numOpenParenthesis;
            else if (it->getCont() == ")")
                ++numCloseParenthesis;
            else if (it->getCont() == "=") {
                ++numEqualSign;
                //"="左右侧的"("")"分别计算
                if (numCloseParenthesis != numOpenParenthesis) {
                    isGood = false;
                    if (isParenthesisMatch)
                        isParenthesisMatch = false;
                    errMsg += "Error: Mismatched parentheses\n";//额外的if, 防止多次报同样的错误
                }
                numCloseParenthesis = (numOpenParenthesis = 0);
                continue;
            }
            else if (it->getCont() == ",") {
                isComma = true;
                continue;
            }
            else
                continue;

            if (numCloseParenthesis > numOpenParenthesis) {
                isGood = false;
                if (isParenthesisMatch) {
                    isParenthesisMatch = false;
                    errMsg += "Error: Mismatched parentheses\n";
                }//额外的if, 防止多次报同样的错误
            }
        }

        else if (it->getType() == TokenType::UNKNOWN) {
            isComma = false;
            string cont = it->getCont();

            if (isKeyword(cont)) {
                it->setType(TokenType::KEYWORD);
                continue;
            }

            for (const auto &func : vecFunc) //让我装个B, 用下范围for
                if (func.getName() == cont)
                    it->setType(TokenType::FUNCTION);
            for (const auto &vari : vecVari)
                if (vari.getName() == cont)
                    it->setType(TokenType::VARIATE);

            if (it->getType() == TokenType::UNKNOWN)
                it->setType(TokenType::UNDEFINED);
        }//判断该串是否为关键字, 变量名, 函数名, 或者还未定义
    }

    if (numCloseParenthesis < numOpenParenthesis) {
        isGood = false;
        if (isParenthesisMatch)
            errMsg += "Error: Mismatched parentheses\n";//额外的if, 防止多次报同样的错误
    }
    if (numEqualSign > 1) {
        isGood = false;
        errMsg += "Error: Mutiple equal signs\n";
    }

    if (!isGood)
        return -1;

    Token headToken = *(lstToken.begin());
    if (headToken.getCont() == "Var" || headToken.getCont() == "Func") {
        def(vecFunc, vecVari);
        return 0;
    }
    else if (headToken.getCont() == "SHOW") {
        show(vecFunc, vecVari);
        return 0;
    }
    else if (headToken.getCont() == "HELP") {
        help();
        return 0;
    }
    else if (numEqualSign == 1) {
        update(vecFunc, vecVari);
        return 0;
    }
    else {
        return 1;
    }
}


void Expression::def(vector<Function> &vecFunc, vector<Variate> &vecVari) {
    auto it = lstToken.begin();

    if (it->getCont() == "Var") {
        ++it;
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }

        if (it->getType() == TokenType::VARIATE) {
            isGood = false;
            errMsg += "Error: \"" + it->getCont() + "\" has been used\n";
            return;
        }
        else if (it->getType() == TokenType::KEYWORD) {
            isGood = false;
            errMsg += "Error: \"" + it->getCont() + "\" is a keyword\n";
            return;
        }
        else if (it->getType() != TokenType::UNDEFINED) {
            isGood = false;
            errMsg += "Error: Wrong Format at \"" + it->getCont() + "\"\n";
            return;
        }//检查要定义的名字的正确性
        string name = it->getCont();

        ++it;
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }
        if (it->getCont() != "=") {
            isGood = false;
            errMsg += "Error: A \"=\" expected\n";
            return;
        }

        ++it;
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }

        auto bodyBeg = it, bodyEnd = it;
        for (; bodyEnd != lstToken.end(); ++bodyEnd) {
            if (bodyEnd->getType() == TokenType::UNDEFINED) {
                isGood = false;
                errMsg += "Error: \"" + bodyEnd->getCont() + "\" has not been defined \n";
                return;
            }
        }

        Variate vari0(name, bodyBeg, bodyEnd);
        vecVari.push_back(vari0);
    }

    else {//elif cont == "Func"
        ++it;
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }

        if (it->getType() == TokenType::FUNCTION) {
            isGood = false;
            errMsg += "Error: \"" + it->getCont() + "\" has been defined\n";
            return;
        }
        else if (it->getType() == TokenType::KEYWORD) {
            isGood = false;
            errMsg += "Error: \"" + it->getCont() + "\" is a keyword\n";
            return;
        }
        else if (it->getType() != TokenType::UNDEFINED) {
            isGood = false;
            errMsg += "Error: Wrong Format at \"" + it->getCont() + "\"\n";
            return;
        }//检查要定义的名字的正确性
        string name = it->getCont();

        ++it;
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }
        if (it->getCont() != "(") {
            isGood = false;
            errMsg += "Error: A \"(\" expected\n";
            return;
        }

        vector<string> parameters;
        short state = -1;//-1:init  0:str  1:"," 2:error
        ++it;
        while (it != lstToken.end()) {
            if ((state == -1 || state == 1) &&
                (it->getType() == TokenType::UNDEFINED || it->getType() == TokenType::VARIATE)) {
                //只要是个非关键字,非函数名(我懒，不想处理这种情况)字符串，就可作为变量
                state = 0;
                string para_temp = it->getCont();
                if (!parameters.empty() && find(parameters.begin(), parameters.end(), para_temp) != parameters.end()) {
                    isGood = false;
                    errMsg += "Error: Parameter \"" + para_temp + "\" repeated\n";
                    return;
                }
                parameters.push_back(it->getCont());

            }
            else if (state == 0 && it->getCont() == ",") {
                state = 1;
            }
            else
                break;
            ++it;
        }
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }
        if (it->getCont() != ")") {
            isGood = false;
            errMsg += "Error: Parameter expected\n";
            return;
        }
        if (state != 0 && state != -1) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }

        ++it;
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }
        if (it->getCont() != "=") {
            isGood = false;
            errMsg += "Error: A \"=\" expected\n";
            return;
        }

        ++it;
        if (it == lstToken.end()) {
            isGood = false;
            errMsg += "Error: Wrong Format\n";
            return;
        }

        auto bodyBeg = it, bodyEnd = it;
        for (; bodyEnd != lstToken.end(); ++bodyEnd) {
            bool isPara = (find(parameters.begin(), parameters.end(), bodyEnd->getCont()) != parameters.end());
            if (bodyEnd->getType() == TokenType::UNDEFINED && !isPara) {
                isGood = false;
                errMsg += "Error: \"" + bodyEnd->getCont() + "\"has not been defined \n";
                return;
            }
        }

        Function func0(name, parameters, bodyBeg, bodyEnd);
        vecFunc.push_back(func0);
    }

}


void Expression::update(vector<Function> &vecFunc, vector<Variate> &vecVari) {
    auto it = lstToken.begin();
    if (it == lstToken.end()) {
        isGood = false;
        errMsg += "Error: Wrong Format\n";
        return;
    }

    if (it->getType() == TokenType::UNDEFINED) {
        isGood = false;
        errMsg += "Error: \"" + it->getCont() + "\" is not defined\n";
        return;
    }
    else if (it->getType() == TokenType::KEYWORD) {
        isGood = false;
        errMsg += "Error: \"" + it->getCont() + "\" is a keyword\n";
        return;
    }
    else if (it->getType() != TokenType::VARIATE) {
        isGood = false;
        errMsg += "Error: Wrong Format at \"" + it->getCont() + "\"\n";
        return;
    }//检查要更新的变量的名字的正确性

    for (auto &vari : vecVari) {
        if (vari.getName() == it->getCont()) {
            ++it;
            if (it == lstToken.end()) {
                isGood = false;
                errMsg += "Error: Wrong Format\n";
                return;
            }
            if (it->getCont() != "=") {
                isGood = false;
                errMsg += "Error: A \"=\" expected\n";
                return;
            }

            ++it;
            if (it == lstToken.end()) {
                isGood = false;
                errMsg += "Error: Wrong Format\n";
                return;
            }

            auto bodyBeg = it, bodyEnd = it;
            for (; bodyEnd != lstToken.end(); ++bodyEnd) {
                if (bodyEnd->getType() == TokenType::UNDEFINED) {
                    isGood = false;
                    errMsg += "Error: \"" + bodyEnd->getCont() + "\"has not been defined \n";
                    return;
                }
            }
            vari.setBody(bodyBeg, bodyEnd);

            break;
        }
    }
}


void Expression::show(vector<Function> &vecFunc, vector<Variate> &vecVari) {
    auto it = lstToken.begin();

    ++it;
    if (it == lstToken.end()) {
        isGood = false;
        errMsg += "Error: Wrong Format\n";
        return;
    }

    if (it->getCont() == "VAR" && (++it) == lstToken.end())
        for (const auto &vari : vecVari)
            std::cout << vari << std::endl;
    else if (it->getCont() == "FUNC" && (++it) == lstToken.end())
        for (const auto &func : vecFunc)
            std::cout << func << std::endl;

    else {
        isGood = false;
        errMsg += "Error: Wrong Format\n";
        return;
    }

}


void Expression::help() {
    cout << "***************************************************\n";
    auto it = lstToken.begin();
    ++it;
    if (it == lstToken.end()) {
        cout 
            << "Format: HELP X1 X2 X3 ..." << std::endl
            << "Xi can be one of words listed below" << std::endl
            << "Math: for help of what mathematical operations are supported" << std::endl
            << "Function: how to define or use a function" << std::endl
            << "Variate: how to define or use a variate" << std::endl;
    }

    while (it != lstToken.end()) {
        if (it->getCont() == "Math")
            cout << "*Math"<<std::endl
            << "Operations:" << std::endl
            << "\t+, -, *, /, sin, cos, tan, sqrt, lg, abs" << std::endl
            << "Example:" << std::endl
            << "\t1+2, 3.4/5, sin 3.14, tan(3.14/3), lg(x), abs(-101.1)" << std::endl << std::endl;
        else if (it->getCont() == "Function")
            cout <<"*Function"<< std::endl
            << "Define:\n\tFunc [Function Name]([parameter list]) = [body]" << std::endl
            << "Use:\n\t[Function Name]([arguments])" << std::endl 
            << "Note:\n\tThere is at least one parameter." << std::endl
            << "Example:\n\tFunc f(x) = x, Func gg(a, b) = a*a/tan(b)" << std::endl 
            << "\tf(3.3), gg(3, 0.314)/2" << std::endl << std::endl;
        else if (it->getCont() == "Variate")
            cout << "*Variate"<< std::endl
            << "Define:\n\tVar [Variate Name] = [body]" << std::endl
            << "Use:\n\t[Variate Name]" << std::endl
            << "Note:\n\tIf a variate's body contain other variate(s), the value will be influenced by it(them)."<< std::endl
            << "Example:\n\tVar x = 2, Var y = x-10, Var z = sin z - cos z" << std::endl
            << "\tx+y, z*2-z" << std::endl << std::endl;

        else {
            isGood = false;
            errMsg += "Error: Cannot find help \""+it->getCont()+"\"\n";
            return;
        }
        ++it;
    }

    cout << "***************************************************\n";
}


list<Token> Expression::getMathExpr() {
    for (const auto &tok : lstToken) {
        if (tok.getType() == TokenType::UNDEFINED) {
            isGood = false;
            errMsg += "Error: \"" + tok.getCont() + "\"has not been defined \n";
        }
    }

    return lstToken;

}


bool Expression::isCh(char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_');
}

bool Expression::isDigit(char ch) {
    return ((ch >= '0' && ch <= '9') || ch == '.');
}

bool Expression::isSymb(char ch) {
    return (ch == '(' || ch == ')' || ch == ',' || ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' );
}

bool Expression::isKeyword(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    set<string> setKeyword = { "func", "var", "help", "show", "sin", "cos", "tan", "sqrt", "history", "lg", "abs"};
    return (setKeyword.find(str) != setKeyword.end());
}

string Expression::getErrMsg() const {
    return this->errMsg;
}

bool Expression::good() const {
    return this->isGood;
}
