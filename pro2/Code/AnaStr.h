#ifndef AnaStr_h
#define AnaStr_h


#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum class StrType {
    KEYWORD,
    PARAMETER,
    PUNCTUATION
};

class Token {
public:
    StrType strtype;
    string content;

    string ToStr();
};//Contain single word with its type from the sentence a user input


class Sentence {
public:
    vector<string> keywords = {"CREATE", "TABLE", "SHOW", "TABLES", \
                               "PRIMARY_KEY", "INSERT", "INTO", "VALUES", \
                               "DISTINCT", "FROM", "WHERE", "AND", "OR", \
                               "UPDATE", "SET", "DELETE", "DROP", "ALTER", \
                               "ADD", "COUNT", "MAX", "MIN", "LIMIT", "LOWER", \
                               "UPPER"};//keywords for searching

    vector<Token> split_sen;
    char temp[40];//to store single word
    char *pch;//to get

    Sentence(char *in_sen);

    static bool IsPunc(char ch);//decide whether a ch is a punctuation
    void Split(); //split the whole sentence into words
    void OutPut();//output words split, for testing and debugging
    int Analyse();//analyse grammar, meanings of a sentence, return a int which matches a kind of command
};


#endif
