#include "Other.h"

void Notice(int option, string str) {
    switch (option) {
        case 0: {
            cout << endl << "===========================================================" << endl
                 << "|              Welcome to use the SQL Lite++!             |\n"
                 << "|                   Author:SkyerWalkery                   |\n"
                 << "|         WebPage: https://github.com/SkyerWalkery        |\n"
                 << "|     We offer some functions of SQL, and for help, you   |\n"
                 << "|     can refer to user manual or input \"HELP XXXX;\"      |\n"
                 << "===========================================================" << endl << endl << endl << endl;

        }
            break;

        case 1:
            cout << "\nThere is something wrong!\n";
            break;


        case 2:
            cout << "\nThe table is successfully created!\n";
            break;

        case 3:
            cout << "\nok!\n";
            break;

        case 4:
            cout << "\nNo such table!\n";
            break;

        case 5:
            cout << "\nTable " << str << " already exits!\n";
            break;

        case 6:
            cout << "\nToo more or less values!\n";
            break;

        case 7:
            cout << "\nPrimary key value repeating!\n";
            break;

        case 8:
            cout << "\nYou've input invalid field(s)!\n";
            break;

        case 9:
            cout << "\nTable " << str << " is successfully changed.\n";
            break;

        case 10:
            cout << "\nYou cannot change the value of primary key of the table.\n";
            break;

        case 11:
            cout << "\nWrong format!\n";
            break;

        case 12:
            cout << "\nTable " << str << " is successfully dropped.\n";
            break;

        case 13: {
            cout << endl << "***********************************************\n" << "Function: Create a table\n"
                 << "Basic Format: \"CREATE TABLE [A] ([B]);\"\n" << "\t" << "A: name of table\n" << "\t"
                 << "B: fields of table, which can be separated by \",\"\n"
                 << "Note: a \"PRIMARY_KEY\"can be attached after a field, which means the field is the primary key\n"
                 << "Example:\n" << "\t" << "CREATE TABLE test (column_one,column_two PRIMARY_KEY);\n" << "\t"
                 << "CREATE TABLE test2(column_one);\n" << "***********************************************\n" << endl;
        }
            break;//HELP CREATE

        case 14: {
            cout << endl << "***********************************************\n"
                 << "Function: Show brief information of all tables\n" << "Basic Format: \"SHOW TABLES;\"\n"
                 << "Example(output):\n" << "\t" << "2 table(s):\n" << "\t"
                 << "student(id PRIMARY_KEY,name,birth_place)\n" << "\t" << "department(name)\n"
                 << "***********************************************\n" << endl;
        }
            break;//HELP SHOW

        case 15: {
            cout << endl << "***********************************************\n" << "Function: Drop a whole table\n"
                 << "Basic Format: \"DROP TABLE [A];\"\n" << "\t" << "A: name of the table to be dropped\n"
                 << "Note: A table that doesn't exit cannot be dropped.\n" << "Example:\n" << "\t"
                 << "DROP TABLE test;\n" << "***********************************************\n" << endl;
        }
            break;//HELP DROP

        case 16: {
            cout << endl << "***********************************************\n"
                 << "Function: Insert record into a table\n" << "Basic Format: \"INSERT INTO [A] VALUES ([B]);\"\n"
                 << "\t" << "A: name of the table\n" << "\t" << "B: values of a record\n" << "Note: \n" << "\t"
                 << "1.Table [A] must exist\n" << "\t"
                 << "2.Number of values and that of fields of table must be equal\n" << "\t"
                 << "3.Value of primary key should be different from primary-key-value of all records in the table\n"
                 << "Example:\n" << "\t" << "INSERT INTO student VALUES (123, Zhang, Harbin);\n"
                 << "***********************************************\n" << endl;
        }
            break;//HELP INSERT

        case 17: {
            cout << endl << "***********************************************\n"
                 << "Function: Insert record into a table\n" << "Basic Format: \"SELECT [A] [B] FROM [C] [D];\"\n"
                 << "\t" << "A: nothing or \"DISTINCT\", which means results won't be repeated\n" << "\t"
                 << "B: fields to select, or\"*\"(all fields)\n" << "\t" << "C: name of the table\n" << "\t"
                 << "D: nothing, or conditions of records, which is like \"WHERE E=e AND(OR) F=f\"\n" << "Note: \n"
                 << "\t" << "1.In the conditions, we do not support any symbol except \"=\"\n" << "\t"
                 << "2.Table [B] must exist\n" << "Example:\n" << "\t" << "SELECT a,b,c FROM student;\n" << "\t"
                 << "SELECT DISTINCT * FROM student;\n" << "\t" << "SELECT * FROM student WHERE a = Zhang;\n" << "\t"
                 << "SELECT * FROM student WHERE a = Wang OR b = USA;\n"
                 << "***********************************************\n" << endl;
        }
            break;//HELP SELECT

        case 18: {
            cout << endl << "***********************************************\n"
                 << "Function: Update values of a table\n" << "Basic Format: \"UPDATE [A] SET [B] [C];\"\n" << "\t"
                 << "A: name of the table\n" << "\t"
                 << "B: target field and value to be updated in a table, which is like \"E=e\"\n" << "\t"
                 << "C: nothing, or conditions of records, which is like \"WHERE E=e AND(OR) F=f\"\n" << "Note: \n"
                 << "\t" << "1.Table [A] must exist\n" << "\t"
                 << "2.In the conditions, we do not support any symbol except \"=\"\n" << "\t"
                 << "3.Values of primary key cannot be updated\n" << "Example:\n" << "\t"
                 << "UPDATE student SET a = Li;\n" << "\t" << "UPDATE student SET a = Li WHERE b = 222 OR c = UK;\n"
                 << "***********************************************\n" << endl;
        }
            break;//HELP UPDATE

        case 19: {
            cout << endl << "***********************************************\n"
                 << "Function: Delete records of a table which meet conditions\n"
                 << "Basic Format: \"DELETE FROM [A] [B];\"\n" << "\t" << "A: name of the table\n" << "\t"
                 << "B: nothing, or conditions of records, which is like \"WHERE E=e AND(OR) F=f\"\n" << "Note: \n"
                 << "\t" << "1.Table [A] must exist\n" << "\t"
                 << "2.In the conditions, we do not support any symbol except \"=\"\n" << "Example:\n" << "\t"
                 << "DELETE FROM student;\n" << "\t" << "DELETE FROM student WHERE a=test AND b=test;\n"
                 << "***********************************************\n" << endl;
        }
            break;//HELP DELETE

        case 20:
            cout << "\nThis table already has a primary key.\n";
            break;

        case 21:
            cout << "\nThis table has no primary key.\n";
            break;

        case 22:
            cout << "\nField repeating!\n";
            break;

        case 23:
            cout << "\nThere is no record in the table!\n";
            break;


        case 24:
            cout << "\nThere are repeating values in the field of the table, so you cannot set the field as primary key.\n";
            break;
    }

}


bool Exit(Sentence &sen) {
    if (sen.split_sen.back().content != ";") {
        return false;
    }

    vector<Token>::iterator iter = sen.split_sen.begin();
    if (iter->content != "EXIT") {
        return false;
    }

    iter++;
    if (iter->content != ";") {
        return false;
    }

    return true;
}