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

void modeAdmin() {
	OnlineShoppingSystem();
}

extern map<string, pair<int, int> > Map_Stock;
void modeUser(string id) {
	int selectNum;
	InitDatas();
	constructDatas();

	while (true) {
		cout << "\tUser : " << id << endl;
		cout << UserMainMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1:
			UserManage(id);
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
	}
}

#endif