#ifndef MODETEST_H_
#define MODETEST_H_

#include <vector>
#include "shoptest.h"
#include "../structure/member.h"
#include "../structure/purchase.h"
#include "../structure/stock.h"
#include "../utils/strings.h"
#include "../utils/rwdata.h"
#define ADMIN 1
#define USER 2

void modeAdmin() {
	vector<Member> listMember;
	vector<Stock> listStock;
	vector<Purchase> listPurchase;

	readTxt<Member>(txtFileMem, listMember);
	writeDat<Member>(datFileMem, listMember);
	readTxt<Stock>(txtFileStock, listStock);
	writeDat<Stock>(datFileStock, listStock);
	readTxt<Purchase>(txtFilePur, listPurchase);
	writeDat<Purchase>(datFilePur, listPurchase);

	OnlineShoppingSystem();
}

void modeUser(string id) {

}

#endif