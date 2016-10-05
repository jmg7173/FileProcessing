#ifndef MODIFY_H_
#define MODIFY_H_

#include "../structure/dataset.h"

extern vector< pair<int, int> > Deleted_Member;
extern vector< pair<int, int> > Deleted_Stock;
extern vector< pair<int, int> > Deleted_Purchase;

extern map<string, pair<int, int> > Map_Member;
extern map<string, pair<int, int> > Map_Stock;
extern map<string, pair<int, int> > Map_Purchase_PID;
extern map<string, vector<pair<int, int> > > Map_Purchase_MID;
extern map<string, vector<pair<int, int> > > Map_Purchase_SID;

/* If Member's ID change, update it to Purchase.
 * If Stock's ID change, update it to Purchase.(never changes)
 * If Purchase's PID change, nothing to update.
 * If Purchase's MID change, check if new MID exists in member DB.
 * If Purchase's SID chagne, check if new SID exists in stock DB.
 * If Every ID changes, check if it is in use.
 */

bool PurModifyData(Purchase newP, Purchase prevP);

bool ModifyMember() {
	string prevID;
	int recaddr;
	cout << "Input ID >> ";
	getline(cin, prevID);
	pair<int, int> prevInfo = SearchFromMap<Member>(Map_Member, prevID);
	recaddr = prevInfo.first;
	if (recaddr == -1) {
		cout << "Doesn't exist ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}

	else {
		Member prevM = readSpecificDat<Member>(datFileMem, recaddr);
		Member newM = prevM;
		cout << "Modify this record." << endl;
		cout << prevM << endl;
		cout << "Press enter." << endl;
		cin.get();

		int selectNum;
		string id, name, ph, addr, email;
		int birth;

		cout << ModifyMemberMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1: {// ID
				cout << "Input ID >> ";
				getline(cin, id);
				pair<int, int> ptmp = SearchFromMap<Member>(Map_Member, id);
				if (ptmp.first != -1) {
					cout << "Already exist ID" << endl;
					cout << "Press any key to return Shopping menu.";
					cin.get();
					return false;
				}
				newM.setID(id);
				break;
			}
		case 2: // Name
			cout << "Input name >> ";
			getline(cin, name);
			if (name.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newM.setName(name);
			break;
		case 3: // P.H.
			cout << "Input P.H. >> ";
			getline(cin, ph);
			if (ph.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newM.setPH(ph);
			break;
		case 4: // Addr
			cout << "Input addr >> ";
			getline(cin, addr);
			if (addr.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newM.setAddr(addr);
			break;
		case 5: // Birth
			cout << "Input birth >> ";
			cin >> birth;
			cin.get();
			if (birth > 21000000 || birth < 18000000) {
				cout << "Invalid birthday" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newM.setBirth(birth);
			break;
		case 6: // E-mail
			cout << "Input E-mail >> ";
			getline(cin, email);
			if (email.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newM.setEmail(email);
		case 7: // Exit
		default:
			return true;
		}

		DelimFieldBuffer buffer('|', MAXBUF);
		if (!(newM.Pack(buffer))) {
			cout << "Invalid information" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		int bufSize = buffer.PackedLength();
		int totalSize = prevInfo.second;
		
		if (newM.getID() != prevM.getID()) {
			// update info to Purchase
			vector<pair<int, int> > addrs = SearchFromMapAll(Map_Purchase_MID, prevM.getID());
			if (!addrs.empty()) {
				for (pair<int, int> i : addrs) {
					Purchase prevP = readSpecificDat<Purchase>(datFilePur, i.first);
					Purchase newP = prevP;
					newP.setMemberID(newM.getID());
					cout << newP.getMemberID();
					PurModifyData(newP, prevP);
					// Call function
				}
			}
			Map_Member.erase(prevM.getID());
		}
		
		if (bufSize <= prevInfo.second) {
			writeSpecificDat<Member>(datFileMem, newM, recaddr, totalSize - bufSize);
		}
		else {
			recaddr = -1;
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
				if (!MemberFile.Open(datFileMem.c_str(), ios::out)) {
					cout << "File write error!" << endl;
					cout << "Press any key to return Shopping menu.";
					cin.get();
					return false;
				}
				recaddr = MemberFile.Append(newM);
				Map_Member[newM.getID()] = make_pair(recaddr, totalSize = bufSize);
			}
			else {
				writeSpecificDat<Member>(datFileMem.c_str(), newM, recaddr, totalSize - bufSize);
				Map_Member[newM.getID()] = make_pair(recaddr, totalSize);
			}
		}
		Map_Member[newM.getID()] = make_pair(recaddr, totalSize);
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return true;
	}
}

bool ModifyStock() {	
	char prevID[LEN_STOCKID + 1];
	long long int tmpid;
	int recaddr;
	cout << "Input ID(Under Numeric 12character) >> ";
	cin >> tmpid;
	cin.get();
	sprintf(prevID, "%012lld", tmpid);
	prevID[LEN_STOCKID] = '\0';
	
	pair<int, int> prevInfo = SearchFromMap<Stock>(Map_Stock, prevID);
	recaddr = prevInfo.first;
	if (recaddr == -1) {
		cout << "Doesn't exist ID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}

	else {
		Stock prevS = readSpecificDat<Stock>(datFileStock, recaddr);
		Stock newS = prevS;
		cout << "Modify this record." << endl;
		cout << prevS << endl;
		cout << "Press enter." << endl;
		cin.get();

		int selectNum;
		string category, material, price, wash, size;
		int stock;

		cout << ModifyStockMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1: // Category
			cout << "Input category >> ";
			getline(cin, category);
			if (category.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newS.setCategory(category);
			break;
		case 2: // Material
			cout << "Input material >> ";
			getline(cin, material);
			if (material.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newS.setCategory(material);
			break;
		case 3: {// Price
				int pricetmp;
				cout << "Input Price(integer format) >> ";
				cin >> pricetmp;
				cin.get();
				if (pricetmp >= 100000 || pricetmp <= 0) {
					cout << "Invalid price" << endl;
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
				newS.setPrice(price);
				break;
			}
		case 4: // Stock
			cout << "Input stock >> ";
			cin >> stock;
			cin.get();
			if (stock > 65535 || stock < 0) {
				cout << "Invalid stock" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newS.setStock((short)stock);
			break;
		case 5: // Washing Method
			cout << "Input washing method >> ";
			getline(cin, wash);
			if (wash.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newS.setCategory(wash);
			break;
		case 6: // Size
			cout << "Input size(one of S, M, L, XL) >> ";
			getline(cin, size);
			if (size.empty()) {
				cout << "Empty input!" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			newS.setSize(size);
		case 7: // Exit
		default:
			return true;
		}

		DelimFieldBuffer buffer('|', MAXBUF);
		if (!(newS.Pack(buffer))) {
			cout << "Invalid information" << endl;
			cout << "Press any key to return Shopping menu.";
			cin.get();
			return false;
		}
		int bufSize = buffer.PackedLength();
		int totalSize = prevInfo.second;

		if (bufSize <= prevInfo.second) {
			writeSpecificDat<Stock>(datFileStock, newS, recaddr, totalSize - bufSize);
		}
		else {
			recaddr = -1;
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
				recaddr = StockFile.Append(newS);
				Map_Stock[newS.getID()] = make_pair(recaddr, bufSize);
			}
			else {
				writeSpecificDat<Stock>(datFileStock.c_str(), newS, recaddr, totalSize - bufSize);
				Map_Stock[newS.getID()] = make_pair(recaddr, totalSize);
			}
		}
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return true;
	}
}

bool ModifyPurchase() {
	char purchaseID[LEN_PURID + 1] = "\0";
	long long int tmpid;
	int recaddr;
	cout << "Input ID(Under Numeric 16character) >> ";
	cin >> tmpid;
	cin.get();

	sprintf(purchaseID, "%016lld", tmpid);
	purchaseID[LEN_PURID] = '\0';

	pair<int, int> prevInfo = SearchFromMap<Purchase>(Map_Purchase_PID, purchaseID);
	recaddr = prevInfo.first;
	if (recaddr == -1) {
		cout << "Doesn't exist PurchaseID" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}

	else {
		Purchase prevP = readSpecificDat<Purchase>(datFilePur, recaddr);
		Purchase newP = prevP;
		cout << "Modify this record." << endl;
		cout << prevP << endl;
		cout << "Press enter." << endl;
		cin.get();

		int selectNum;
		char stockID[LEN_STOCKID + 1] = "\0";
		string memberID;
		int quantity;

		cout << ModifyPurchaseMenu << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1: // StockID
			cout << "Input stockID(Under Numeric 12character) >> ";
			cin >> tmpid;
			cin.get();
			sprintf(stockID, "%012lld", tmpid);
			stockID[LEN_STOCKID] = '\0';
			if (!strlen(stockID)) {
				cout << "Empty input!" << endl;
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
			newP.setStockID(stockID);
			break;
		case 2: // Member
			cout << "Input memberID >> ";
			getline(cin, memberID);
			if (memberID.empty()) {
				cout << "Empty input!" << endl;
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
			newP.setMemberID(memberID);
			break;
		case 3: 
			cout << "Input quantity >> ";
			cin >> quantity;
			cin.get();
			if (quantity > 65535 || quantity < 0) {
				cout << "Invalid quantity" << endl;
				cout << "Press any key to return Shopping menu.";
				cin.get();
				return false;
			}
			break;
		case 4: // Exit
		default:
			return true;
		}

		PurModifyData(newP, prevP);
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return true;
	}
}

bool PurModifyData(Purchase newP, Purchase prevP) {
	// get previous recaddr and bufsize
	// decide if just change data or delete and make new data
	pair<int, int> prevInfo = SearchFromMap<Purchase>(Map_Purchase_PID, prevP.getPurchaseID());
	int prevRecaddr = prevInfo.first;
	int newRecaddr = -1;
	int totalSize = prevInfo.second;

	DelimFieldBuffer buffer('|', MAXBUF);
	if (!(newP.Pack(buffer))) {
		cout << "Invalid information" << endl;
		cout << "Press any key to return Shopping menu.";
		cin.get();
		return false;
	}
	int bufSize = buffer.PackedLength();

	// If can modify in original position
	if (bufSize <= prevInfo.second)
		writeSpecificDat<Purchase>(datFilePur, newP, newRecaddr = prevRecaddr, totalSize - bufSize);

	// If can't modify in original position
	else {
		// find new recaddr
		for (unsigned int i = 0; i < Deleted_Purchase.size(); i++) {
			if (Deleted_Purchase[i].second >= bufSize) {
				newRecaddr = Deleted_Purchase[i].first;
				totalSize = Deleted_Purchase[i].second;
				Deleted_Purchase.erase(Deleted_Purchase.begin() + i);
				break;
			}
		}

		// If there is no space for reusing.
		if (newRecaddr == -1) {
			RecordFile <Purchase> PurchaseFile(buffer);
			if (!PurchaseFile.Open(datFilePur.c_str(), ios::out)) {
				cout << "File write error!" << endl;
				return false;
			}
			totalSize = bufSize;
			newRecaddr = PurchaseFile.Append(newP);
			// update PID
			Map_Purchase_PID[newP.getPurchaseID()] = make_pair(newRecaddr, bufSize);
		}

		// If there is space for reusing.
		else {
			writeSpecificDat<Purchase>(datFilePur.c_str(), newP, newRecaddr, totalSize - bufSize);
			Map_Purchase_PID[newP.getPurchaseID()] = make_pair(newRecaddr, totalSize);
		}
	}

	// modify Map_MID
	if (newP.getMemberID() != prevP.getMemberID()) {
		{
			vector<pair<int, int> >& addrs = Map_Purchase_MID[prevP.getMemberID()];
			for (unsigned int i = 0; i < addrs.size(); i++) {
				if (addrs[i].first == prevRecaddr) {
					addrs.erase(addrs.begin() + i);
					break;
				}
			}
			Map_Purchase_MID[newP.getMemberID()].push_back(make_pair(newRecaddr, totalSize));
		}
		{
			vector<pair<int, int> >& addrs = Map_Purchase_SID[prevP.getStockID()];
			for (unsigned int i = 0; i < addrs.size(); i++) {
				if (addrs[i].first == prevRecaddr) {
					addrs[i].first = newRecaddr;
					addrs[i].second = totalSize;
					break;
				}
			}
		}
		// Erase prev MAP_MID data(only one element) and insert new MAP_MID data
	}

	// modify Map_SID
	if (newP.getStockID() != prevP.getStockID()) {
		vector<pair<int, int> >& addrs = Map_Purchase_SID[prevP.getStockID()];
		for (unsigned int i = 0; i < addrs.size(); i++) {
			if (addrs[i].first == prevRecaddr) {
				addrs.erase(addrs.begin() + i);
				break;
			}
		}
		Map_Purchase_SID[newP.getStockID()].push_back(make_pair(newRecaddr, totalSize));
	}

	// modify Map_MID, Map_SID if recaddr changed.
	if (newP.getQuantity() != prevP.getQuantity()) {
		if (newRecaddr != prevRecaddr) {
			vector<pair<int, int> >& addrs = Map_Purchase_MID[prevP.getMemberID()];
			for (unsigned int i = 0; i < addrs.size(); i++) {
				if (addrs[i].first == prevRecaddr) {
					addrs[i].first = newRecaddr;
					addrs[i].second = totalSize;
					break;
				}
			}
		}
		{
			vector<pair<int, int> >& addrs = Map_Purchase_SID[prevP.getStockID()];
			for (unsigned int i = 0; i < addrs.size(); i++) {
				if (addrs[i].first == prevRecaddr) {
					addrs[i].first = newRecaddr;
					addrs[i].second = totalSize;
					break;
				}
			}
		}
	}
	return true;
}
#endif
