#ifndef FUNCTION_H
#define FUNCTION_H

#include "Token.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>

using std::string; using std::vector; using std::list; using std::ostream;


class Function {
    friend ostream &operator<<(ostream &out, Function &func);

    friend ostream &operator<<(ostream &out, const Function &func);


private:

    string name;
    vector<string> parameters;
    list<Token> body;

public:
    Function();

    Function(string name_, vector<string> parameters_, list<Token>::iterator begin, list<Token>::iterator end);

    string getName() const;

    list<Token> getBody(list<Token> &arguments) const;
};


ostream &operator<<(ostream &out, Function &func);

ostream &operator<<(ostream &out, const Function &func);


#endif // !FUNCTION_H
