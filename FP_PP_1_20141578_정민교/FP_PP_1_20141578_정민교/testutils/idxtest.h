#pragma once
#ifndef IDXTEST_H_
#define IDXTEST_H_

#include <fstream>

#include "../utils/strings.h"
#include "../utils/indexutil.h"
#include "../structure/dataset.h"
#include "../structure/member.h"
#include "../structure/stock.h"

void checkidx();

extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Stock;

void checkidx() {
	fstream File;
	File.open(idxFileMem.c_str(), ios::in | ios::binary);
	if (!File.good()) {
		createIdxFile<Member>(idxFileMem, datFileMem, Map_Member.size(), LEN_MEMID);
	}
	
	File.clear();
	File.open(idxFileStock.c_str(), ios::in | ios::binary);
	if (!File.good()) {
		createIdxFile<Stock>(idxFileStock, datFileStock, Map_Stock.size(), LEN_STOCKID);
	}
}
#endif