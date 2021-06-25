#include "Variate.h"


Variate::Variate() = default;


Variate::Variate(string name_, list<Token>::iterator begin, list<Token>::iterator end) : name(std::move(name_)) {
    this->body.assign(begin, end);
}


string Variate::getName() const {
    return this->name;
}


list<Token> Variate::getBody() const {
    return this->body;
}


void Variate::setBody(list<Token>::iterator begin, list<Token>::iterator end) {
    this->body.clear();
    this->body.assign(begin, end);
}


ostream &operator<<(ostream &out, Variate &vari) {
    out << vari.name << " = ";
    for (const auto &tok : vari.body) {
        out << tok.getCont();
        if (tok.getType() != TokenType::FUNCTION)
            out << ' ';
    }
    return out;
}

ostream &operator<<(ostream &out, const Variate &vari) {
    out << vari.name << " = ";
    for (const auto &tok : vari.body) {
        out << tok.getCont();
        if (tok.getType() != TokenType::FUNCTION)
            out << ' ';
    }
    return out;
}