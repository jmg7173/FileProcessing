#ifndef DELETE_H_
#define DELETE_H_

#include "../utils/strings.h"
#include "../structure/dataset.h"
#include "search.h"

extern vector< pair<int, int> > Deleted_Member;
extern vector< pair<int, int> > Deleted_Stock;
extern vector< pair<int, int> > Deleted_Purchase;

extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Stock;
extern map<string, pair<int, int> > Map_Purchase_PID;
extern map<string, vector<pair<int, int> > > Map_Purchase_MID;
extern map<string, vector<pair<int, int> > > Map_Purchase_SID;

inline bool DeleteFromMem();
inline bool DeleteFromStock();
inline bool DeleteFromPurchase();
inline void MemDeleteData(Member m, int recaddr, string id);
inline void StockDeleteData(Stock s, int recaddr, string id);
inline void PurDeleteData(Purchase p, int recaddr, string id);

inline bool DeleteFromMem() {
	string id;
	cout << "Input ID >> ";
	getline(cin, id);
	int recaddr = SearchFromMap<Member>(Map_Member, id).first;

	if (recaddr == -1) {
		cout << "Invalid ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	else {
		Member m = readSpecificDat<Member>(datFileMem, recaddr);
		cout << "Delete this record." << endl;
		cout << m << endl;
		cout << "Press any key to return Shopping menu.";
		MemDeleteData(m, recaddr, id);
		cin.get();
		return true;
	}
}

inline bool DeleteFromStock() {
	char id[LEN_STOCKID + 1];
	long long int tmpid;
	cout << "Input ID(Under Numeric 12character) >> ";
	cin >> tmpid;
	cin.get();

	sprintf(id, "%012lld", tmpid);
	id[LEN_STOCKID] = '\0';

	int recaddr = SearchFromMap<Stock>(Map_Stock, id).first;

	if (recaddr == -1) {
		cout << "Invalid ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	else {
		Stock s = readSpecificDat<Stock>(datFileStock, recaddr);
		cout << "Delete this record." << endl;
		cout << s << endl;
		cout << "Press any key to return Shopping menu.";
		StockDeleteData(s, recaddr, id);
		cin.get();
		return true;
	}
}

inline bool DeleteFromPurchase() {
	char purchaseID[LEN_PURID + 1] = "\0";
	long long int tmpid;
	cout << "Input ID(Under Numeric 16character) >> ";
	cin >> tmpid;
	cin.get();

	sprintf(purchaseID, "%016lld", tmpid);
	purchaseID[LEN_PURID] = '\0';
	int recaddr = SearchFromMap<Purchase>(Map_Purchase_PID, purchaseID).first;

	if (recaddr == -1) {
		cout << "Invalid ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	else {
		Purchase p = readSpecificDat<Purchase>(datFilePur, recaddr);
		cout << "Delete this record." << endl;
		cout << p << endl;
		cout << "Press any key to return Shopping menu.";
		PurDeleteData(p, recaddr, purchaseID);
		cin.get();
		return true;
	}
}

inline void MemDeleteData(Member m, int recaddr, string id) {
	unsigned char bufSize;

	// Erase datas from associated Member's data structure and add at Deleted_Member
	pair<int, int> addr = Map_Member[id];
	Map_Member.erase(id);
	bufSize = addr.second;

	Deleted_Member.push_back(make_pair(recaddr, bufSize));

	writeSpecificDat<Member>(datFileMem, Member(), recaddr, bufSize);
	// Delete from .dat File
	// Also Delete data at Purchase(list_Purchase, recaddr_Purchase, Map_Purchase_PID, Map_Purchase_MID, Map_Purchase_SID)
	vector<pair<int, int> > addrs = SearchFromMapAll(Map_Purchase_MID, id);
	if (!addrs.empty()) {
		vector<pair<Purchase, int> > ps;
		for (pair<int, int> i : addrs) {
			recaddr = i.first;
			bufSize = i.second;
			ps.push_back(make_pair(readSpecificDat<Purchase>(datFilePur, recaddr), recaddr));
			writeSpecificDat<Purchase>(datFilePur, Purchase(), recaddr, bufSize);
			Deleted_Purchase.push_back(make_pair(recaddr, bufSize));
		}
		Map_Purchase_MID.erase(id);
		for (pair<Purchase, int> p : ps) {
			// For SID
			//vector<pair<int, int> > tmps = SearchFromMapAll(Map_Purchase_SID, p.first.getStockID());
			vector<pair<int, int> >& tmps = Map_Purchase_SID[p.first.getStockID()];
			for (unsigned int i = 0; i < tmps.size(); i++) {
				if (tmps[i].first == p.second) {
					tmps.erase(tmps.begin() + i);
					i--;
				}
			}
			// For PID
			Map_Purchase_PID.erase(p.first.getPurchaseID());
		}
	}
}

inline void StockDeleteData(Stock s, int recaddr, string id) {
	unsigned char bufSize;
	// Erase datas from associated Member's data structure and add at Deleted_Member
	pair<int, int> addr = Map_Stock[id];
	Map_Stock.erase(id);
	bufSize = addr.second;

	Deleted_Stock.push_back(make_pair(recaddr, bufSize));

	writeSpecificDat<Stock>(datFileStock, Stock(), recaddr, bufSize);
	// Delete from .dat File
	// Also Delete data at Purchase(list_Purchase, recaddr_Purchase, Map_Purchase_PID, Map_Purchase_MID, Map_Purchase_SID)
	vector<pair<int, int> > addrs = SearchFromMapAll(Map_Purchase_SID, id);
	if (!addrs.empty()) {
		vector<pair<Purchase, int> > ps;
		for (pair<int, int> i : addrs) {
			recaddr = i.first;
			bufSize = i.second;
			ps.push_back(make_pair(readSpecificDat<Purchase>(datFilePur, recaddr), recaddr));
			writeSpecificDat<Purchase>(datFilePur, Purchase(), recaddr, bufSize);
			Deleted_Purchase.push_back(make_pair(recaddr, bufSize));
		}
		Map_Purchase_SID.erase(id);
		for (pair<Purchase, int> p : ps) {
			// For MID
			vector<pair<int, int> > &tmps = Map_Purchase_MID[p.first.getMemberID()];
			for (unsigned int i = 0; i < tmps.size(); i++) {
				if (tmps[i].first == p.second) {
					tmps.erase(tmps.begin() + i);
					i--;
				}
			}
			// For PID
			Map_Purchase_PID.erase(p.first.getPurchaseID());
		}
	}
}

inline void PurDeleteData(Purchase p, int recaddr, string id) {
	unsigned char bufSize;
	// Erase datas from associated Purchase's data structure and add at Deleted_Purchase
	pair<int, int> addr = Map_Purchase_PID[id];
	Map_Purchase_PID.erase(id);
	bufSize = addr.second;

	Deleted_Purchase.push_back(make_pair(recaddr, bufSize));

	writeSpecificDat<Purchase>(datFilePur, Purchase(), recaddr, bufSize);

	// Delete also from _SID, _MID
	{
		vector<pair<int, int> >& addrs = Map_Purchase_MID[p.getMemberID()];
		for (unsigned int i = 0; i < addrs.size(); i++) {
			if (addrs[i].first == recaddr) {
				addrs.erase(addrs.begin() + i);
				break;
			}
		}
	}

	{
		vector<pair<int, int> >& addrs = Map_Purchase_SID[p.getStockID()];
		for (unsigned int i = 0; i < addrs.size(); i++) {
			if (addrs[i].first == recaddr) {
				addrs.erase(addrs.begin() + i);
				break;
			}
		}
	}
}
#endif