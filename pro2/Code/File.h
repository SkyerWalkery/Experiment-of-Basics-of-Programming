#ifndef File_h
#define File_h
#include <fstream>
using namespace std;
#include "Table.h"

bool Read(vector<Table> &tables);
bool Write(vector<Table> &tables);

#endif
