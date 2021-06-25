#ifndef VARIATE_H
#define VARIATE_H

#include "Token.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>

using std::string; using std::vector; using std::list; using std::ostream;

class Variate {
    friend ostream &operator<<(ostream &out, Variate &vari);

    friend ostream &operator<<(ostream &out, const Variate &vari);


private:

    string name;
    list<Token> body;

public:
    Variate();

    Variate(string name_, list<Token>::iterator begin, list<Token>::iterator end);

    string getName() const;

    list<Token> getBody() const;

    void setBody(list<Token>::iterator begin, list<Token>::iterator end);
};


ostream &operator<<(ostream &out, Variate &vari);

ostream &operator<<(ostream &out, const Variate &vari);


#endif