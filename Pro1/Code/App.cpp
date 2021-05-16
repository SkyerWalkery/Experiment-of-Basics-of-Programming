#include "App.h"


Application::Application() {
	FILE* puser = fopen("Data\\User_Data.dat", "rb");
	if (!puser) {
		cout << "Error in place 1";//PLACE1
		exit(-1);
	}
	users_num = 0;
	User user0;
	fread(&user0, sizeof(User), 1, puser);
	while (!feof(puser)) {
		users.push_back(user0);
		users_num++;
		fread(&user0, sizeof(User), 1, puser);
	}
	fclose(puser);//�����û���Ϣ

	FILE* pgoods = fopen("Data\\Goods_Data.dat", "rb");
	if (!pgoods) {
		cout << "Error in place 2";//PLACE2
		exit(-1);
	}
	goodss_num = 0;
	Goods goods0;;
	fread(&goods0, sizeof(Goods), 1, pgoods);
	while (!feof(pgoods)) {
		goodss.push_back(goods0);
		goodss_num++;
		fread(&goods0, sizeof(Goods), 1, pgoods);
	}
	fclose(pgoods);//������Ʒ��Ϣ

	FILE* porder = fopen("Data\\Order_Data.dat", "rb");
	if (!porder) {
		cout << "Error in place 7";//PLACE7
		exit(-1);
	}
	orders_num = 0;
	Order order0;
	fread(&order0, sizeof(Order), 1, porder);
	while (!feof(porder)) {
		orders.push_back(order0);
		orders_num++;
		fread(&order0, sizeof(Order), 1, porder);
	}
	fclose(porder);//���붩����Ϣ

	ifstream in_mail("Data\\Mail_Data.dat", ios::in | ios::binary);
	if (!in_mail.is_open()) {
		cout << "Error in place 12";//PLACE12
		exit(-1);
	}
	Mail mail0;
	in_mail.read((char*)&mail0, sizeof(Mail));
	while (in_mail.good()) {
		mails.push_back(mail0);
		in_mail.read((char*)&mail0, sizeof(Mail));
	}
	in_mail.close();//�����ʼ���Ϣ

	appstate = DEFAULT;
	user_on = users.end();//ָ��һ�������ڵĶ��󣬷�ֹ�Ҹ�
	user_off = users.end();//ָ��һ�������ڵĶ��󣬷�ֹ�Ҹ�
	goods_on = goodss.end();//ָ��һ�������ڵĶ��󣬷�ֹ�Ҹ�
	mail_on = mails.end();//ָ��һ�������ڵĶ��󣬷�ֹ�Ҹ�

	/***********�ô����������ɹ���Ա*************/
	vector<User>::iterator itad;
	for (itad = users.begin(); itad < users.end(); itad++)
		if (itad->id == 10000) break;
	if (itad == users.end()) {
		User user1(10000, "ADMINIS", "PASSWORD", "12315", "Beijing", 999999.9, 1000,  ADMINIS);
		users.push_back(user1);
	}
	//users.erase(users.begin());
	//User user1(10000, "ADMINIS", "PASSWORD", "12315", "Beijing", 999999.9, ADMINIS);
	//users.insert(users.begin(), user1);
}


void Application::Save() {
	FILE* puser = fopen("Data\\User_Data.dat", "w+b");
	if (!puser) {
		cout << "Error in place 3";//PLACE3
		exit(-1);
	}
	for (vector<User>::iterator iter = users.begin(); iter != users.end(); iter++) {
		fwrite(&(*iter), sizeof(User), 1, puser);
	}
	fclose(puser);//����ʱ�û����ݴ����ļ�

	FILE* pgoods = fopen("Data\\Goods_Data.dat", "w+b");
	if (!pgoods) {
		cout << "Error in place 4";//PLACE4
		exit(-1);
	}
	for (vector<Goods>::iterator iter = goodss.begin(); iter != goodss.end(); iter++) {
		fwrite(&(*iter), sizeof(Goods), 1, pgoods);
	}
	fclose(pgoods);//����ʱ��Ʒ���ݴ����ļ�

	FILE* porder = fopen("Data\\Order_Data.dat", "w+b");
	if (!porder) {
		cout << "Error in place 8";//PLACE8
		exit(-1);
	}
	for (vector<Order>::iterator iter = orders.begin(); iter != orders.end(); iter++) {
		fwrite(&(*iter), sizeof(Order), 1, porder);
	}
	fclose(porder);//����ʱ�������ݴ����ļ�

	ofstream out_mail("Data\\Mail_Data.dat", ios::out | ios::binary | ios::trunc);
	if (!out_mail.is_open()) {
		cout << "Error in place 12";//PLACE12
		exit(-1);
	}
	for (vector<Mail>::iterator iter = mails.begin(); iter != mails.end(); iter++)
		out_mail.write((char*)&(*iter), sizeof(Mail));
	out_mail.close();//����ʱ�ʼ����ݴ����ļ�
}


void Application::Window(int option) {
	switch (option) {
	case -2: {
		cout << endl
			<< "===========================================================" << endl
			<< "|              Welcome to use the C2C Monitor!            |\n"
			<< "|                   Author:SkyerWalkery                   |\n"
			<< "|         WebPage: https://github.com/SkyerWalkery        |\n"
			<< "|    Wait patiently for seconds, and then we'll kick off! |\n"
			<< "===========================================================" << endl << endl << endl << endl;
	}break;//��ͷ

	case -1:cout << "************************************************************************" << endl; break;

	case 0: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.Log in                                            |\n"
			<< "| 2.Sign up                                           |\n"
			<< "| 3.Forgot Password?                                  |\n"
			<< "| 4.Exit                                              |\n" 
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;//��ʼ�˵�

	case 1: {
		cout << endl << "Please enter your name: " << endl;
	}break;

	case 2: {
		cout << endl << "Please enter your passord: " << endl;
	}break;

	case 3: {
		cout << endl << "----------Wrong name or password! Back to main menu.----------" << endl << endl;//��¼ʧ��
	}break;

	case 4: {
		cout << endl << "*********You are logged in*********" << endl << endl;//��¼�ɹ�
	}break;

	case 5: {
		cout <<endl<<"-------------The name has been used by someone else-------------"<< endl;
	}break;

	case 6: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.I'm buyer                                        |\n"
			<< "| 2.I'm seller                                       |\n"
			<< "| 3.Manage my information                            |\n" 
			<< "| 4.Top up                                           |\n" 
			<< "| 5.Mail                                             |\n"
			<< "| 6.Log out                                          |\n"
			<< "| 7.Close Account                                    |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;//��ͨ�û��˵�

	case 7: {
		cout << endl << "It's is too long! Try to make it short." << endl;
	}break;

	case 8: {
		cout << endl << "The goods are as belows: " << endl;
	}break;

	case 9: {
		cout << endl << "----------You haven't signed up!----------" << endl << endl;
	}break;

	case 10: {
		cout << endl << "*********You are logged out*********" << endl << endl;//ע���ɹ�
	}break;

	case 11: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.Realease Goods                                   |\n"
			<< "| 2.Manage My Goods                                  |\n"
			<< "| 3.My History Orders                                |\n"
			<< "| 4.Back to the Main Menu                            |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;//������˵�

	case 12: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.Modify the Information                           |\n"
			<< "| 2.Withdraw the Goods                               |\n"
			<< "| 3.Back                                             |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;//�����Ʒ�˵�

	case 13: {
		cout << endl << "Please enter The name of your goods: " << endl;
	}break;

	case 14: {
		cout << endl << "Give it a reasonable price: " << endl;
	}break;

	case 15: {
		cout << endl << "---------The price cannot be negative!----------" << endl;
	}break;

	case 16: {
		cout << endl << "Give it a description which is based on reality: " << endl;
	}break;

	case 17: {
		cout << endl << "Please enter the ID of Goods you want to operate on, which should start with\"M\": " << endl;
	}break;

	case 18: {
		cout << endl << "Please enter the ID in the correct format: " << endl;
	}break;

	case 19: {
		cout << endl << "---------You've input a wrong ID!----------" << endl;
	}break;

	case 20: {
		cout << endl << "The information are as belows." << endl;
	}break;

	case 21: {
		cout << endl << "***********The information is successfully changed.***********" << endl;
	}break;

	case 22: {
		cout << endl << "************The goods is successfully withdrawn.*************" << endl;
	}break;

	case 23: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.Name                                             |\n"
			<< "| 2.Price                                            |\n"
			<< "| 3.Description                                      |\n"
			<< "| 4.Back                                             |\n"
			<< "======================================================" << endl
			<< "What do you want to change? \nEnter the number before the option: " << endl;
	}break;//����޸���Ʒ�˵�

	case 24: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.Name                                             |\n"
			<< "| 2.Password                                         |\n"
			<< "| 3.Contact Information                              |\n"
			<< "| 4.Address                                          |\n"
			<< "| 5.Back                                             |\n"
			<< "======================================================" << endl
			<< "What do you want to change? \nEnter the number before the option: " << endl;
	}break;//�û��޸ĸ�����Ϣ�˵�

	case 25: {
		cout << endl << "Please enter your contact information: " << endl;
	}break;

	case 26: {
		cout << endl << "Please enter your address: " << endl;
	}break;

	case 27: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.See the goods available                          |\n"
			<< "| 2.Search                                           |\n"
			<< "| 3.See my orders                                    |\n"
			<< "| 4.Back                                             |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;//���һ���˵�

	case 28: {
		cout << endl << "-------------Insufficient balance in your account, you need to recharge.-------------" << endl;
	}break;

	case 29: {
		cout << endl << "-------------You cannot buy the goods you release.--------------" << endl;
	}break;

	case 30: {
		cout << endl << "-------------You cannot buy the goods that has been withdrawn or sold.-------------" << endl;
	}break;

	case 31: {
		cout << endl << "*************The deal is compeleted.**************" << endl;
	}break;

	case 32: {
		cout << endl << "*************Your goods is successfully released.*************" << endl;
	}break;

	case 33: {
		cout << endl << "--------------You cannot change the Goods that is sold.----------------" << endl;
	}break;

	case 34: {
		cout << endl << "Top-up amount: " << endl;
	}break;

	case 35: {
		cout << endl << "The amount cannot have cents! Enter again: " << endl;
	}break;

	case 36: {
		cout << endl << "The amount cannot be negative! Enter again: " << endl;
	}break;

	case 37: {
		cout << endl << "Please enter the ID or the name of what you search for: " << endl;
	}break;//������Ʒ

	case 38: {
		cout << endl << "--------------Sorry, we don't have the goods you want.--------------" << endl;
	}break;//������Ʒ

	case 39: {
		cout << endl << "The orders are as belows: " << endl;
	}break;

	case 40: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.See All Goods                                    |\n"
			<< "| 2.Search Goods                                     |\n"
			<< "| 3.Withdraw Goods                                   |\n"
			<< "| 4.See All Orders                                   |\n"
			<< "| 5.See All Users                                    |\n"
			<< "| 6.Suspend or Restore User                          |\n" 
			<< "| 7.Log out                                          |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;//������˵�

	case 41: {
		cout << endl << "Please enter the ID of him or her, which should start with\"U\": " << endl;
	}break;

	case 42: {
		cout << "I'm sorry, your account is suspended.\nFor help, please contact the administrator." << endl;
	}break;

	case 43: {
		cout << endl << "-------------Back to the Last Menu Soon--------------" << endl << endl;
	}break;

	case 44: {
		cout << endl << "************Congratulations! You've signed up!**************" << endl << endl;
	}break;

	case 45: {
		cout << endl << "Enter your password again: " << endl;
	}break;

	case 46: {
		cout << endl << "There is something wrong" << endl;
	}break;

	case 47: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.Buy directly                                     |\n"
			<< "| 2.Back                                             |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;//��Ҷ����˵�

	case 48: {
		cout << endl << "Are you sure?\nEnter \"y\"(yes) or \"n\"(no) (Any other input will be seen as \"no\"): " << endl;
	}break;

	case 49: {
		cout << endl << "******************The user's account is successfully suspended by you.******************" << endl;	
	}break;

	case 50: {
		cout << endl << "******************The user's account is successfully restored by you.******************" << endl;
	}break;

	case 51: {
		cout << endl << "-----------You cannot operate on your own account!-------------" << endl;
	}break;

	case 52: {
		cout << endl << "-----------You haven't set your contact information!-------------" << endl;
	}break;

	case 53: {
		cout << endl << "-----------Invalid number! Back to the main menu soon.-------------" << endl;
	}break;

	case 54: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.+ New Mail                                       |\n"
			<< "| 2.Inbox                                            |\n"
			<< "| 3.Outbox                                           |\n"
			<< "| 4.Back                                             |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;

	case 55: {
		cout << endl << "Please input the content of your mail: " << endl;
	}break;

	case 56: {
		cout << endl << "**************The mail is successfully sent!*****************" << endl;
	}break;

	case 57: {
		cout << endl
			<< "======================================================" << endl
			<< "| 1.Delete                                           |\n"
			<< "| 2.Delete All                                       |\n"
			<< "| 3.Back                                             |\n"
			<< "======================================================" << endl
			<< "What do you want? \nEnter the number before the option: " << endl;
	}break;

	case 58: {
		cout << endl << "Please enter the ID of mail you want to delete, which should start with\"S\": " << endl;
	}break;

	case 59: {
		cout << endl << "**************The mail is successfully deleted!*****************" << endl;
	}break;

	case 60: {
		cout << endl << "----------The password is not allowed!----------" << endl;
	}break;

	case 61: {
		cout << endl << "Your account will be closed forever!(Really so long!)";
	}break;

	case 62: {
		cout << endl << "*************Your account is successfully closed. Thank you for using!****************" << endl;
	}break;

	case 63: {
		cout << endl
			<< "What do you think of the deal?\n"
			<< "------------------------------------------------------" << endl
			<< "| 1.Very Satisfying                                  |\n"
			<< "| 2.Fairly Satisfying                                |\n"
			<< "| 3.Not too Good                                     |\n"
			<< "| 4.Awful                                            |\n"
			<< "------------------------------------------------------" << endl
			<< "Enter the number before the option: " << endl;
	}break;


	default: {
		cout << "This is a egg.\n";
		exit(-1);
	}

	}
}


void Application::Start() {
	Window(-2);
	ForFun();
	
	while (true) {
		if (appstate == DEFAULT) {
			char inputc;
			Window(0);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1':Login(0); break;
			case '2':SignUp(); break;
			case '3':Login(1); break;
			case '4': {
				char confir;
				Window(48);
				confir = cin.get();
				cin.ignore(1024, '\n');
				if (confir != 'y') continue;//����ȷ��

				return;
			}
				break;
			default: {
				cout << endl << "You can only input number from 1 to 3!" << endl;
				continue;//FLAG1
			}
			}
			Save();//����
		}

		else if (appstate == USER_MAIN) {
			char inputc;
			Window(6);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1':appstate = USER_BUY; break;//���һ���˵�
			case '2':appstate = USER_SELL; break;//���һ���˵�
			case '3':appstate = USER_INFO; break;//���������Ϣ
			case '4':TopUp(); break;
			case '5':appstate = MAIL; break;
			case '6': {
				Window(10);
				user_on = users.end();//ָ��һ�������ڵ�
				appstate = DEFAULT;
			}break;//�ǳ��˺�
			case '7': {
				CloseAcc();
				appstate = DEFAULT;
			}break;//ע���˺�
			default: {
				cout << endl << "You can only input number from 1 to 7!" << endl;
				continue;//FLAG1
			}
			}
			Save();//����
		}

		else if (appstate == USER_SELL) {
			char inputc;
			Window(11);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1':Release(); break;//������Ʒ
			case '2':appstate = USER_SELL_GOODS;break;//�鿴���޸���Ʒ
			case '3':CheckOrders(2); break;//�鿴����
			case '4':appstate = USER_MAIN; break;//����
			default: {
				cout << endl << "You can only input number from 1 to 4!" << endl;
				continue;//FLAG1
			}
			}
			Save();//����
		}

		else if (appstate == USER_SELL_GOODS) {
			CheckGoodss(1);
			char inputc;
			Window(12);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1':appstate = USER_SELL_GOODS_MANAG;break;//�޸���Ʒ
			case '2': {
				BindGoods();
				GoodsManag(3);
			}break;//�¼���Ʒ
			case '3':appstate = USER_SELL; break;//����
			default: {
				cout << endl << "You can only input number from 1 to 3!" << endl;
				continue;//FLAG1
			}
			}
			Save();//����
		}

		else if (appstate == USER_SELL_GOODS_MANAG) {
			//if(goods_on != goodss.end())//FLAG5
				BindGoods();//�󶨲�������.��if�жϷ�ֹ�ظ���ʾ��
			char inputc;
			Window(23);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1': {
				GoodsManag(0);
				appstate = USER_SELL_GOODS;
			}break;//�޸���Ʒname
			case '2': {
				GoodsManag(1);
				appstate = USER_SELL_GOODS;
			}break;//�޸���Ʒprice
			case '3': {
				GoodsManag(2);
				appstate = USER_SELL_GOODS;
			}break;//�޸���Ʒdescription
			case '4': {
				appstate = USER_SELL_GOODS;
			}break;//����
			default: {
				cout << endl << "You can only input number from 1 to 4!" << endl;
				continue;//FLAG1
			}
			}
			goods_on = goodss.end();
			Save();//����
		}

		else if (appstate == USER_INFO) {
			CheckUsers(1);
			char inputc;
			Window(24);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1':UserManag(0); break;//�޸�name
			case '2':UserManag(1); break;//�޸�password
			case '3':UserManag(2); break;//�޸���ϵ��ʽ
			case '4':UserManag(3); break;//�޸ĵ�ַ
			case '5':appstate = USER_MAIN; break;//����
			default: {
				cout << endl << "You can only input number from 1 to 5!" << endl;
				continue;//FLAG1
			}
			}
			Save();//����
		}

		else if (appstate == USER_BUY) {
			//CheckGoodss(2);
			char inputc;
			Window(27);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1':appstate = USER_BUY_DIREC; break;//������Ʒ
			case '2':SearchGoods(); break;//����
			case '3':CheckOrders(1); break;//�鿴����
			case '4':appstate = USER_MAIN; break;//����
			default: {
				cout << endl << "You can only input number from 1 to 4!" << endl;
				continue;//FLAG1
			}
			}
			Save();//����
		}

		else if (appstate == ADMINIS_MAIN) {
			char inputc;
			Window(40);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1':CheckGoodss(0); break;//�鿴������Ʒ
			case '2':SearchGoods(); break;//������Ʒ
			case '3': {
				BindGoods();
				GoodsManag(3);
			}break;//�¼���Ʒ
			case '4':CheckOrders(0); break;//�鿴���ж���
			case '5':CheckUsers(0); break;//�鿴�����û�
			case '6': {
				BindUserOff();
				UserManag(4);
			}break;//���������û�
			case '7': {
				Window(10);
				user_on = users.end();//ָ��һ�������ڵ�
				appstate = DEFAULT;
			}//�ǳ��˺�
			default: {
				cout << endl << "You can only input number from 1 to 7!" << endl;
				continue;//FLAG1
			}
			}
			goods_on = goodss.end();
			user_off = users.end();
			Save();//����
		}

		else if (appstate == USER_BUY_DIREC) {
			CheckGoodss(2);
			char inputc;
			Window(47);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1': {
				BindGoods();
				Buy();
				goods_on = goodss.end();
			}break;//������Ʒ
			case '2':appstate = USER_BUY; break;//����
			default: {
				cout << endl << "You can only input number from 1 to 2!" << endl;
				continue;//FLAG1
			}
			}
			Save();//����
		}

		else if (appstate == USER_FROZEN) {
			Window(-1);
			Window(42);
			Window(-1);
			Window(43);
			//_sleep(2000);//����ֹͣ2��
			appstate = DEFAULT;
			Save();//����
		}

		else if (appstate == MAIL) {
			char inputc;
			Window(54);
			inputc = cin.get();
			cin.ignore(1024, '\n');
			switch (inputc) {
			case '1': {
				BindUserOff();
				NewMail();
			}break;//д��
			case '2': appstate = MAIL_INBOX; break;//�ռ���
			case '3': CheckMails(2); break;//������
			case '4': appstate = USER_MAIN; break;
			default: {
				cout << endl << "You can only input number from 1 to 4!" << endl;
				continue;//FLAG1
			}
			}
			user_off = users.end();
			Save();//����
		}

		else if (appstate == MAIL_INBOX) {
		CheckMails(1);
		char inputc;
		Window(57);
		inputc = cin.get();
		cin.ignore(1024, '\n');
		switch (inputc) {
		case '1': {
			BindMail();
			MailManag(1);
		}break;//�Ѷ�ѡ���ʼ�
		case '2': MailManag(0); break;//�Ѷ�����
		case '3': appstate = MAIL; break;//����
		default: {
			cout << endl << "You can only input number from 1 to 3!" << endl;
			continue;//FLAG1
		}
		}
		mail_on = mails.end();
		Save();//����
		}

	}
}


void Application::Login(int option) {
	if (option == 0) {
		vector<User>::iterator iton;//ָ���Ե�¼�Ķ���
		char name[101] = "\0";
		char password[101] = "\0";
		while (true) {
			Window(1);
			cin.getline(name, 101);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(name) > USER_NAME_LEN) {
				Window(7);
				continue;
			}
			for (iton = users.begin(); iton < users.end(); iton++) {
				if (strcmp(iton->name, name) == 0) {
					break;
				}
			}
			if (iton == users.end()) {
				Window(9);
				continue;
			}
			break;
		}//��¼ʱ�����˺ţ������г��ȼ����Լ�nameƥ��

		while (true) {
			Window(2);
			cin.getline(password, 101);
			//cin.ignore(1024, '\n');
			if (strlen(password) > USER_PASS_LEN) {
				Window(7);
				continue;
			}
			if (strcmp(iton->password, password) != 0) {
				Window(3);
			}//��½ʧ��
			else {
				Window(4);
				user_on = iton;
				Identity ident = user_on->identity;
				if (ident == NORMAL)
					appstate = USER_MAIN;
				else if (ident == ADMINIS)
					appstate = ADMINIS_MAIN;
				else if (ident == FROZEN) {
					appstate = USER_FROZEN;
				}
				else {
					cout << "ERROR in PLACE5" << endl;//PLACE5
				}
			}
			break;
		}//��¼ʱ�����˺����룬�����г��ȼ���
	}

	else if (option == 1) {
		vector<User>::iterator iton;//ָ���Ե�¼�Ķ���
		char name[101] = "\0";
		while (true) {
			Window(1);
			cin.getline(name, 101);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(name) > USER_NAME_LEN) {
				Window(7);
				continue;
			}
			for (iton = users.begin(); iton < users.end(); iton++) {
				if (strcmp(iton->name, name) == 0) {
					break;
				}
			}
			if (iton == users.end()) {
				Window(9);
				continue;
			}
			break;
		}//��¼ʱ�����˺ţ������г��ȼ����Լ�nameƥ��

		char contact[101];
		while (true) {
			Window(25);
			cin.getline(contact, 101);
			//cin.ignore(1024, '\n');
			if (strlen(contact) > USER_CONTACT) {
				Window(7);
				continue;
			}
			if (strcmp(iton->contact, "null") == 0) {
				Window(52);
			}
			else if (strcmp(iton->contact, contact) != 0) {
				Window(53);
			}//��½ʧ��
			else {
				cout << endl << "Your password is " << iton->password << ", don't forget it again." << endl;
				Window(4);
				user_on = iton;
				Identity ident = user_on->identity;
				if (ident == NORMAL)
					appstate = USER_MAIN;
				else if (ident == ADMINIS)
					appstate = ADMINIS_MAIN;
				else if (ident == FROZEN) {
					appstate = USER_FROZEN;
				}
				else {
					cout << "ERROR in PLACE5" << endl;//PLACE5
				}
			}
			break;
		}//��¼ʱ�����˺����룬�����г��ȼ���
	}
	
}


void Application::SignUp() {
	char name[101];
	char password[101];
	char passConfir[101];
	while (true) {
		Window(1);
		cin.getline(name, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(name) > USER_NAME_LEN) {
			Window(7);
			continue;
		}
		bool sameName = false;
		for (vector<User>::iterator it = users.begin(); it < users.end(); it++) {
			if (strcmp(it->name, name) == 0) {
				Window(5);
				sameName = true;
				break;
			}
		}
		if (sameName) {
			continue;
		}
		break;
	}
	while (true) {
		Window(2);
		cin.getline(password, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(password) > USER_PASS_LEN) {
			Window(7);
			continue;
		}
		if (CheckPass(password) == 0) {
			Window(60);
			continue;
		}
		break;
	}//ע��ʱ�����˺�����
	while (true) {
		Window(45);
		cin.getline(passConfir, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strcmp(passConfir, password)!=0) {
			Window(46);
			continue;
		}
		break;
	}//ע��ʱ����ȷ������

	int safety = CheckPass(password);
	switch (safety) {
	case 1:cout << endl << "Your password is too easy, the account may in risk." << endl; break;
	case 2:cout << endl << "Your password is not very safe, you'd better change it." << endl; break;
	case 3:cout << endl << "Your password is safe." << endl; break;
	case 4:cout << endl << "Your password is very safe, enjoy our service!" << endl; break;
	case 5:cout << endl << "Your password is very safe, enjoy our service!" << endl; break;
	default:cout << "This is an egg." << endl;
	}


	int id = Random(10001, 99999);
	while (true) {
		vector<User> ::iterator it;
		for (it = users.begin(); it < users.end(); it++) {
			if (id == it->id) {
				id = Random(10001, 99999);
				break;
			}
		}
		if (it == users.end())
			break;
	}//Ϊid����һ�������������
	User user1(id, name, password, "null", "null", 0, 0, NORMAL);
	users.push_back(user1);

	Window(44);
}


void Application::Buy() {
	char confir;
	Window(48);
	confir = cin.get();
	cin.ignore(1024, '\n');
	if (confir != 'y') return;

	if (goods_on->goodsstate != AVAILABLE) {
		Window(30);
		return;
	}//��ͼ�����¼ܻ��۳���Ʒ

	if (user_on->money < goods_on->price) {
		Window(28);
		return;//Ǯ����
	}

	vector<User>::iterator seller;
	for (seller = users.begin(); seller < users.end(); seller++) {
		if (seller->id == goods_on->seller_id) {
			if (seller->id == user_on->id) {
				Window(29);
				return;
			}//��ֹ�Լ����Լ�����
			seller->money += goods_on->price;
			break;
		}//��Ǯ�������,��������
	}
	user_on->money -= goods_on->price;//������˻��ۿ�

	char inputc;
	int credit_add = 0;
	Window(63);
	inputc = cin.get();
	cin.ignore(1024, '\n');
	switch (inputc) {
	case '1':credit_add = 5; break;
	case '2':credit_add = 3; break;
	case '3':credit_add = 1; break;
	case '4':credit_add = -3; break;
	default: cout << "This is an egg." << endl;
	}
	seller->credit += credit_add;
	user_on->credit += 2;

	int id = Random(10001, 99999);
	while (true) {
		vector<Order> ::iterator it;
		for (it = orders.begin(); it < orders.end(); it++) {
			if (id == it->id) {
				id = Random(10001, 99999);
				break;
			}
		}
		if (it == orders.end())
			break;
	}//Ϊ����id����һ�������������
	char dealtime[DEAL_TIME_LEN + 1];
	GetTime(dealtime, DEAL_TIME_LEN + 1);
	Order order0(id, goods_on->id, seller->id, user_on->id, goods_on->price, dealtime);
	orders.push_back(order0);//���ɶ���

	goods_on->goodsstate = SOLDOUT;//������Ʒ״̬

	Notify(0, seller->id);
	Notify(1, user_on->id);

	Window(31);
}


void Application::Release() {
	char name[101];
	while (true) {
		Window(13);
		cin.getline(name, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(name) > GOODS_NAME_LEN) {
			Window(7);//FLAG2
			continue;
		}
		break;
	}//������Ʒ��

	double price;
	Window(14);
	cin >> price;
	while (true) {
		double temp = price * 10;
		if (price < 0) {
			Window(15);
			cin >> price;
		}
		else if (temp - (int)temp != 0) {
			Window(35);
			cin >> price;
		}
		else break;
	}//������Ʒ�۸�,�ж��Ƿ�Ϊ��������λ����С��
	cin.ignore(1024, '\n');//��ջ�����

	char descrip[201];
	while (true) {
		Window(16);
		cin.getline(descrip, 201);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(name) > GOODS_DESCRIP_LEN) {
			Window(7);
			continue;
		}//FLAG3
		break;
	}//������Ʒ����

	int id = Random(10001, 99999);
	while (true) {
		vector<Goods> ::iterator it;
		for (it = goodss.begin(); it < goodss.end(); it++) {
			if (id == it->id) {
				id = Random(10001, 99999);
				break;
			}
		}
		if (it == goodss.end())
			break;
	}//Ϊid����һ�������������

	char arrivetime[ARRIVE_TIME_LEN + 1];
	GetTime(arrivetime, ARRIVE_TIME_LEN + 1);//��ȡʱ��

	char confir;
	Window(48);
	confir = cin.get();
	cin.ignore(1024, '\n');
	if (confir != 'y') return;//����ȷ��

	Goods goods0(id, name, price, user_on->id, user_on->credit, arrivetime, descrip, AVAILABLE);
	goodss.push_back(goods0);//������Ʒ��������vector

	Window(32);
}


void Application::CheckUsers(int option) {
	Window(20);
	Window(-1);

	if (option == 0) {
		cout << left << setw(8) << "ID"
			<< left << setw(USER_NAME_LEN+1) << "Name"
			<< left << setw(16) << "Password"
			<< left << setw(USER_CONTACT+3) << "Contact Information"
			<< left << setw(13) << "Balance"
			<< left << setw(8) << "Credit"
			<< left << setw(USER_ADD_LEN) << "Address" 
			<< left << setw(20) << "State" << endl;
		vector<User>::iterator it;
		for (it = users.begin(); it < users.end(); it++) {
			cout << 'U' << left << setw(7) << it->id
				<< left << setw(USER_NAME_LEN + 1) << it->name
				<< left << setw(16) << it->password
				<< left << setw(USER_CONTACT+3) << it->contact
				<< left << setw(13) << fixed << setprecision(1) << it->money
				<< left << setw(8) << it->credit
				<< left << setw(USER_ADD_LEN) << it->address;
			if (it->identity == NORMAL) cout << left << setw(20) << "Normal" << endl;
			else if (it->identity == FROZEN) cout << left << setw(20) << "Suspended" << endl;
			else if (it->identity == ADMINIS) cout << left << setw(20) << "Administrator" << endl;
			else cout << "ERROR in PLACE11" << endl;//PLACE11
		}
	}//�鿴�����û���Ϣ

	else if (option == 1) {
		cout << left << setw(8) << "ID"
			<< left << setw(USER_NAME_LEN + 1) << "Name"
			<< left << setw(16) << "Password"
			<< left << setw(USER_CONTACT+3) << "Contact Information"
			<< left << setw(13) << "Balance"
			<< left << setw(8) << "Credit"
			<< left << setw(USER_ADD_LEN) << "Address" << endl;
		cout << 'U' << left << setw(7) << user_on->id
			<< left << setw(USER_NAME_LEN + 1) << user_on->name
			<< left << setw(16) << "******"
			<< left << setw(USER_CONTACT+3) << user_on->contact
			<< left << setw(13) << fixed << setprecision(1) << user_on->money
			<< left << setw(8) << user_on->credit
			<< left << setw(USER_ADD_LEN) << user_on->address << endl;
	}//�鿴��ǰ�û���Ϣ

	Window(-1);
}


void Application::UserManag(int option){
	if (option == 0) {
		char name[101] = "\0";
		while (true) {
			Window(1);
			cin.getline(name, 101);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(name) > USER_NAME_LEN) {
				Window(7);//FLAG2
				continue;
			}
			break;
		}//�����û���

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		strcpy(user_on->name, name);
		Window(21);
	}

	else if (option == 1) {
		char password[101] = "\0";
		while (true) {
			Window(2);
			cin.getline(password, 101);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(password) > USER_PASS_LEN) {
				Window(7);//FLAG2
				continue;
			}
			break;
		}//�����û���

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		strcpy(user_on->password, password);
		Window(21);
	}

	else if (option == 2) {
		char contact[101] = "\0";
		while (true) {
			Window(25);
			cin.getline(contact, 101);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(contact) > USER_CONTACT) {
				Window(7);//FLAG2
				continue;
			}
			break;
		}//�����û���

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		strcpy(user_on->contact, contact);
		Window(21);
	}

	else if (option == 3) {
		char address[101] = "\0";
		while (true) {
			Window(26);
			cin.getline(address, 101);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(address) > USER_ADD_LEN) {
				Window(7);//FLAG2
				continue;
			}
			break;
		}

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		strcpy(user_on->address, address);
		Window(21);
	}

	else if (option == 4) {
		if (user_off->id == user_on->id) {
			Window(51);
			return;
		}//����Ա��ͼ�����Լ�

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��

		if (user_off->identity == NORMAL) {
			user_off->identity = FROZEN;
			Window(49);
		}
		else if (user_off->identity == FROZEN) {
			user_off->identity = NORMAL;
			Window(50);
		}
		else cout << "ERROR in PLACE10" << endl;//PLACE10
	}
}


void Application::CheckGoodss(int option) {
	Window(8);
	Window(-1);
	if (option == 0) {
		cout << left << setw(8) << "ID"
			<< left << setw(GOODS_NAME_LEN + 1) << "Name"
			<< left << setw(8) << "Price"
			<< left << setw(15) << "Seller's ID"
			<< left << setw(17) << "Seller's Credit"
			<< left << setw(ARRIVE_TIME_LEN + 4) << "Arrive Time"
			<< "State" << endl << endl;
		vector<Goods> ::iterator it;
		for (it = goodss.begin(); it < goodss.end(); it++) {
			cout << 'M' << left << setw(7) << it->id
				<< left << setw(GOODS_NAME_LEN + 1) << it->name
				<< left << setw(8) << fixed << setprecision(1) << it->price
				<< 'U' << left << setw(14) << it->seller_id
				<< left << setw(17) << it->seller_credit
				<< left << setw(ARRIVE_TIME_LEN + 4) << it->arrivetime;
				
			if (it->goodsstate == SOLDOUT) cout << left << setw(15) << "Sold out." << endl;
			else if (it->goodsstate == AVAILABLE) cout << left << setw(15) << "Available" << endl;
			else if (it->goodsstate == WITHDRAWN) cout << left << setw(15) << "Withdrawn" << endl;
			else cout << "ERROR IN PLACE9" << endl;//PLACE9
			cout << "Description: " << it->descrip << endl<< endl;
		}
	}//�鿴������Ʒ

	else if (option == 1) {
		cout << left << setw(8) << "ID"
			<< left << setw(GOODS_NAME_LEN + 1) << "Name"
			<< left << setw(8) << "Price"
			<< left << setw(ARRIVE_TIME_LEN + 4) << "Arrive Time"
			<< "State" << endl;
		vector<Goods> ::iterator it;
		for (it = goodss.begin(); it < goodss.end(); it++) {
			if (it->seller_id == user_on->id) {
				cout << 'M' << left << setw(7) << it->id
					<< left << setw(GOODS_NAME_LEN + 1) << it->name
					<< left << setw(8) << fixed << setprecision(1) << it->price
					<< left << setw(ARRIVE_TIME_LEN + 4) << it->arrivetime;

				if (it->goodsstate == SOLDOUT) cout << left << setw(15) << "Sold out." << endl;
				else if (it->goodsstate == AVAILABLE) cout << left << setw(15) << "Available" << endl;
				else if (it->goodsstate == WITHDRAWN) cout << left << setw(15) << "Withdrawn" << endl;
				else cout << "ERROR IN PLACE9" << endl;//PLACE9
				cout << "Description: " << it->descrip << endl;
			}
		}
	}//�鿴����Լ�����Ʒ

	else if (option == 2) {
		cout << left << setw(8) << "ID"
			<< left << setw(GOODS_NAME_LEN + 1) << "Name"
			<< left << setw(8) << "Price"
			<< left << setw(17) << "Seller's Credit"
			<< left << setw(ARRIVE_TIME_LEN + 4) << "Arrive Time"<< endl;
		vector<Goods> ::iterator it;
		for (it = goodss.begin(); it < goodss.end(); it++) {
			if (it->goodsstate == AVAILABLE) {
				cout << 'M' << left << setw(7) << it->id
					<< left << setw(GOODS_NAME_LEN + 1) << it->name
					<< left << setw(8) << fixed << setprecision(1) << it->price
					<< left << setw(17) << it->seller_credit
					<< left << setw(ARRIVE_TIME_LEN + 4) << it->arrivetime << endl;
				cout << "Description: " << it->descrip << endl;
			}
		}
	}//�鿴�ϼܵĵ���Ʒ

	Window(-1);
}//�鿴��Ʒ


void Application::GoodsManag(int option) {
	if (option == 0) {
		if (goods_on->goodsstate == SOLDOUT) {
			Window(33);
			return;
		}//��ֹ�޸��ѳ�����Ʒ����Ϣ
		char name[101] = "\0";
		while (true) {
			Window(13);
			cin.getline(name, 101);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(name) > GOODS_NAME_LEN) {
				Window(7);//FLAG2
				continue;
			}
			break;
		}//������Ʒ��

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		strcpy(goods_on->name, name);
		Window(21);
	}

	else if (option == 1) {
		if (goods_on->goodsstate == SOLDOUT) {
			Window(33);
			return;
		}//��ֹ�޸��ѳ�����Ʒ����Ϣ
		double price = goods_on->price;
		Window(14);
		cin >> price;
		cin.ignore(1024, '\n');//������Ʒ�۸�

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		goods_on->price = price;
		Window(21);
	}

	else if (option == 2) {
		if (goods_on->goodsstate == SOLDOUT) {
			Window(33);
			return;
		}//��ֹ�޸��ѳ�����Ʒ����Ϣ
		char descrip[201] = "\0";
		while (true) {
			Window(16);
			cin.getline(descrip, 201);
			//cin.ignore(1024, '\n');//��ջ�����
			if (strlen(descrip) > GOODS_DESCRIP_LEN) {
				Window(7);
				continue;
			}//FLAG3
			break;
		}//������Ʒ����

		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		strcpy(goods_on->descrip, descrip);
		Window(21);
	}

	else if (option == 3) {
		if (goods_on->goodsstate == SOLDOUT) {
			Window(33);
			return;
		}//��ֹ�޸��ѳ�����Ʒ����Ϣ
		char confir;
		Window(48);
		confir = cin.get();
		cin.ignore(1024, '\n');
		if (confir != 'y') return;//����ȷ��
		goods_on->goodsstate = WITHDRAWN;//�¼���Ʒ
		Window(22);
	}

}


void Application::BindGoods() {
	vector<Goods>::iterator itgd;//ָ���Բ�������Ʒ����
	Window(17);
	char idstr[101] = "\0";
	while (true) {
		cin.getline(idstr, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(idstr) != 6 || idstr[0] != 'M') {
			Window(18);
			continue;
		}//�����Ƿ�'M'��ͷ
		for (int i = 1; i < (int)strlen(idstr); i++) {
			if (idstr[i] < '0' || idstr[i]>'9') {
				Window(18);
				continue;
			}
		}//�����5λ�Ƿ�����

		int id = IdToInt(idstr, 5);
		for (itgd = goodss.begin(); itgd < goodss.end(); itgd++) {
			if (id == itgd->id) {
				break;
			}
		}
		if (itgd == goodss.end()) {
			Window(19);
			continue;
		}
		break;
	}

	goods_on = itgd;

}


void Application::BindUserOff() {
	vector<User>::iterator itus;//ָ���Բ�������Ʒ����
	Window(41);
	char idstr[101] = "\0";
	while (true) {
		cin.getline(idstr, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(idstr) != 6 || idstr[0] != 'U') {
			Window(18);
			continue;
		}//�����Ƿ�'U'��ͷ
		for (int i = 1; i < (int)strlen(idstr); i++) {
			if (idstr[i] < '0' || idstr[i]>'9') {
				Window(18);
				continue;
			}
		}//�����5λ�Ƿ�����

		int id = IdToInt(idstr, 5);
		for (itus = users.begin(); itus < users.end(); itus++) {
			if (id == itus->id) {
				break;
			}
		}
		if (itus == users.end()) {
			Window(19);
			continue;
		}
		break;
	}

	user_off = itus;
}


void Application::TopUp() {
	Window(34);
	double amount;
	cin >> amount;
	while (true) {
		double temp = amount*10;
		if (amount < 0) {
			Window(36);
			cin >> amount;
		}
		else if (temp - (int)temp != 0) {
			Window(35);
			cin >> amount;
		}
		else break;
	}//�ж��Ƿ�Ϊ��������λ����С��
	cin.ignore(1024, '\n');//��ջ������Ǹ���ϰ��

	char confir;
	Window(48);
	confir = cin.get();
	cin.ignore(1024, '\n');
	if (confir != 'y') return;//����ȷ��

	system("Data\\TopUp.jpg");

	user_on->money += amount;
	cout << endl << "Top up successfully! Now the balance is " << user_on->money <<'.'<< endl;
}


void Application::SearchGoods() {
	bool hasTarg = false;//�Ƿ���Ŀ����Ʒ
	char keywords[101]="\0";
	Window(37);

	while (true) {
		cin.getline(keywords, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(keywords) > GOODS_NAME_LEN) {
			Window(7);//FLAG2
			continue;
		}
		break;
	}//������Ʒ��

	vector<Goods>::iterator targGoods = goodss.begin();
	for (targGoods = goodss.begin(); targGoods < goodss.end(); targGoods++) {
		string targstr = targGoods->name, keystr = keywords;
		if (targstr.find(keystr) != string::npos) {
			cout << endl
				<< "ID: M" << targGoods->id << endl
				<< "Name: " << targGoods->name << endl
				<< "Price: " << targGoods->price << endl
				<< "Arrive Time: " << targGoods->arrivetime << endl 
				<< "Description: " << targGoods->descrip << endl;
			hasTarg = true;
		}
	}//����Ʒ��Ϊ�ؼ�������

	if (strlen(keywords) == 6 && keywords[0] == 'M' && keywords[5] <= '9' && keywords[5] >= '0') {
		int keyId = IdToInt(keywords, 5);
		for (targGoods = goodss.begin(); targGoods < goodss.end(); targGoods++) {
			if (keyId == targGoods->id) {
				cout << endl
					<< "ID: M" << targGoods->id << endl
					<< "Name: " << targGoods->name << endl
					<< "Price: " << targGoods->price << endl
					<< "Arrive Time: " << targGoods->arrivetime << endl
					<< "Description: " << targGoods->descrip << endl;
				hasTarg = true;
			}
		}//��IDΪ�ؼ�������
	}

	if (!hasTarg)
		Window(38);
}


void Application::CheckOrders(int option) {
	Window(39);
	Window(-1);
	if (option == 0) {
		cout << left << setw(8) << "ID"
			<< left << setw(15) << "ID of Goods"
			<< left << setw(15) << "ID of Seller"
			<< left << setw(15) << "ID of Buyer"
			<< left << setw(8) << "Amount"
			<< left << setw(DEAL_TIME_LEN+4) << "Deal Time" << endl;
		vector<Order> ::iterator it;
		for (it = orders.begin(); it < orders.end(); it++) {
			cout << 'T' << left << setw(7) << it->id
				<< 'M' << left << setw(14) << it->goods_id
				<< 'U' << left << setw(14) << it->seller_id
				<< 'U' << left << setw(14) << it->buyer_id
				<< left << setw(8) << fixed << setprecision(1) << it->amount
				<< left << setw(DEAL_TIME_LEN + 4) << it->dealtime << endl;
		}
	}//�鿴���ж���

	else if (option == 1) {
		cout << left << setw(8) << "ID"
			<< left << setw(15) << "ID of Goods"
			<< left << setw(15) << "ID of Seller"
			//<< left << setw(15) << "ID of Buyer"
			<< left << setw(8) << "Amount"
			<< left << setw(DEAL_TIME_LEN + 4) << "Deal Time" << endl;
		vector<Order> ::iterator it;
		for (it = orders.begin(); it < orders.end(); it++) {
			if (it->buyer_id == user_on->id)
				cout << 'T' << left << setw(7) << it->id
				<< 'M' << left << setw(14) << it->goods_id
				<< 'U' << left << setw(14) << it->seller_id
				//<< 'U' << left << setw(14) << it->buyer_id
				<< left << setw(8) << fixed << setprecision(1) << it->amount
				<< left << setw(DEAL_TIME_LEN + 4) << it->dealtime << endl;
		}
	}//�鿴��Ҷ���

	else if (option == 2) {
		cout << left << setw(8) << "ID"
			<< left << setw(15) << "ID of Goods"
			//<< left << setw(15) << "ID of Seller"
			<< left << setw(15) << "ID of Buyer"
			<< left << setw(8) << "Amount"
			<< left << setw(DEAL_TIME_LEN + 4) << "Deal Time" << endl;
		vector<Order> ::iterator it;
		for (it = orders.begin(); it < orders.end(); it++) {
			if (it->seller_id == user_on->id)
				cout << 'T' << left << setw(7) << it->id
				<< 'M' << left << setw(14) << it->goods_id
				//<< 'U' << left << setw(14) << it->seller_id
				<< 'U' << left << setw(14) << it->buyer_id
				<< left << setw(8) << fixed << setprecision(1) << it->amount
				<< left << setw(DEAL_TIME_LEN + 4) << it->dealtime << endl;
		}
	}//�鿴��Ҷ���

	Window(-1);
}


void Application::NewMail() {
	char content[301];
	while (true) {
		Window(55);
		cin.getline(content, 301);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(content) > CONTENT_LEN) {
			Window(7);
			continue;
		}//FLAG3
		break;
	}//�����ż�����

	char mailtime[MAIL_TIME_LEN + 1];
	GetTime(mailtime, MAIL_TIME_LEN + 1);//��ȡʱ��

	int id = Random(10001, 99999);
	while (true) {
		vector<Mail> ::iterator it;
		for (it = mails.begin(); it < mails.end(); it++) {
			if (id == it->id) {
				id = Random(10001, 99999);
				break;
			}
		}
		if (it == mails.end())
			break;
	}//Ϊid����һ�������������

	cout << endl << "You are going to send the mail to " << user_off->name << endl;
	char confir;
	Window(48);
	confir = cin.get();
	cin.ignore(1024, '\n');
	if (confir != 'y') return;//����ȷ��

	Mail mail0(id, user_on->id, user_off->id, user_on->name, user_off->name, mailtime, content);
	mails.push_back(mail0);//�����ʼ���������vector

	Window(56);
}


void Application::CheckMails(int option) {
	Window(-1);

	if (option == 0) {
		vector<Mail>::iterator it;
		for (it = mails.begin(); it < mails.end(); it++) {
			cout << endl
				<< "ID: S" << it->id << endl
				<< "From: " << it->sender_name << " (ID: U" << it->sender_id << ")\n"
				<< "To: " << it->reci_name << " (ID: U" << it->reci_id << ")\n"
				<< "Time: " << it->mail_time << endl
				<< "    " << it->content;
			if (it->isread) cout << "State: read\n\n";
			else cout << "State: unread\n\n";
		}
	}

	else if (option == 1) {
		vector<Mail>::iterator it;
		for (it = mails.begin(); it < mails.end(); it++) {
			if (user_on->id == it->reci_id && !it->isread)
				cout << endl
				<< "ID: S" << it->id << endl
				<< "From: " << it->sender_name << " (ID: U" << it->sender_id << ")\n"
				//<< "To: " << it->reci_name << " (ID: U" << it->reci_id << ")\n"
				<< "Time: " << it->mail_time << endl
				<< "    " << it->content
				<< endl << endl;
		}
	}

	else if (option == 2) {
		vector<Mail>::iterator it;
		for (it = mails.begin(); it < mails.end(); it++) {
			if (user_on->id == it->sender_id)
				cout << endl
				<< "ID: S" << it->id << endl
				//<< "From: " << it->sender_name << " (ID: U" << it->sender_id << ")\n"
				<< "To: " << it->reci_name << " (ID: U" << it->reci_id << ")\n"
				<< "Time: " << it->mail_time << endl
				<< "    " << it->content
				<< endl << endl;
		}
	}

	else
		cout << "This is an egg." << endl;

	Window(-1);
}


void Application::BindMail() {
	vector<Mail>::iterator itml;//ָ���Բ������ʼ�����
	Window(58);
	char idstr[101] = "\0";
	while (true) {
		cin.getline(idstr, 101);
		//cin.ignore(1024, '\n');//��ջ�����
		if (strlen(idstr) != 6 || idstr[0] != 'S') {
			Window(18);
			continue;
		}//�����Ƿ�'S'��ͷ�Լ�ƥ�䳤��
		for (int i = 1; i < (int)strlen(idstr); i++) {
			if (idstr[i] < '0' || idstr[i]>'9') {
				Window(18);
				continue;
			}
		}//�����5λ�Ƿ�����

		int id = IdToInt(idstr, 5);
		for (itml = mails.begin(); itml < mails.end(); itml++) {
			if (id == itml->id && !itml->isread) {
				break;
			}
		}
		if (itml == mails.end()) {
			Window(19);
			continue;
		}
		break;
	}

	mail_on = itml;

}


void Application::MailManag(int option) {
	char confir;
	Window(48);
	confir = cin.get();
	cin.ignore(1024, '\n');
	if (confir != 'y') return;//����ȷ��

	if (option == 0) {
		vector<Mail>::iterator iter;
		for (iter = mails.begin(); iter < mails.end(); iter++) {
			if (iter->reci_id == user_on->id && !iter->isread)
				iter->isread = true;
		}
	}

	else if (option == 1) {
		vector<Mail>::iterator iter;
		for (iter = mails.begin(); iter < mails.end(); iter++) {
			if (iter->id == mail_on->id)
				iter->isread = true;
		}
	}

	Window(59);
}


int Application::CheckPass(const char* cstr) {
	int len = strlen(cstr);
	if (len == 0)
		return 0;//���볤��Ϊ0��������
	for(int i=0;i<len;i++)
		if (cstr[i] == ' ')
			return 0;//���뺬�ո񣬲�����

	bool hasNum = false, hasLet = false, hasSym = false;
	for (int i = 0; i < len; i++) {
		if (cstr[i] <= '9' && cstr[i] >= '0')
			hasNum = true;
		else if ((cstr[i] <= 'z' && cstr[i] >= 'a') || (cstr[i] <= 'Z' && cstr[i] >= 'A'))
			hasLet = true;
		else hasSym = true;
	}

	int res = 1;//��ȫ�ȼ���ͼ�
	if (len >= 6) res++;
	res += (hasNum + hasLet + hasSym);
	return res;
}


void Application::CloseAcc() {
	Window(61);
	char confir;
	Window(48);
	confir = cin.get();
	cin.ignore(1024, '\n');
	if (confir != 'y') return;//����ȷ��

	users.erase(user_on);
	user_on = users.end();

	Window(62);
}


void Application::Notify(int option, int id) {
	char content[100];
	if (option == 0)
		strcpy(content, "Your goods is sold, please check your balance and credit.");
	else if(option==1)
		strcpy(content, "You have made a deal, please check your balance and credit.");

	char mailtime[MAIL_TIME_LEN + 1];
	GetTime(mailtime, MAIL_TIME_LEN + 1);//��ȡʱ��


	int mid = Random(10001, 99999);
	while (true) {
		vector<Mail> ::iterator it;
		for (it = mails.begin(); it < mails.end(); it++) {
			if (mid == it->id) {
				mid = Random(10001, 99999);
				break;
			}
		}
		if (it == mails.end())
			break;
	}//Ϊid����һ�������������

	Mail mail0(mid, 0, id, "System", " ", mailtime, content);
	mails.push_back(mail0);//�����ʼ���������vector

}





















