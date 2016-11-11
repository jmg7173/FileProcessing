#ifndef INSERT_H_
#define INSERT_H_

#include "../structure/dataset.h"
#include <stdio.h>
#include <sstream>

extern vector< pair<int, int> > Deleted_Member;
extern vector< pair<int, int> > Deleted_Stock;
extern vector< pair<int, int> > Deleted_Purchase;

extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Stock;
extern map<string, pair<int, int> > Map_Purchase_PID;
extern map<string, vector<pair<int, int> > > Map_Purchase_MID;
extern map<string, vector<pair<int, int> > > Map_Purchase_SID;

/* Basic idea : "get Primary Key"
 * Check if data has that key
 * If so, reject insert
 * If not, get other instances
 * If instances has more than one blank data, reject
 * If instances filled normally, write at .dat file
 * If there is "blank space", write at blank space.
 * If there is not blank space, append.
 * In case of purchase, also check if instance "memberID"
 * and instance "stockID" is in Stock and Member.
 * Then, if purchase added, apply at Stock's stock(as minus)
 * If Stock class's instance stock is negative, reject.
 */

bool InsertMember() {
	string id;
	cout << "Input ID >> ";
	getline(cin, id);
	pair<int, int> ptmp = SearchFromMap<Member>(Map_Member, id);
	if (ptmp.first != -1) {
		cout << "Already exist ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	else {
		string name, ph, addr, email;
		int birth;
		cout << "Input name >> ";
		getline(cin, name);
		cout << "Input P.H >> ";
		getline(cin, ph);
		cout << "Input addr >> ";
		getline(cin, addr);
		
		cout << "Input birth >> ";
		cin >> birth;
		cin.get();
		
		cout << "Input E-mail >> ";
		getline(cin, email);

		if (id.empty() ||
			name.empty() ||
			ph.empty() ||
			addr.empty() ||
			email.empty()) {
			cout << "There is empty instance" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		if (birth > 21000000 || birth < 18000000) {
			cout << "Invalid birthday" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}

		Member m(id, name, ph, addr, birth, email);
		bool success = AddMemberAsRecord(m);
		if (!success)
			cout << "Error at file write" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return success;
	}
}

bool InsertStock() {
	char id[LEN_STOCKID+1];
	long long int tmpid;
	cout << "Input ID(Under Numeric 12character) >> ";
	cin >> tmpid;
	cin.get();

	sprintf(id, "%012lld", tmpid);
	id[LEN_STOCKID] = '\0';
	pair<int, int> ptmp = SearchFromMap<Stock>(Map_Stock, id);
	if (ptmp.first != -1) {
		cout << "Already exist ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	else {
		string category, material, price, wash, size;
		int pricetmp, stock;

		cout << "Input category >> ";
		getline(cin, category);
		cout << "Input material >> ";
		getline(cin, material);
		
		cout << "Input Price(integer format) >> ";
		cin >> pricetmp;
		cin.get();
		
		cout << "Input stock >> ";
		cin >> stock;
		cin.get();
		
		cout << "Input washing method >> ";
		getline(cin, wash);
		cout << "Input size(one of S, M, L, XL) >> ";
		getline(cin, size);

		if (!strlen(id) ||
			category.empty() ||
			material.empty() ||
			wash.empty() ||
			size.empty()) {
			cout << "There is empty instance" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		if (pricetmp >= 100000 || pricetmp <= 0) {
			cout << "Invalid price" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		if (stock > 65535 || stock < 0) {
			cout << "Invalid stock" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		ostringstream ss;
		if (pricetmp >= 1000) {
			ss << pricetmp / 1000;
			price = ss.str() + ",";
			ss.str("");
			ss.clear();
			if (!(pricetmp % 1000))
				price = price + "000";
			else {
				ss << pricetmp % 1000;
				price = price + ss.str();
			}
			ss.str("");
			ss.clear();
		}
		else {
			ss << pricetmp;
			price = price + ss.str();
			ss.str("");
			ss.clear();
		}


		Stock s(id, category, material, price, (short)stock, wash, size);
		DelimFieldBuffer buffer('|', MAXBUF);
		s.Pack(buffer);
		int bufSize = buffer.PackedLength();
		int totalSize;
		int recaddr = -1;

		for (unsigned int i = 0; i < Deleted_Stock.size(); i++) {
			if (Deleted_Stock[i].second >= bufSize) {
				recaddr = Deleted_Stock[i].first;
				totalSize = Deleted_Stock[i].second;
				Deleted_Stock.erase(Deleted_Stock.begin() + i);
				break;
			}
		}

		if (recaddr == -1) {
			RecordFile <Stock> StockFile(buffer);
			if (!StockFile.Open(datFileStock.c_str(), ios::out)) {
				cout << "File write error!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			recaddr = StockFile.Append(s);
			Map_Stock[id] = make_pair(recaddr, bufSize);
		}
		else {
			writeSpecificDat<Stock>(datFileStock.c_str(), s, recaddr, totalSize - bufSize);
			Map_Stock[id] = make_pair(recaddr, totalSize);
		}
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return true;
	}
}

// TODO
bool InsertPurchase() {
	char purchaseID[LEN_PURID + 1] = "\0";
	long long int tmpid;
	cout << "Input ID(Under Numeric 16character) >> ";
	cin >> tmpid;
	cin.get();

	sprintf(purchaseID, "%016lld", tmpid);
	purchaseID[LEN_PURID] = '\0';
	pair<int, int> ptmp = SearchFromMap<Purchase>(Map_Purchase_PID, purchaseID);
	if (ptmp.first != -1) {
		cout << "Already exist ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	else {
		char stockID[LEN_STOCKID + 1] = "\0";
		string memberID;
		int quantity;

		cout << "Input stockID(Under Numeric 12character) >> ";
		cin >> tmpid;
		cin.get();
		sprintf(stockID, "%012lld", tmpid);

		stockID[LEN_STOCKID] = '\0';

		cout << "Input memberID >> ";
		getline(cin, memberID);

		cout << "Input quantity >> ";
		cin >> quantity;
		cin.get();

		if (!strlen(purchaseID) ||
			!strlen(stockID) ||
			memberID.empty()) {
			cout << "There is empty instance" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}

		if (SearchFromMap<Member>(Map_Member, memberID).first == -1) {
			cout << "Doesn't exist memberID at member DB" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		if (SearchFromMap<Stock>(Map_Stock, stockID).first == -1) {
			cout << "Doesn't exist stockID at stock DB" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}

		if (quantity > 65535 || quantity < 0) {
			cout << "Invalid quantity" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}

		Purchase p(purchaseID, stockID, memberID, quantity);
		DelimFieldBuffer buffer('|', MAXBUF);
		p.Pack(buffer);
		int bufSize = buffer.PackedLength();
		int totalSize;
		int recaddr = -1;

		for (unsigned int i = 0; i < Deleted_Purchase.size(); i++) {
			if (Deleted_Purchase[i].second >= bufSize) {
				recaddr = Deleted_Purchase[i].first;
				totalSize = Deleted_Purchase[i].second;
				Deleted_Purchase.erase(Deleted_Purchase.begin() + i);
				break;
			}
		}

		if (recaddr == -1) {
			RecordFile <Purchase> PurchaseFile(buffer);
			if (!PurchaseFile.Open(datFilePur.c_str(), ios::out)) {
				cout << "File write error!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			recaddr = PurchaseFile.Append(p);
			Map_Purchase_PID[purchaseID] = make_pair(recaddr, bufSize);
			Map_Purchase_MID[memberID].push_back(make_pair(recaddr, bufSize));
			Map_Purchase_SID[stockID].push_back(make_pair(recaddr, bufSize));
		}
		else {
			writeSpecificDat<Purchase>(datFilePur.c_str(), p, recaddr, totalSize - bufSize);
			Map_Purchase_PID[purchaseID] = make_pair(recaddr, bufSize);
			Map_Purchase_MID[memberID].push_back(make_pair(recaddr, bufSize));
			Map_Purchase_SID[stockID].push_back(make_pair(recaddr, bufSize));
		}
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return true;
	}
}

bool AddMemberAsRecord(Member m) {
	DelimFieldBuffer buffer('|', MAXBUF);
	if (!(m.Pack(buffer)))
		return false;

	int bufSize = buffer.PackedLength();
	int totalSize;
	int recaddr = -1;

	for (unsigned int i = 0; i < Deleted_Member.size(); i++) {
		if (Deleted_Member[i].second >= bufSize) {
			recaddr = Deleted_Member[i].first;
			totalSize = Deleted_Member[i].second;
			Deleted_Member.erase(Deleted_Member.begin() + i);
			break;
		}
	}

	if (recaddr == -1) {
		RecordFile <Member> MemberFile(buffer);
		if (!MemberFile.Open(datFileMem.c_str(), ios::out))
			return false;
		recaddr = MemberFile.Append(m);
		Map_Member[m.getID()] = make_pair(recaddr, bufSize);
	}
	else {
		writeSpecificDat<Member>(datFileMem.c_str(), m, recaddr, totalSize - bufSize);
		Map_Member[m.getID()] = make_pair(recaddr, totalSize);
	}
	return true;
}
#endif