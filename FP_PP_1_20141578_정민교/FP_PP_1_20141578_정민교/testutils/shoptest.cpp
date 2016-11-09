#include <stdlib.h>
#include "../structure/dataset.h"
#include "../utils/recfile.h"
#include "../utils/rwdata.h"
#include "../utils/strings.h"
#ifndef SEARCH_H_
#include "../shoppingutils/search.h"
#endif
#include "../shoppingutils/delete.h"
#include "../shoppingutils/insert.h"
#include "../shoppingutils/modify.h"
#include "strings.h"
#include "shoptest.h"

extern vector< pair<int, int> > Deleted_Member;
extern vector< pair<int, int> > Deleted_Stock;
extern vector< pair<int, int> > Deleted_Purchase;

extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Stock;
extern map<string, pair<int, int> > Map_Purchase_PID;
extern map<string, vector<pair<int, int> > > Map_Purchase_MID;
extern map<string, vector<pair<int, int> > > Map_Purchase_SID;
//First element : recaddr, Second element : space (Save when data deleted, deleted when data saved.)

void OnlineShoppingSystem(void) {
	int selectNum;
	InitDatas();
	constructDatas();
	/*readDat<Member>(
		datFileMem,
		Deleted_Member,
		Map_Member);
	readDat<Stock>(
		datFileStock,
		Deleted_Stock,
		Map_Stock);
	readDatPurchase(
		datFilePur,
		Deleted_Purchase);*/

	while (true) {
		cout << shoppingMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1:
			system("cls");
			Search();
			break;
		case 2:
			system("cls");
			Insert();
			break;
		case 3:
			system("cls");
			Delete();
			break;
		case 4:
			system("cls");
			Modify();
			break;
		case 5:
			return;
		}
		system("cls");
	}
}

void Search(void) {
	int selectNum;
	cout << SearchMenu << ">> ";
	cin >> selectNum;
	cin.get();
	switch (selectNum) {
	case 1:
		system("cls");
		SearchData<Member>(Map_Member, datFileMem);
		break;
	case 2:
		system("cls");
		SearchData<Stock>(Map_Stock, datFileStock);
		break;
	case 3:
		system("cls");
		SearchDataPurchase();
		break;
	case 4:
	default:
		break;
	}
}

void Insert(void) {
	int selectNum;
	cout << InsertMenu << ">> ";
	cin >> selectNum;
	cin.get();
	switch (selectNum) {
	case 1:
		system("cls");
		InsertMember();
		break;
	case 2:
		system("cls");
		InsertStock();
		break;
	case 3:
		system("cls");
		InsertPurchase();
		break;
	case 4:
	default:
		break;
	}
}

void Delete(void) {
	int selectNum;
	cout << DeleteMenu << ">> ";
	cin >> selectNum;
	cin.get();
	switch (selectNum) {
	case 1:
		system("cls");
		DeleteFromMem();
		break;
	case 2:
		system("cls");
		DeleteFromStock();
		break;
	case 3:
		system("cls");
		DeleteFromPurchase();
		break;
	case 4:
	default:
		break;
	}
}

void Modify(void) {
	int selectNum;
	cout << ModifyMenu << ">> ";
	cin >> selectNum;
	cin.get();
	switch (selectNum) {
	case 1:
		system("cls");
		ModifyMember();
		break;
	case 2:
		system("cls");
		ModifyStock();
		break;
	case 3:
		system("cls");
		ModifyPurchase();
		break;
	case 4:
	default:
		break;
	}
}