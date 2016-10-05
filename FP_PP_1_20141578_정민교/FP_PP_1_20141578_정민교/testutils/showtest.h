#ifndef PACKTEST_H_
#define PACKTEST_H_

#include <vector>

#include "../utils/rwdata.h"
#include "../utils/strings.h"

void showMember(void) {
	vector<Member> list_Member;
	InitDatas();
	readTxt<Member>(txtFileMem,list_Member);
	for (int i = 0; i < 10; i++) {
		cout << i+1 << ".\n" << list_Member[i] << endl;
	}
	cout << "Press any key to return menu.";
	cin.get();
}

void showStock(void) {
	vector<Stock> list_Stock;
	InitDatas();
	readTxt<Stock>(txtFileStock,list_Stock);
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ".\n" << list_Stock[i] << endl;
	}
	cout << "Press any key to return menu.";
	cin.get();
}

void showPurchase(void) {
	vector<Purchase> list_Purchase;
	InitDatas();
	readTxt<Purchase>(txtFilePur,list_Purchase);
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ".\n" << list_Purchase[i] << endl;
	}
	cout << "Press any key to return menu.";
	cin.get();
}

#endif