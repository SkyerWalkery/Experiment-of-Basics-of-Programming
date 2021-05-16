#include "AnaStr.h"


string Token::ToStr() {
    return this->content;
}


Sentence::Sentence(char *in_sen) {
    pch = in_sen;
}

void Sentence::Split() {
    while (*pch != '\0') {
        for (int j = 0; j < 40; j++) {
            temp[j] = '\0';
        }

        Token token;
        StrType strtype = StrType::PARAMETER;
        int i = 0;

        if (IsPunc(*pch)) {
            strtype = StrType::PUNCTUATION;
            temp[0] = *pch;
            temp[1] = '\0';
            ++pch;
            token.content = temp;
            token.strtype = strtype;
            split_sen.push_back(token);
            for (; *pch == ' ' && *pch != '\0'; pch++); //skip space
            continue;
        }

        for (; *pch != ' ' && !IsPunc(*pch) && *pch != '\0'; i++, pch++) {
            temp[i] = *pch;
        }
        temp[i] = '\0'; //fetch a single word

        string stemp = temp;
        for (vector<string>::iterator it = keywords.begin(); it < keywords.end(); it++) {
            if (*it == stemp)
                strtype = StrType::KEYWORD;
        }//decide the type of the word

        token.strtype = strtype;
        token.content = temp;
        split_sen.push_back(token);

        for (; *pch == ' ' && *pch != '\0'; pch++); //skip space

    }
}


bool Sentence::IsPunc(char ch) {
    return (ch == ',' || ch == '(' || ch == ')' || ch == ';' || ch == '*' || ch == '=');
}

void Sentence::OutPut() {
    vector<Token>::iterator it = split_sen.begin();
    for (; it < split_sen.end(); it++) {
        cout << it->content << " ";
        if (it->strtype == StrType::KEYWORD)
            cout << "KEYWORD";
        else if (it->strtype == StrType::PARAMETER)
            cout << "PARAMETER";
        else if (it->strtype == StrType::PUNCTUATION)
            cout << "PUNCTUATION";
        cout << endl;
    }
}


int Sentence::Analyse() {
    vector<Token>::iterator it = split_sen.begin();
    if (it == split_sen.end() || (it + 1) == split_sen.end())
        return -1;
    else if (it->content == "EXIT")
        return 0;
    else if (it->content == "CREATE")
        return 1;//create a table
    else if (it->content == "SHOW")
        return 2;
    else if (it->content == "INSERT")
        return 3;
    else if (it->content == "SELECT" && (it + 1)->content == "COUNT")
        return 40;
    else if (it->content == "SELECT" && ((it + 1)->content == "MAX" || (it + 1)->content == "MIN"))
        return 41;
    else if (it->content == "SELECT")
        return 4;
    else if (it->content == "UPDATE")
        return 5;
    else if (it->content == "DELETE")
        return 6;
    else if (it->content == "DROP")
        return 7;
    else if (it->content == "HELP")
        return 8;
    else if (it->content == "ALTER")
        return 9;


    return -1;
}