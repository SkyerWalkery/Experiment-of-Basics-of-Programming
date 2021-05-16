#define DEBUG

#include "Table.h"


Table::Table(string _name, vector<string> _fields, string _prim_key = "_NULL_", int _num_col = 0) {
    name = _name;
    prim_key = _prim_key;
    fields.assign(_fields.begin(), _fields.end());
    num_col = _num_col;
}


Table::Table() {
    name = "\0";
    prim_key = "\0";
    num_col = 0;
}


bool Table::Insert(vector<string> &values) {
    if (fields.size() != values.size()) {
        Notice(6);
        return false;
    }

    map<string, string> record;
    vector<string>::iterator fd_it = fields.begin();
    vector<string>::iterator vl_it = values.begin();
    for (; fd_it < fields.end(); fd_it++, vl_it++) {
        if (*fd_it == prim_key) {
            vector<map<string, string>>::iterator rcd_it = records.begin();
            for (; rcd_it < records.end(); rcd_it++) {
                map<string, string>::iterator rcd_vl_it = (*rcd_it).find(prim_key);
                if (rcd_vl_it->second == *vl_it) {
                    Notice(7);
                    return false;
                }
            }
        }//decide if there is already a primary key value that is same as the one to insert
        record.insert(pair<string, string>(*fd_it, *vl_it));
    }

    records.push_back(record);
    return true;
}


bool Table::Update(pair<string, string> &upd, vector<pair<string, string>> &conditions, int AND_OR) {
    vector<map<string, string>>::iterator rcd_it = this->records.begin();
    if (AND_OR == 0) {
        while (rcd_it < this->records.end()) {
            map<string, string>::iterator vl_it = (*rcd_it).find(upd.first);
            if (vl_it != rcd_it->end())
                vl_it->second = upd.second;
            rcd_it++;
        }
    }

    else if (AND_OR == 1 || AND_OR == 2) {
        while (rcd_it < this->records.end()) {
            bool isMeet = true;
            for (vector<pair<string, string>>::iterator cond_it = conditions.begin();
                 cond_it != conditions.end(); cond_it++) {
                string cond_fd = cond_it->first, cond_vl = cond_it->second;
                map<string, string>::iterator vl_it = (*rcd_it).find(cond_fd);
                if (vl_it->second != cond_vl) {
                    isMeet = false;
                    break;
                }
            }
            if (!isMeet) {
                rcd_it++;
                continue;
            }//decide if the record of original table meets the conditions

            map<string, string>::iterator vl_it = (*rcd_it).find(upd.first);
            if (vl_it != rcd_it->end())
                vl_it->second = upd.second;

            rcd_it++;
        }
    }

    else if (AND_OR == 3) {
        while (rcd_it < this->records.end()) {
            bool isMeet = false;
            for (vector<pair<string, string>>::iterator cond_it = conditions.begin();
                 cond_it != conditions.end(); cond_it++) {
                string cond_fd = cond_it->first, cond_vl = cond_it->second;
                map<string, string>::iterator vl_it = (*rcd_it).find(cond_fd);
                if (vl_it->second == cond_vl) {
                    isMeet = true;
                    break;
                }
            }
            if (!isMeet) {
                rcd_it++;
                continue;
            }//decide if the record of original table meets the conditions

            map<string, string>::iterator vl_it = (*rcd_it).find(upd.first);
            if (vl_it != rcd_it->end())
                vl_it->second = upd.second;

            rcd_it++;
        }
    }

    else {
        cout << "Wrong";
        exit(-1);
    }

    return true;
}


bool Table::Delete(vector<pair<string, string>> &conditions, int AND_OR) {
    vector<map<string, string>>::iterator rcd_it = this->records.begin();
    if (AND_OR == 0) {
        while (rcd_it != this->records.end()) {
            rcd_it = this->records.erase(rcd_it);
        }
    }

    else if (AND_OR == 1 || AND_OR == 2) {
        while (rcd_it != this->records.end()) {
            bool isMeet = true;
            for (vector<pair<string, string>>::iterator cond_it = conditions.begin();
                 cond_it != conditions.end(); cond_it++) {
                string cond_fd = cond_it->first, cond_vl = cond_it->second;
                map<string, string>::iterator vl_it = (*rcd_it).find(cond_fd);
                if (vl_it->second != cond_vl) {
                    isMeet = false;
                    break;
                }
            }
            if (!isMeet) {
                rcd_it++;
                continue;
            }//decide if the record of original table meets the conditions

            rcd_it = this->records.erase(rcd_it);
        }
    }

    else if (AND_OR == 3) {
        while (rcd_it != this->records.end()) {
            bool isMeet = false;
            for (vector<pair<string, string>>::iterator cond_it = conditions.begin();
                 cond_it != conditions.end(); cond_it++) {
                string cond_fd = cond_it->first, cond_vl = cond_it->second;
                map<string, string>::iterator vl_it = (*rcd_it).find(cond_fd);
                if (vl_it->second == cond_vl) {
                    isMeet = true;
                    break;
                }
            }
            if (!isMeet) {
                rcd_it++;
                continue;
            }//decide if the record of original table meets the conditions

            rcd_it = this->records.erase(rcd_it);
        }
    }

    else {
        cout << "Wrong";
        exit(-1);
    }

    return true;
}


bool Table::Alter(string fd_name, int Add_Drop, bool is_on_prim) {
    bool fd_exist;
    auto fd_it = this->fields.begin();

    for (; fd_it < fields.end(); fd_it++) {
        if (*fd_it == fd_name) {
            fd_exist = true;
            break;
        }
    }
    if (is_on_prim && Add_Drop == 1) {
        fd_exist = true;
    }
    else if (fd_it == fields.end()) {
        fd_exist = false;
    }


    if (is_on_prim) {
        if (Add_Drop == 0) {
            if (!fd_exist) {
                Notice(8);
                return false;
            }
            if (this->prim_key != "_NULL_") {
                Notice(20);
                return false;
            }
            vector<string> fd_vls;
            for (auto rcd_it = records.begin(); rcd_it < records.end(); rcd_it++) {
                auto vl_it = rcd_it->find(fd_name);
                string temp = vl_it->second;
                fd_vls.push_back(temp);
            }
            if (fd_vls.size() > 1) {
                for (auto it1 = fd_vls.begin(); it1 + 1 < fd_vls.end(); it1++)
                    for (auto it2 = it1 + 1; it2 < fd_vls.end(); it2++)
                        if (*it1 == *it2) {
                            Notice(24);
                            return false;
                        }
            }//check if the values in the field repeat(against conditions of a primary key)

            this->prim_key = fd_name;
        }

        else {
            if (!fd_exist) {
                Notice(8);
                return false;
            }
            if (this->prim_key == "_NULL_") {
                Notice(21);
                return false;
            }
            this->prim_key = "_NULL_";
        }
    }

    else {//if !is_on prim
        if (Add_Drop == 0) {
            if (fd_exist) {
                Notice(22);
                return false;
            }
            this->fields.push_back(fd_name);
            for (auto rcd_it = records.begin(); rcd_it < records.end(); rcd_it++) {
                rcd_it->insert(pair<string, string>(fd_name, "_NULL_"));
            }
            num_col++;
        }

        else {
            if (!fd_exist) {
                Notice(8);
                return false;
            }
            fd_it = fields.erase(fd_it);
            if (this->prim_key == fd_name) {
                this->prim_key = "_NULL_";
            }//don't forget to delete the primary key
            for (auto rcd_it = records.begin(); rcd_it < records.end(); rcd_it++) {
                rcd_it->erase(fd_name);
            }
            num_col--;
        }
    }

    return true;
}


string Table::MaxMin(string &fd_name, int max_min) {
    auto fd_it = fields.begin();
    for (; fd_it < fields.end(); fd_it++) {
        if (*fd_it == fd_name)
            break;
    }
    if (fd_it == fields.end())
        return "_NULL_NO_FD_";

    if (records.empty())
        return "_NULL_NO_RCD_";

    auto rcd_it = records.begin();
    string res = "_NULL_";
    for (; rcd_it < records.end(); rcd_it++) {
        map<string, string>::iterator map_it;
        map_it = rcd_it->find(fd_name);
        if (max_min == 0 && map_it->second > res)
            res = map_it->second;
        else if (max_min == 1 && map_it->second < res)
            res = map_it->second;
        else if (res == "_NULL_")
            res = map_it->second;
    }

    return res;
}


bool Table::TurnLU(int Lower_Upper, vector<string> l_u_fd) {
    for (auto lu_it = l_u_fd.begin(); lu_it < l_u_fd.end(); lu_it++) {
        vector<string>::iterator find_it;
        find_it = find(this->fields.begin(), this->fields.end(), *lu_it);
        if (find_it == this->fields.end()) {
            Notice(8);
            return false;
        }
    }

    for (auto lu_it = l_u_fd.begin(); lu_it < l_u_fd.end(); lu_it++) {
        for (auto rcd_it = this->records.begin(); rcd_it < this->records.end(); rcd_it++) {
            map<string, string>::iterator map_find = rcd_it->find(*lu_it);
            if (Lower_Upper == 1)
                transform(map_find->second.begin(), map_find->second.end(), map_find->second.begin(), ::tolower);
            else
                transform(map_find->second.begin(), map_find->second.end(), map_find->second.begin(), ::toupper);
        }
    }

    return true;
}


void Table::Display() {
    num_col = (int) fields.size();
    for (int i = 0; i < num_col; i++) {
        cout << "+-------------------------";
    }
    cout << "+\n";

    for (int i = 0; i < num_col; i++) {
        cout << "|" << left << setw(25) << fields[i];
    }
    cout << "|\n";

    vector<map<string, string>>::iterator rcd_it = records.begin();
    while (rcd_it < records.end()) {
        for (int i = 0; i < num_col; i++) {
            cout << "+-------------------------";
        }
        cout << "+\n";

        for (int i = 0; i < num_col; i++) {
            string tup = fields[i];
            map<string, string>::iterator vl_it = (*rcd_it).find(tup);
            string str_out = vl_it->second;
            if (str_out == "_NULL_") str_out.clear();
            cout << "|" << left << setw(25) << str_out;
        }
        cout << "|\n";

        rcd_it++;
    }

    for (int i = 0; i < num_col; i++) {
        cout << "+-------------------------";
    }
    cout << "+\n";
}


bool CreateTab(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
#ifdef DEBUG
        cout << "8";
#endif
        return false;
    }
    string namestr;
    vector<string> fieldtemp;
    string _primary_key;

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "CREATE") {
#ifdef DEBUG
        cout << "1";
#endif
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "TABLE") {
#ifdef DEBUG
        cout << "2";
#endif
        Notice(11);
        return false;
    } //decide correctness of first two words

    iter++;
    if (iter->strtype != StrType::PARAMETER) {
#ifdef DEBUG
        cout << "3";
#endif
        Notice(11);
        return false;
    }
    namestr = iter->content;

    iter++;
    if (iter->content != "(") {
#ifdef DEBUG
        cout << "4";
#endif
        Notice(11);
        return false;
    }

    iter++;
    int read_state = 0;
    //0:init  1:after reading a parameter  2:after reading a ","  3:after reading a "PRIMARY_KEY"
    while (iter->content != ")") {
        if (iter->content == ";") {
#ifdef DEBUG
            cout << "5";
#endif
            Notice(11);
            return false;
        }
        else if ((read_state == 0 || read_state == 2) && iter->strtype == StrType::PARAMETER) {
            fieldtemp.push_back(iter->content);
            read_state = 1;
        }
        else if ((read_state == 1 || read_state == 3) && iter->content == ",") {
            read_state = 2;
        }
        else if (read_state == 1 && iter->content == "PRIMARY_KEY") {
            _primary_key = fieldtemp.back();
            read_state = 3;
        }
        else {
#ifdef DEBUG
            cout << "6";
#endif
            Notice(11);
            return false;
        }

        iter++;
    }
    if (read_state == 0 || read_state == 2) {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != ";") {
#ifdef DEBUG
        cout << "7";
#endif
        Notice(11);
        return false;
    }

    for (vector<Table>::iterator tab_it = tables.begin(); tab_it < tables.end(); tab_it++) {
        if (tab_it->name == namestr) {
            Notice(5, namestr);
            return false;
        }
    }//decide if the table to create has a unique name

    if (_primary_key.empty())
        _primary_key = "_NULL_";
    Table table0(namestr, fieldtemp, _primary_key, (int) fieldtemp.size());
    tables.push_back(table0);

#ifdef DEBUG
    table0.Display();
#endif

    return true;
}


bool ShowTab(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
#ifdef DEBUG
        cout << "9";
#endif
        Notice(11);
        return false;
    }

    vector<string> values;
    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "SHOW") {
        Notice(11);
        return false;
    }
    iter++;
    if (iter->content != "TABLES") {
        Notice(11);
        return false;
    }
    iter++;
    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    vector<Table>::iterator tab_it = tables.begin();
    string outstr;
    int num = 0;
    while (tab_it < tables.end()) {
        Table table0 = *tab_it;
        outstr += table0.name;
        outstr += "(";
        for (vector<string>::iterator fd_it = table0.fields.begin(); fd_it < table0.fields.end(); fd_it++) {
            outstr += *fd_it;
            if (*fd_it == table0.prim_key)
                outstr += " PRIMARY_KEY";
            outstr += ",";
        }
        outstr.pop_back();//delete the extra ","
        outstr += ")\n";

        num++, tab_it++;
    }

    outstr.insert(0, to_string(num) + " table(s):\n");

    cout << endl << outstr << endl;

    return true;
}


bool InsertInto(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "INSERT") {
        Notice(11);
        return false;
    }
    iter++;
    if (iter->content != "INTO") {
        Notice(11);
        return false;
    }
    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }

    string tab_name = iter->content;
    vector<Table>::iterator table_on;
    vector<string> values;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    iter++;
    if (iter->content != "VALUES") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "(") {
        Notice(11);
        return false;
    }
    iter++;
    int read_state = 0; //0:init  1:after reading a para  2:after reading a ","
    while (iter->content != ")") {
        if (iter->content == ";") {
            return false;
        }
        else if ((read_state == 0 || read_state == 2) && iter->strtype == StrType::PARAMETER) {
            values.push_back(iter->content);
            read_state = 1;
        }
        else if (read_state == 1 && iter->content == ",") {
            read_state = 2;
        }
        else {
            Notice(11);
            return false;
        }
        iter++;
    }
    if (read_state == 2) {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    if (!(*table_on).Insert(values)) {
        return false;
    }

#ifdef DEBUG
    Table table0 = *table_on;
    table0.Display();
#endif

    return true;
}


bool Select(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "SELECT") {
        Notice(11);
        return false;
    }

    bool isDist = false, isAllFd;
    vector<string> fd_select;
    string tab_name;
    string new_name;
    string prim_key_select = "_NULL_";
    vector<Table>::iterator table_on;
    vector<pair<string, string>> conditions;
    Table table_select;
    bool isCreate = false;
    bool isLmt = false;
    int lmt_num;
    int AND_OR = 0;//0:no condition  1:only one cond  2:two with AND  3:two with OR
    int Lower_Upper = 0;//0:no change  1:lower  2:upper
    vector<string> l_u_fd;

    iter++;
    if (iter->strtype == StrType::KEYWORD && iter->content == "DISTINCT") {
        isDist = true;
        iter++;
    }
    if (iter->strtype == StrType::PUNCTUATION && iter->content == "*") {
        isAllFd = true;
        iter++;
    }
    else {
        int read_state = 0;//0:init  1:after a parameter  2:after a ","
        while (iter->strtype != StrType::KEYWORD && iter->content != ";") {
            if ((read_state == 0 || read_state == 2) && iter->strtype == StrType::PARAMETER) {
                fd_select.push_back(iter->content);
                read_state = 1;
            }
            else if (read_state == 1 && iter->content == ",") {
                read_state = 2;
            }
            else {
                Notice(11);
                return false;
            }
            iter++;
        }
        if (read_state == 2 || read_state == 0) {
            Notice(11);
            return false;
        }
    }

    if (iter->content == "INTO") {
        isCreate = true;
        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            Notice(11);
            return false;
        }

        new_name = iter->content;
        for (auto tab_it = tables.begin(); tab_it < tables.end(); tab_it++) {
            if (tab_it->name == new_name) {
                Notice(5, new_name);
                return false;
            }
        }

        iter++;
    }

    if (iter->content == "LOWER" || iter->content == "UPPER") {
        Lower_Upper = iter->content == "LOWER" ? 1 : 2;

        iter++;
        if (iter->content != "(") {
            Notice(11);
            return false;
        }
        iter++;
        int read_state = 0; //0:init  1:after reading a para  2:after reading a ","
        while (iter->content != ")") {
            if (iter->content == ";") {
                return false;
            }
            else if ((read_state == 0 || read_state == 2) && iter->strtype == StrType::PARAMETER) {
                l_u_fd.push_back(iter->content);
                read_state = 1;
            }
            else if (read_state == 1 && iter->content == ",") {
                read_state = 2;
            }
            else {
                Notice(11);
                return false;
            }
            iter++;
        }
        if (read_state == 2) {
            Notice(11);
            return false;
        }
        iter++;
    }

    if (iter->content != "FROM") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    tab_name = iter->content;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    if (!isAllFd) {
        for (vector<string>::iterator it = fd_select.begin(); it < fd_select.end(); it++) {
            vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), *it);
            if (find_it == table_on->fields.end()) {
                Notice(8);
                return false;
            }//find if there is invalid field input
            if (*find_it == table_on->prim_key) {
                prim_key_select = *find_it;
            }//decide the primary key of the temporary table to create
        }
    }
    else {
        fd_select.assign(table_on->fields.begin(), table_on->fields.end());
        prim_key_select = table_on->prim_key;
    }

    iter++;
    pair<string, string> temppair;
    if (iter->content == "WHERE") {

        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            Notice(11);
            return false;
        }
        temppair.first = iter->content;
        vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), temppair.first);
        if (find_it == table_on->fields.end()) {
            Notice(8);
            return false;
        }//find if there is invalid field input

        iter++;
        if (iter->content != "=") {
            Notice(11);
            return false;
        }

        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            Notice(11);
            return false;
        }
        temppair.second = iter->content;
        conditions.push_back(temppair);

        iter++;
        if (iter->content == "AND" || iter->content == "OR") {
            AND_OR = iter->content == "AND" ? 2 : 3;

            iter++;
            if (iter->strtype != StrType::PARAMETER) {
                Notice(11);
                return false;
            }
            temppair.first = iter->content;
            vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), temppair.first);
            if (find_it == table_on->fields.end()) {
                Notice(8);
                return false;
            }//find if there is invalid field input

            iter++;
            if (iter->content != "=") {
                Notice(11);
                return false;
            }

            iter++;
            if (iter->strtype != StrType::PARAMETER) {
                Notice(11);
                return false;
            }
            temppair.second = iter->content;
            conditions.push_back(temppair);
            iter++;
        }
    }

    if (iter->content == "LIMIT") {
        isLmt = true;
        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            Notice(11);
            return false;
        }
        string strnum = iter->content;
        char cstrnum[9] = "\0";
        strcpy(cstrnum, strnum.c_str());
        lmt_num = atoi(cstrnum);//turn number string into int
        if (lmt_num <= 0) {
            Notice(11);
            return false;
        }
        iter++;
    }

    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    table_select = CreateFrom(fd_select, prim_key_select, *table_on, conditions, AND_OR);
    if (isDist)
        DistinctTab(table_select);

    if (isLmt && lmt_num < table_select.records.size()) {
        auto slt_rcd_it = table_select.records.begin();
        for (int i = 0; i < lmt_num; i++, slt_rcd_it++);
        while (slt_rcd_it != table_select.records.end())
            slt_rcd_it = table_select.records.erase(slt_rcd_it);
    }

    if (Lower_Upper != 0) {
        if (!table_select.TurnLU(Lower_Upper, l_u_fd))
            return false;
    }

    if (isCreate) {
        table_select.name = new_name;
        tables.push_back(table_select);
    }

    table_select.Display();
    return true;
}


bool UpdateCall(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "UPDATE") {
        Notice(11);
        return false;
    }

    vector<Table>::iterator table_on;
    string tab_name;
    pair<string, string> upd;
    vector<pair<string, string>> conditions;
    int AND_OR = 0;//0:no condition  1:only one cond  2:two with AND  3:two with OR
    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    tab_name = iter->content;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    iter++;
    if (iter->content != "SET") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    upd.first = iter->content;
    if (upd.first == table_on->prim_key) {
        Notice(10);
        return false;
    }//avoid repeated values of primary key
    vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), upd.first);
    if (find_it == table_on->fields.end()) {
        Notice(8);
        return false;
    }//find if there is invalid field input

    iter++;
    if (iter->content != "=") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    upd.second = iter->content;

    iter++;
    pair<string, string> temppair;
    if (iter->content == "WHERE") {
        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            return false;
        }
        temppair.first = iter->content;
        vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), temppair.first);
        if (find_it == table_on->fields.end()) {
            Notice(8);
            return false;
        }//find if there is invalid field input

        iter++;
        if (iter->content != "=") {
            Notice(11);
            return false;
        }

        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            Notice(11);
            return false;
        }
        temppair.second = iter->content;
        conditions.push_back(temppair);
        AND_OR = 1;

        iter++;
        if (iter->content == "AND" || iter->content == "OR") {
            AND_OR = (iter->content == "AND") ? 2 : 3;

            iter++;
            if (iter->strtype != StrType::PARAMETER) {
                return false;
            }
            temppair.first = iter->content;
            vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), temppair.first);
            if (find_it == table_on->fields.end()) {
                Notice(8);
                return false;
            }//find if there is invalid field input

            iter++;
            if (iter->content != "=") {
                Notice(11);
                return false;
            }

            iter++;
            if (iter->strtype != StrType::PARAMETER) {
                Notice(11);
                return false;
            }
            temppair.second = iter->content;
            conditions.push_back(temppair);
            iter++;
        }
    }

    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    table_on->Update(upd, conditions, AND_OR);
    Notice(9, table_on->name);
    return true;
}


bool DeleteCall(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "DELETE") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "FROM") {
        Notice(11);
        return false;
    }

    vector<Table>::iterator table_on;
    string tab_name;
    vector<pair<string, string>> conditions;
    int AND_OR = 0;//0:no condition  1:only one cond  2:two with AND  3:two with OR
    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    tab_name = iter->content;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    iter++;
    pair<string, string> temppair;
    if (iter->content == "WHERE") {
        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            return false;
        }
        temppair.first = iter->content;
        vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), temppair.first);
        if (find_it == table_on->fields.end()) {
            Notice(8);
            return false;
        }//find if there is invalid field input

        iter++;
        if (iter->content != "=") {
            Notice(11);
            return false;
        }

        iter++;
        if (iter->strtype != StrType::PARAMETER) {
            Notice(11);
            return false;
        }
        temppair.second = iter->content;
        conditions.push_back(temppair);
        AND_OR = 1;

        iter++;
        if (iter->content == "AND" || iter->content == "OR") {
            AND_OR = (iter->content == "AND") ? 2 : 3;

            iter++;
            if (iter->strtype != StrType::PARAMETER) {
                return false;
            }
            temppair.first = iter->content;
            vector<string>::iterator find_it = find(table_on->fields.begin(), table_on->fields.end(), temppair.first);
            if (find_it == table_on->fields.end()) {
                Notice(8);
                return false;
            }//find if there is invalid field input

            iter++;
            if (iter->content != "=") {
                Notice(11);
                return false;
            }

            iter++;
            if (iter->strtype != StrType::PARAMETER) {
                Notice(11);
                return false;
            }
            temppair.second = iter->content;
            conditions.push_back(temppair);
            iter++;
        }
    }

    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    table_on->Delete(conditions, AND_OR);
    Notice(9, table_on->name);
    return true;
}


bool Drop(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "DROP") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "TABLE") {
        Notice(11);
        return false;
    }

    string tab_name;
    vector<Table>::iterator table_on;
    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    tab_name = iter->content;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    iter++;
    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    Notice(12, table_on->name);
    table_on = tables.erase(table_on);
    return true;
}


bool Help(Sentence &sen) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "HELP") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content == "CREATE") {
        Notice(13);
    }
    else if (iter->content == "SHOW") {
        Notice(14);
    }
    else if (iter->content == "DROP") {
        Notice(15);
    }
    else if (iter->content == "INSERT") {
        Notice(16);
    }
    else if (iter->content == "SELECT") {
        Notice(17);
    }
    else if (iter->content == "UPDATE") {
        Notice(18);
    }
    else if (iter->content == "DELETE") {
        Notice(19);
    }
    else {
        Notice(11);
        return false;
    }


    iter++;
    if (iter->content != ";") {
        Notice(11);
        return false;
    }
    return true;
}


bool AlterCall(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "ALTER") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "TABLE") {
        Notice(11);
        return false;
    }

    vector<Table>::iterator table_on;
    string tab_name;
    int Add_Drop;//0:ADD  1:DROP
    string fd_name;
    bool is_on_prim;

    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    tab_name = iter->content;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    iter++;
    if (iter->content != "ADD" && iter->content != "DROP") {
        Notice(11);
        return false;
    }
    Add_Drop = (iter->content == "ADD" ? 0 : 1);

    iter++;

    if (iter->content == "PRIMARY_KEY") {
        is_on_prim = true;
        iter++;
        if (Add_Drop == 0) {

            if (iter->content != "(") {
                Notice(11);
                return false;
            }

            iter++;
            if (iter->strtype != StrType::PARAMETER) {
                Notice(11);
                return false;
            }
            fd_name = iter->content;

            iter++;
            if (iter->content != ")") {
                Notice(11);
                return false;
            }

            iter++;
        }
        else if (Add_Drop == 1) {
            fd_name = table_on->prim_key;
            //iter++;
        }

    }

    else if (iter->strtype == StrType::PARAMETER) {
        is_on_prim = false;
        fd_name = iter->content;
        iter++;
    }

    else {
        Notice(11);
        return false;
    }

    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    if (!table_on->Alter(fd_name, Add_Drop, is_on_prim)) {
        return false;
    }

    Notice(9, tab_name);
    return true;
}


bool Count(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "SELECT") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "COUNT") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "FROM") {
        Notice(11);
        return false;
    }

    string tab_name;
    vector<Table>::iterator table_on;
    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    tab_name = iter->content;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    iter++;
    if (iter->content != ";") {
        Notice(11);
        return false;
    }

    int num_rcd = 0;
    for (auto rcd_it = table_on->records.begin(); rcd_it < table_on->records.end(); rcd_it++, num_rcd++);
    cout << "Table " << tab_name << " has " << num_rcd << " records.\n";
    return true;
}


bool MaxMinCall(Sentence &sen, vector<Table> &tables) {
    if (sen.split_sen.back().content != ";") {
        Notice(11);
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "SELECT") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "MAX" && iter->content != "MIN") {
        Notice(11);
        return false;
    }

    int max_min = iter->content == "MAX" ? 0 : 1;//0:max  1:min
    string fd_name;
    string tab_name;
    vector<Table>::iterator table_on;
    iter++;
    if (iter->content != "(") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    fd_name = iter->content;

    iter++;
    if (iter->content != ")") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->content != "FROM") {
        Notice(11);
        return false;
    }

    iter++;
    if (iter->strtype != StrType::PARAMETER) {
        Notice(11);
        return false;
    }
    tab_name = iter->content;
    for (table_on = tables.begin(); table_on < tables.end(); table_on++) {
        if (table_on->name == tab_name)
            break;
    }
    if (table_on == tables.end()) {
        Notice(4);
        return false;
    }//find the table user want to operate on

    string res = table_on->MaxMin(fd_name, max_min);
    if (res == "_NULL_NO_RCD_") {
        Notice(23);
        return false;
    }
    else if (res == "_NULL_NO_FD_") {
        Notice(8);
        return false;
    }

    string str1 = max_min == 0 ? "maximum" : "minimum";
    cout << "The " << str1 << " is " << res << endl;
    return true;
}


Table CreateFrom(vector<string> fields, string primary_key, Table &table_orin, vector<pair<string, string>> conditions,
                 int AND_OR) {
    string name = table_orin.name + "\'s child table";
    Table table0(name, fields, primary_key, (int) fields.size());
    vector<string> values;
    vector<map<string, string>>::iterator rcd_it = table_orin.records.begin();
    if (AND_OR == 0) {
        while (rcd_it < table_orin.records.end()) {
            for (vector<string>::iterator fd_it = fields.begin(); fd_it < fields.end(); fd_it++) {
                string value;
                map<string, string>::iterator find_it = (*rcd_it).find(*fd_it);
                value = find_it->second;
                values.push_back(value);
            }
            table0.Insert(values);
            values.clear();
            rcd_it++;
        }
    }

    else if (AND_OR == 1 || AND_OR == 2) {
        while (rcd_it < table_orin.records.end()) {
            bool isMeet = true;
            for (vector<pair<string, string>>::iterator cond_it = conditions.begin();
                 cond_it != conditions.end(); cond_it++) {
                string cond_fd = cond_it->first, cond_vl = cond_it->second;
                map<string, string>::iterator vl_it = (*rcd_it).find(cond_fd);
                if (vl_it->second != cond_vl) {
                    isMeet = false;
                    break;
                }
            }
            if (!isMeet) {
                rcd_it++;
                continue;
            }//decide if the record of original table meets the conditions

            for (vector<string>::iterator fd_it = fields.begin(); fd_it < fields.end(); fd_it++) {
                string value;
                map<string, string>::iterator find_it = (*rcd_it).find(*fd_it);
                value = find_it->second;
                values.push_back(value);
            }
            table0.Insert(values);
            values.clear();
            rcd_it++;
        }
    }

    else if (AND_OR == 3) {
        while (rcd_it < table_orin.records.end()) {
            bool isMeet = false;
            for (vector<pair<string, string>>::iterator cond_it = conditions.begin();
                 cond_it != conditions.end(); cond_it++) {
                string cond_fd = cond_it->first, cond_vl = cond_it->second;
                map<string, string>::iterator vl_it = (*rcd_it).find(cond_fd);
                if (vl_it->second == cond_vl) {
                    isMeet = true;
                    break;
                }
            }
            if (!isMeet) {
                rcd_it++;
                continue;
            }//decide if the record of original table meets the conditions

            for (vector<string>::iterator fd_it = fields.begin(); fd_it < fields.end(); fd_it++) {
                string value;
                map<string, string>::iterator find_it = (*rcd_it).find(*fd_it);
                value = find_it->second;
                values.push_back(value);
            }
            table0.Insert(values);
            values.clear();
            rcd_it++;
        }
    }

    else {
        cout << "Wrong";
        exit(-1);
    }

    return table0;
}


bool DistinctTab(Table &tab) {
    if (tab.records.size() < 2)
        return true;

    vector<map<string, string>>::iterator it1 = tab.records.begin();
    while (it1 < tab.records.end() - 1) {
        vector<map<string, string>>::iterator it2 = it1 + 1;
        while (it2 < tab.records.end()) {

            map<string, string>::iterator mapit1 = (*it1).begin();
            while (mapit1 != (*it1).end()) {
                map<string, string>::iterator mapit2 = (*it2).find(mapit1->first);
                if (mapit2 != (*it2).end() && mapit2->second != mapit1->second)
                    break;
                mapit1++;
            }//My head is spinning

            if (mapit1 == (*it1).end()) {
                it2 = tab.records.erase(it2);
                continue;
            }//operate on it2, instead of it1, which can handle 1.three or more repeated records; 2.avoid repeating deleting the same record

            it2++;
        }
        it1++;
    }

    return true;
}//Delete repeated records of a map