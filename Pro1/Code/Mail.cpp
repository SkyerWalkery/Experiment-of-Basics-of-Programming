#include <cstring>
using namespace std;
#include "Mail.h"



Mail::Mail(const int _id, const int _sender_id, const int _reci_id, const char* _sender_name, const char* _reci_name, const char* _mail_time, const char* _content) {
	id = _id;
	sender_id = _sender_id;
	reci_id = _reci_id;
	strcpy(sender_name, _sender_name);
	strcpy(reci_name, _reci_name);
	strcpy(mail_time, _mail_time);
	strcpy(content, _content);
	isread = false;
}


Mail::Mail() {
	id = -1;
	sender_id = -1;
	reci_id = -1;
	strcpy(sender_name, "\0");
	strcpy(reci_name, "\0");
	strcpy(mail_time, "\0");
	strcpy(content, "\0");
	isread = false;
}
