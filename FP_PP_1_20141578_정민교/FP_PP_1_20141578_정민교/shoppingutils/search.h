#ifndef SEARCH_H_
#define SEARCH_H_


#include <iostream>
#include <string>
#include "../structure/dataset.h"
#include "../testutils/strings.h"
#include "search.h"

extern map<string, pair<int, int> > Map_Purchase_PID;
extern map<string, vector<pair<int, int> > > Map_Purchase_MID;
extern map<string, vector<pair<int, int> > > Map_Purchase_SID;

template <class Type>
inline bool SearchData(map<string, pair<int, int> > MapType, string filename);

template <class Type>
inline pair<int, int> SearchFromMap(map<string, pair<int, int> > MapType, string key);

inline vector<pair<int, int> > SearchFromMapAll(map<string, vector<pair<int, int> > > MapType, string key);

inline bool SearchDataPurchase();
inline bool FindByPID(const string id);
inline bool FindByMID(const string id);
inline bool FindBySID(const string id);

template <class Type>
inline bool SearchData(map<string, pair<int, int> > MapType, string filename) {
	string id;
	cout << "Input ID >> ";
	getline(cin, id);
	int recaddr = SearchFromMap<Type>(MapType, id).first;

	if (recaddr == -1) {
		cout << "Invalid ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	else {
		// TODO : DREAD
		Type T = readSpecificDat<Type>(filename, recaddr);
		cout << T << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return true;
	}
}

template <class Type>
inline pair<int, int> SearchFromMap(map<string, pair<int, int> > MapType, string key) {
	if (MapType.find(key) == MapType.end())
		return make_pair(-1, -1);
	else
		return MapType[key];
}

inline vector<pair<int, int> > SearchFromMapAll(map<string, vector<pair<int, int> > > MapType, string key) {
	if (MapType.find(key) == MapType.end())
		return vector<pair<int, int> >();
	else
		return MapType[key];
}

inline bool SearchDataPurchase() {
	string id;
	int selectNum;
	bool isSuccess = true;
	cout << PurchaseSearchMenu << "<< ";
	cin >> selectNum;
	cin.get();
	switch (selectNum) {
	case 1:
		system("cls");
		cout << "Input Purchase ID << ";
		getline(cin, id);
		isSuccess = FindByPID(id);
		break;
	case 2:
		system("cls");
		cout << "Input Member ID << ";
		getline(cin, id);
		isSuccess = FindByMID(id);
		break;
	case 3:
		system("cls");
		cout << "Input Stock ID << ";
		getline(cin, id);
		isSuccess = FindBySID(id);
		break;
	case 4:
	default:
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return true;
	}
	if (!isSuccess) {
		cout << "No entry" << endl;
	}
	cout << "Press any key to return Shopping menu.";
	cin.get();
	return isSuccess;
	/*
	getline(cin, id);
	int cnt = 0;
	switch (selectNum) {
	case 1:
		recaddr = SearchFromMap<Purchase>(Map_Purchase_PID, id).first;
		if (recaddr == -1) {
			cout << "Invalid ID" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		else {
			Purchase p = readSpecificDat<Purchase>(datFilePur, recaddr);
			cout << p << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return true;
		}
		break;
	case 2: {
			vector<pair<int, int> >& recaddrs = SearchFromMapAll(Map_Purchase_MID, id);
			if (!recaddrs.empty()) {
				for (pair<int, int> data : recaddrs) {
					Purchase p = readSpecificDat<Purchase>(datFilePur, data.first);
					cout << cnt + 1 << "." << endl;
					cout << p << endl;
					cnt++;
				}
			}
			else {
				cout << "Invalid ID" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			break;
		}
	case 3: {
			vector<pair<int, int> >&recaddrs = SearchFromMapAll(Map_Purchase_SID, id);
			if (!recaddrs.empty()) {
				for (pair<int, int> data : recaddrs) {
					Purchase p = readSpecificDat<Purchase>(datFilePur, data.first);
					cout << cnt + 1 << "." << endl;
					cout << p << endl;
					cnt++;
				}
			}
			else {
				cout << "Invalid ID" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			break;
		}
	}
	cout << "Press any key to return Shopping menu.";
	cin.get();
	return true;*/
}

inline bool FindByPID(const string id) {
	int recaddr = SearchFromMap<Purchase>(Map_Purchase_PID, id).first;
	if (recaddr == -1)
		return false;
	else {
		Purchase p = readSpecificDat<Purchase>(datFilePur, recaddr);
		cout << p << endl;
		return true;
	}
}

inline bool FindByMID(const string id) {
	vector<pair<int, int> >& recaddrs = SearchFromMapAll(Map_Purchase_MID, id);
	int cnt = 0;
	if (!recaddrs.empty()) {
		for (pair<int, int> data : recaddrs) {
			Purchase p = readSpecificDat<Purchase>(datFilePur, data.first);
			cout << cnt + 1 << "." << endl;
			cout << p << endl;
			cnt++;
		}
		return true;
	}
	else 
		return false;
}

inline bool FindBySID(const string id) {
	vector<pair<int, int> >&recaddrs = SearchFromMapAll(Map_Purchase_SID, id);
	int cnt = 0;
	if (!recaddrs.empty()) {
		for (pair<int, int> data : recaddrs) {
			Purchase p = readSpecificDat<Purchase>(datFilePur, data.first);
			cout << cnt + 1 << "." << endl;
			cout << p << endl;
			cnt++;
		}
		return true;
	}
	else
		return false;
}
#endif