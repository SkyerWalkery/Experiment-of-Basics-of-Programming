#include "Function.h"


Function::Function() = default;


Function::Function(string name_, vector<string> parameters_, list<Token>::iterator begin, list<Token>::iterator end)
        : name(std::move(name_)), parameters(std::move(parameters_)) {
    this->body.assign(begin, end);
}


string Function::getName() const {
    return this->name;
}


list<Token> Function::getBody(list<Token> &arguments) const {
    arguments.pop_front();
    arguments.pop_back();//删去头尾的括号

    list<Token> res = this->body;
    unsigned open = 0, closed = 0;//记录括号
    vector<list<Token>::iterator> arguBeg, arguEnd;//分别储存每个实参的开始与结束位置, 左闭右开
    arguBeg.push_back(arguments.begin());
    for (auto it = arguments.begin(); it != arguments.end(); ++it) {
        if (it->getCont() == "(")
            ++open;
        else if (it->getCont() == ")")
            ++closed;
        else if (it->getCont() == "," && open == closed) {
            arguEnd.push_back(it);
            arguBeg.push_back(++it);
        }
    }
    arguEnd.push_back(arguments.end());
    if (arguBeg.size() != this->parameters.size())
        return {};//参数数量不匹配, 返回空

    //实参的代换
    unsigned index = 0;
    for (const auto &para : parameters) {
        auto it_body = res.begin();
        while (it_body != res.end()) {
            if (it_body->getCont() == para) {
                it_body = res.erase(it_body);
                res.insert(it_body, arguBeg[index], arguEnd[index]);
                //WARNING1: 一定要用insert, 不要用splice, 见Note.txt
                continue;
            }
            ++it_body;
        }
        ++index;
    }

    return res;
}


ostream &operator<<(ostream &out, Function &func) {
    out << func.name << "(";
    string paraLst;
    for (auto &para : func.parameters) {
        paraLst += (para + ", ");
    }
    if (!paraLst.empty()) {
        paraLst.pop_back();
        paraLst.pop_back();
    }
    out << paraLst << ") = ";
    for (const auto &tok : func.body) {
        out << tok.getCont();
        if (tok.getType() != TokenType::FUNCTION)
            out << ' ';
    }
    return out;
}

ostream &operator<<(ostream &out, const Function &func) {
    out << func.name << "(";
    string paraLst;
    for (auto &para : func.parameters) {
        paraLst += (para + ", ");
    }
    if (!paraLst.empty()) {
        paraLst.pop_back();
        paraLst.pop_back();
    }
    out << paraLst << ") = ";
    for (const auto &tok : func.body) {
        out << tok.getCont();
        if (tok.getType() != TokenType::FUNCTION)
            out << ' ';
    }
    return out;
}
