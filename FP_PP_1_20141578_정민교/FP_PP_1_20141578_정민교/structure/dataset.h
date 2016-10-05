#ifndef DATASET_H_
#define DATASET_H_

#include <vector>
#include <map>
#include "member.h"
#include "purchase.h"
#include "stock.h"

/*
	First structure : Save recaddr, length (skip length not needed)
	Second structure : For search. key - primary key, value - recaddr and length
*/

#ifndef DATA_MEMBER
#define DATA_MEMBER
static vector<pair<int, int> > Deleted_Member;
static map<string, pair<int, int> > Map_Member;
#endif

#ifndef DATA_STOCK
#define DATA_STOCK
static vector<pair<int, int> > Deleted_Stock;
static map<string, pair<int, int> > Map_Stock;
#endif

#ifndef DATA_PURCHASE
#define DATA_PURCHASE
static vector<pair<int, int> > Deleted_Purchase;
static map<string, pair<int, int> > Map_Purchase_PID;
static map<string, vector<pair<int, int> > > Map_Purchase_MID;
static map<string, vector<pair<int, int> > > Map_Purchase_SID;
#endif

static void InitDatas() {	
	Deleted_Member.clear();
	Deleted_Stock.clear();
	Deleted_Purchase.clear();

	Map_Member.clear();
	Map_Stock.clear();
	Map_Purchase_PID.clear();
	Map_Purchase_MID.clear();
	Map_Purchase_SID.clear();
}

#endif