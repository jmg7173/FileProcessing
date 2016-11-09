#ifndef USER_H_
#define USER_H_

#include "../structure/dataset.h"
#include "../testutils/strings.h"
#include "../utils/strings.h"

#ifndef SEARCH_H_
#include "search.h"
#endif

extern map<string, pair<int, int> > Map_Member;

void UserManage(const string id);
void UserPurchaseManage(const string id);

void UserManage(const string id) {
	int selectNum;
	while (true) {
		cout << UserMemberMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1: {
			system("cls");
			int recaddr = SearchFromMap<Member>(Map_Member, id).first;
			Member m = readSpecificDat<Member>(datFileMem, recaddr);
			cout << m << endl;
			break;
			}
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}
}

void UserPurchaseManage(const string id) {

}
#endif