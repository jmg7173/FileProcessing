#ifndef USER_H_
#define USER_H_

#include "../structure/dataset.h"
#include "../testutils/strings.h"
#include "../utils/strings.h"

#ifndef SEARCH_H_
#include "search.h"
#endif

#ifndef MODIFY_H_
#include "modify.h"
#endif

#ifndef DELETE_H_
#include "delete.h"
#endif

extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Purchase_PID;

bool UserManage(const string id);
void UserPurchaseManage(const string id);
bool InsertMyPurchase(const string id);
bool DeleteMyPurchase(const string id);

bool UserManage(const string id) {
	int selectNum;
	int recaddr = SearchFromMap<Member>(Map_Member, id).first;
	while (true) {
		cout << UserMemberMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1: {
			system("cls");
			Member m = readSpecificDat<Member>(datFileMem, recaddr);
			cout << m << endl;
			break;
		}
		case 2:
			ModifyMemberData(id, recaddr);
			break;
		case 3: {
			Member m = readSpecificDat<Member>(datFileMem, recaddr);
			cout << "Do you really want to delete this account?(Y/N) ";
			char agreed;
			cin >> agreed;
			fflush(stdin);
			if (agreed == 'Y' || agreed == 'y') {
				MemDeleteData(m, recaddr, id);
				cout << "Account deleted successfully!" << endl;
				return true;
			}
			else
				break;
		}
		case 4:
			break;
		}
	}
	return false;
}

void UserPurchaseManage(const string id) {
	int selectNum;
	bool isSuccess;
	while (true) {
		cout << UserPurchaseMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1:
			isSuccess = FindByMID(id);
			if (!isSuccess)
				cout << "No entry" << endl;
			break;
		case 2:
			// InsertMyPurchase
			InsertMyPurchase(id);
			break;
		case 3:
			// DeleteMyPurchase
			DeleteMyPurchase(id);
			break;
		case 4:
			break;
		}
		system("cls");
	}
}

bool InsertMyPurchase(const string id) {
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
		string memberID = id;
		int quantity;

		cout << "Input stockID(Under Numeric 12character) >> ";
		cin >> tmpid;
		cin.get();
		sprintf(stockID, "%012lld", tmpid);

		stockID[LEN_STOCKID] = '\0';

		cout << "Input quantity >> ";
		cin >> quantity;
		cin.get();

		if (!strlen(purchaseID) ||
			!strlen(stockID) ||
			memberID.empty()) {
			cout << "There is empty instance" << endl;
			cout << "Press any key to return User Manage Menu.";
			cin.get();
			return false;
		}

		if (SearchFromMap<Stock>(Map_Stock, stockID).first == -1) {
			cout << "Doesn't exist stockID at stock DB" << endl;
			cout << "Press any key to return User Manage Menu";
			cin.get();
			return false;
		}

		if (quantity > 65535 || quantity < 0) {
			cout << "Invalid quantity" << endl;
			cout << "Press any key to return User Manage Menu.";
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
				cout << "Press any key to return User Manage Menu.";
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
		cout << "Press any key to return User Manage Menu.";
		cin.get();
		return true;
	}
}


bool DeleteMyPurchase(const string id) {
	vector<pair<int, int> >& recaddrs = SearchFromMapAll(Map_Purchase_MID, id);
	int cnt = 0;
	if (recaddrs.empty()) {
		cout << "No entry to delete.";
		cin.get();
		return false;
	}
	else {
		int idx;
		cout << "Choose number to delete.";
		for (pair<int, int> data : recaddrs) {
			Purchase p = readSpecificDat<Purchase>(datFilePur, data.first);
			cout << cnt + 1 << "." << endl;
			cout << p << endl;
			cnt++;
		}
		cout << "<< ";
		cin >> idx;
		fflush(stdin);

		if (idx < 0 || idx > cnt) {
			cout << "Invalid index";
			cin.get();
			return false;
		}
		Purchase p = readSpecificDat<Purchase>(datFilePur, recaddrs[idx - 1].first);
		int recaddr = recaddrs[idx - 1].first;
		PurDeleteData(p, recaddr, p.getPurchaseID());
		cout << "Deleted Successfully";
		cin.get();
		return true;
	}

}
#endif