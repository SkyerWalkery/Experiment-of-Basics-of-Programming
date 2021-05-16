#ifndef Table_h
#define Table_h


#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;
#include "AnaStr.h"
#include "Other.h"


class Table{
public:
    string name;//name of table
    string prim_key;//primary key, the key in the map below
    vector<string> fields;//fields of a table
    int num_col;//number of columns
    vector<map<string, string>> records; /*records, or rows of the table.
                                        Every row is a map, whose value is part of the record and
                                        key is the field the value matches*/

    Table();
    Table(string _name, vector<string> _fields, string _prim_key, int _num_col);
    bool Insert(vector<string> &values);//execute the insert operation
    bool Update(pair<string, string>& upd, vector<pair<string, string>>& conditions, int AND_OR);
    bool Delete(vector<pair<string, string>>& conditions, int AND_OR);
    bool Alter(string fd_name, int Add_Drop, bool is_on_prim);
    string MaxMin(string &fd_name, int max_min);//return max or min of values of a field
    bool TurnLU(int Lower_Upper, vector<string>l_u_fd);//lower or upper values of fields
    void Display();
};

bool CreateTab(Sentence &sen, vector<Table> &tables);//create a table, which contains fields only
bool ShowTab(Sentence &sen, vector<Table> &tables);//show the brief information of all tables
bool InsertInto(Sentence &sen, vector<Table> &tables);
/*analyse the insert statement, bind a table
and call method(Table::Insert()) of class Table*/
bool Select(Sentence& sen, vector<Table>& tables);//select field(s) which meet the conditions
bool UpdateCall(Sentence& sen, vector<Table>& tables);
bool DeleteCall(Sentence& sen, vector<Table>& tables);
bool Drop(Sentence& sen, vector<Table>& tables);
bool Help(Sentence& sen);
bool AlterCall(Sentence& sen, vector<Table>& tables);
bool Count(Sentence& sen, vector<Table>& tables);
bool MaxMinCall(Sentence& sen, vector<Table>& tables);
Table CreateFrom(vector<string>fields, string primary_key, Table &table_orin, vector<pair<string, string>> condition, int AND_OR);
bool DistinctTab(Table& tab);//delete repeated records in a table

#endif
