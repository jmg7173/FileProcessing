#pragma once
#ifndef IDXTEST_H_
#define IDXTEST_H_

#include <fstream>
#include "../structure/dataset.h"
#include "../utils/strings.h"
#include "../structure/member.h"
#include "../structure/stock.h"
template <class Type>
void makeIdxFile(const string idxfile, const string datfile, int size);
void checkidx();

extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Stock;

void checkidx() {
	fstream File;
	File.open(idxFileMem.c_str(), ios::in | ios::binary);
	if (!File.good()) {
		makeIdxFile<Member>(idxFileMem, datFileMem, Map_Member.size());
	}
	
	File.clear();
	File.open(idxFileStock.c_str(), ios::in | ios::binary);
	if (!File.good()) {
		makeIdxFile<Stock>(idxFileStock, datFileStock, Map_Stock.size());
	}
}

template <class Type>
void makeIdxFile(const string idxfile, const string datfile, int size) {

}
#endif