#ifndef MODETEST_H_
#define MODETEST_H_

#include <vector>

#include "../structure/member.h"
#include "../structure/purchase.h"
#include "../structure/stock.h"
#include "../structure/dataset.h"
#include "../utils/strings.h"
#include "../utils/rwdata.h"
#include "../testutils/strings.h"
#include "shoptest.h"
#include "../shoppingutils/search.h"
#include "../shoppingutils/user.h"


#define ADMIN 1
#define USER 2

void login() {
	int modeflag = 0;
	string id;
	while (true) {
		modeflag = 0;
		string pw;
		cout << "================================================" << endl;
		cout << "        Purchase System" << endl;
		cout << "ID : ";
		cin >> id;
		cin.get();
		cout << "PW : ";
		cin >> pw;
		cin.get();
		if (id == "admin") {
			if (pw == "adminpass") {
				modeflag = ADMIN;
				cout << "Logged in successfully! Press Enter.";
				cin.get();
				system("cls");
			}
			else {
				cout << "Invalid User info. Press Enter.";
				cin.get();
				system("cls");
			}
		}
		else if (id == "TestUser") {
			if (pw == "T1234") {
				modeflag = USER;
				cout << "Logged in successfully! Press Enter.";
				cin.get();
				system("cls");
			}
			else {
				cout << "Invalid User info. Press Enter.";
				cin.get();
				system("cls");
			}
		}
		else {
			cout << "Invalid User info. Press Enter.";
			cin.get();
			system("cls");
		}

		switch (modeflag) {
		case ADMIN:
			modeAdmin();
			break;
		case USER:
			modeUser(id);
			break;
		default:
			break;
		}
	}
}

void modeAdmin() {
	OnlineShoppingSystem();
}

extern map<string, pair<int, int> > Map_Stock;
void modeUser(string id) {
	int selectNum;
	bool deleted;
	InitDatas();
	constructDatas();

	while (true) {
		cout << "\tUser : " << id << endl;
		cout << UserMainMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1:
			deleted = UserManage(id);
			break;
		case 2:
			SearchData<Stock>(Map_Stock, datFileStock);
			break;
		case 3:
			UserPurchaseManage(id);
			break;
		case 4:
			return;
		}
		if (deleted)
			return;
	}
}

#endif