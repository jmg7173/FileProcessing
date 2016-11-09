#ifndef RWDATA_H_
#define RWDATA_H_

#include <fstream>
#include <string>

#include "recfile.h"
#include "../structure/dataset.h"

// Read from .txt Files
template <class Type>
void readTxt(const string filename, vector<Type> &list) {
	ifstream ifs(filename);
	if (ifs.fail())
	{
		cout << "File open error!" << endl;
		exit(1);
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Type p;
		ifs >> p;
		list.push_back(p);
	}
	ifs.close();
}

// Write to .dat Files
template <class Type>
bool writeDat(const string filename, const vector<Type> list) {
	DelimFieldBuffer buffer('|', MAXBUF);
	RecordFile <Type> TypeFile(buffer);

	TypeFile.Create(filename.c_str(), ios::out | ios::trunc);

	if (list.empty())
		return false;

	for (Type t : list) {
		int recaddr;
		if ((recaddr = TypeFile.Write(t)) == -1) {
			cout << "Write Error!" << endl;
			return false;
		}
	}
	TypeFile.Close();
	return true;
}

template <class Type>
bool writeSpecificDat(const string filename, Type t, int recaddr, unsigned char skipSize = 0) {
	DelimFieldBuffer buffer('|', MAXBUF);
	RecordFile <Type> TypeFile(buffer);

	if (!TypeFile.Open(filename.c_str(), ios::out))
		return false;

	int rectmp;
	if ((rectmp = TypeFile.Write(t,recaddr,skipSize)) == -1) {
		cout << "Write Error!" << endl;
		return false;
	}
	TypeFile.Close();
	return true;
}

template <class Type>
Type readSpecificDat(const string filename, int recaddr) {
	DelimFieldBuffer buffer('|', MAXBUF);
	RecordFile <Type> TypeFile(buffer);

	if (!TypeFile.Open(filename.c_str(), ios::in))
		return Type();

	int rectmp;
	Type t;
	unsigned char bufSize, skipSize;

	if ((rectmp = TypeFile.Read(t, bufSize, skipSize, recaddr)) == -1)
		return Type();
	
	if (!bufSize)
		return Type();
	
	TypeFile.Close();
	return t;
}

// Read from .dat Files (Member, Stock)
template <class Type>
bool readDat(
	const string filename,
	vector< pair<int ,int> >& deleted,
	map<string, pair<int, int> > &Map
) {
	DelimFieldBuffer buffer('|', MAXBUF);
	RecordFile <Type> TypeFile(buffer);
	int state = 0;
	if (!TypeFile.Open(filename.c_str(), ios::in))
		return false;
	while (true) {
		Type t;
		unsigned char bufSize = 0;
		unsigned char skipSize = 0;
		state = TypeFile.Read(t, bufSize, skipSize);

		if (state == -1)
			break;
		if (!bufSize) {
			deleted.push_back(make_pair(state, skipSize));
			continue;
		}
		Map[t.getID()] = make_pair(state, bufSize + skipSize);
	}
	TypeFile.Close();
	return true;
}

extern map<string, pair<int, int> > Map_Purchase_PID;
extern map<string, vector<pair<int, int> > > Map_Purchse_MID;
extern map<string, vector<pair<int, int> > > Map_Purchse_SID;

static bool readDatPurchase(
	const string filename,
	vector< pair<int, int> >& deleted
) {
	DelimFieldBuffer buffer('|', MAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	int state = 0;
	int idx = 0;
	if (!PurchaseFile.Open(filename.c_str(), ios::in))
		return false;
	while (true) {
		Purchase p;
		unsigned char bufSize = 0;
		unsigned char skipSize = 0;
		state = PurchaseFile.Read(p, bufSize, skipSize);

		if (state == -1)
			break;
		if (!bufSize) {
			deleted.push_back(make_pair(state, skipSize));
			continue;
		}
		
		Map_Purchase_PID[p.getPurchaseID()] = make_pair(state, bufSize+skipSize);
		Map_Purchase_MID[p.getMemberID()].push_back(make_pair(state, bufSize + skipSize));
		Map_Purchase_SID[p.getStockID()].push_back(make_pair(state, bufSize + skipSize));
	}
	PurchaseFile.Close();
	return true;
}

#include "strings.h"
extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Stock;
extern vector<pair<int, int> > Deleted_Purchase;
extern vector<pair<int, int> > Deleted_Stock;
extern vector<pair<int, int> > Deleted_Member;
static void constructDatas() {
	readDat<Member>(
		datFileMem,
		Deleted_Member,
		Map_Member);
	readDat<Stock>(
		datFileStock,
		Deleted_Stock,
		Map_Stock);
	readDatPurchase(
		datFilePur,
		Deleted_Purchase);
}
#endif