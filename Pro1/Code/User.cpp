#include <iostream>
#include <cstring>
#include "User.h"
using namespace std;


User::User(const int _id, const char* _name, const char* _password, const char* _contact, const char* _address, const double _money, const int _credit, Identity _identity) {
	id = _id;
	strcpy(name, _name);
	strcpy(password, _password);
	strcpy(contact, _contact);
	strcpy(address, _address);
	money = _money;
	credit = _credit;
	identity = _identity;
}

User::User() {
	money = -1;
	identity = ADMINIS;
	credit = 0;
}



