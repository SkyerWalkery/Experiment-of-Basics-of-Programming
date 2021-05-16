#include "File.h"


bool Read(vector<Table> &tables) {
    fstream fin("Table.dat", ios::in);
    if (!fin.is_open()) {
        fin.open("Table.dat", ios::out);
        fin.close();
        return true;
    } //If no such file exit, create it.

    while (fin.good()) {
        string str_temp;
        fin >> str_temp;
        if (fin.eof()) {
            return true;
        }//there is a '\n' at the end of file
        if (str_temp != "$$_HEAD_$$") {
            return false;
        }

        string _name, _prim_key;
        int _num_col;
        vector<string> _fields;
        fin >> _name >> _prim_key >> _num_col;
        for (int i = 0; i < _num_col; i++) {
            string fd_temp;
            fin >> fd_temp;
            _fields.push_back(fd_temp);
        }

        Table table0(_name, _fields, _prim_key, _num_col);
        vector<string> values;
        long long temp_pos = (long) fin.tellg();
        fin >> str_temp;//Attention: record the position before every record to read
        while (str_temp != "$$_END_$$" && fin.good()) {
            fin.seekg(temp_pos);
            for (int i = 0; i < _num_col; i++) {
                string vl_temp;
                fin >> vl_temp;
                values.push_back(vl_temp);
            }
            table0.Insert(values);
            values.clear();
            temp_pos = fin.tellg();
            fin >> str_temp;
        }

        tables.push_back(table0);
    }

    return true;
}


bool Write(vector<Table> &tables) {
    fstream fout("Table.dat", ios::out | ios::trunc);
    if (!fout.is_open()) {
        return false;
    }

    vector<Table>::iterator tab_it = tables.begin();
    while (tab_it < tables.end()) {
        int col_num = tab_it->fields.size();

        fout << "$$_HEAD_$$" << endl << tab_it->name << " " << tab_it->prim_key << " " << tab_it->num_col << endl;
        for (int i = 0; i < col_num; i++) {
            fout << " " << tab_it->fields[i];
        }
        fout << endl;

        vector<map<string, string>>::iterator rcd_it;
        for (rcd_it = tab_it->records.begin(); rcd_it < tab_it->records.end(); rcd_it++) {
            for (int i = 0; i < col_num; i++) {
                map<string, string>::iterator vl_it = (*rcd_it).find(tab_it->fields[i]);
                fout << " " << (*vl_it).second;
            }
            fout << endl;
        }

        fout << "$$_END_$$" << endl << endl;

        tab_it++;
    }
    return true;
}