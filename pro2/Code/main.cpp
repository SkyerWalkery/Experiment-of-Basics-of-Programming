#include "Table.h"
//#include "AnaStr.h"
#include "File.h"
//#include "Other.h"


int main() {
    vector<Table> tables;
    vector<Table>::iterator table_on;
    Read(tables);

    Notice(0);

    while (true) {
        char in_sen[201];
        cin.getline(in_sen, 201);
        Sentence sen(in_sen);
        sen.Split();
        //sen.OutPut();
        switch (sen.Analyse()) {
            case -1: {
                Notice(11);
            }
                break;


            case 0: {
                if (!Exit(sen)) {
                    Notice(1);
                    continue;
                }
                Write(tables);
                return 0;
            }
                break;

            case 1: {
                if (!CreateTab(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Notice(2);
                Write(tables);
            }
                break;

            case 2: {
                if (!ShowTab(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 3: {
                if (!InsertInto(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 4: {
                if (!Select(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 5: {
                if (!UpdateCall(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 6: {
                if (!DeleteCall(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 7: {
                if (!Drop(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 8: {
                if (!Help(sen)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 9: {
                if (!AlterCall(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 40: {
                if (!Count(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;

            case 41: {
                if (!MaxMinCall(sen, tables)) {
                    //Notice(1);
                    continue;
                }
                Write(tables);
            }
                break;
        }

    }

    return 0;
}
