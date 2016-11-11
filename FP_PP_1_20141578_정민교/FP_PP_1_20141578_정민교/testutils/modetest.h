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
#include "../shoppingutils/insert.h"
#include "../shoppingutils/user.h"

#define ERROR -1
#define ADMIN 1
#define USER 2

extern map<string, pair<int, int> > Map_Member;

void login() {
	int modeflag = 0;
	string id;
	string pw;
	
	cout << "================================================" << endl;
	cout << "        Purchase System" << endl;
	cout << "ID : ";
	cin >> id;
	cin.get();
	cout << "PW : ";
	cin >> pw;
	cin.get();
	if (SearchFromMap<Member>(Map_Member, id).first == -1)
		modeflag = ERROR;
	else {
		if (id == "admin") {
			if (pw == "adminpass")
				modeflag = ADMIN;
			else
				modeflag = ERROR;

		}
		else if (id == "TestUser") {
			if (pw == "T1234")
				modeflag = USER;
			else
				modeflag = ERROR;
		}
		else {
			if (pw == "1111")
				modeflag = USER;
			else
				modeflag = ERROR;
		}
	}

	if (modeflag != ERROR) {
		cout << "Logged in successfully! Press Enter.";
		cin.get();
		system("cls");
	}
	switch (modeflag) {
	case ERROR:
		cout << "Invalid User info. Press Enter.";
		cin.get();
		system("cls");
		break;
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

void modeAdmin() {
	OnlineShoppingSystem();
}

extern map<string, pair<int, int> > Map_Stock;
void modeUser(string id) {
	int selectNum;
	bool deleted;

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

void constructAdmins() {
	if (SearchFromMap<Member>(Map_Member, "admin").first == -1) {
		Member m(
			"admin", 
			"admin", 
			"010-0000-0000", 
			"Seoul", 
			19000000, 
			"admin@sogang.ac.kr",
			1
		);
		AddMemberAsRecord(m);
	}
	if (SearchFromMap<Member>(Map_Member, "TestUser").first == -1) {
		Member m(
			"TestUser",
			"TestUser",
			"010-0000-0000",
			"Seoul",
			19000000,
			"TestUser@sogang.ac.kr",
			1
		);
		AddMemberAsRecord(m);
	}
}
#endif