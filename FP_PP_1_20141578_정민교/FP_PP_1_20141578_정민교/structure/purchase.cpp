#include "purchase.h"
#include <sstream>

using namespace std;

Purchase::Purchase(
	const char* purchaseID,
	const char* stockID,
	const string memberID,
	const short quantity
)
	: memberID(memberID),
	quantity(quantity)
{
	setPurchaseID(purchaseID);
	setStockID(stockID);
}

Purchase& Purchase::operator=(const Purchase &operand) {
	setPurchaseID(operand.purchaseID);
	setStockID(operand.stockID);
	memberID = operand.memberID;
	quantity = operand.quantity;
	return *this;
}

bool Purchase::operator==(const Purchase &operand) {
	return !memcmp(purchaseID, operand.purchaseID, LEN_PURID);
}

bool Purchase::operator!=(const Purchase &operand) {
	return 0 != memcmp(purchaseID, operand.purchaseID, LEN_PURID);
}

istream& operator >> (istream& is, Purchase& p) {
	string str;

	getline(is, str);

	istringstream iss(str);
	string token;

	getline(iss, token, '|');
	p.setPurchaseID(token.data());

	getline(iss, token, '|');
	p.setStockID(token.data());

	getline(iss, token, '|');
	p.setMemberID(token);

	getline(iss, token, '|');
	p.setQuantity(stoi(token));

	return is;
}

ostream& operator<<(ostream& os, Purchase& p) {
	os << "PURCHASE ID : " << p.purchaseID << endl;
	os << "STOCK ID : " << p.stockID << endl;
	os << "MEMBER ID : " << p.memberID << endl;
	os << "QUANTITY : " << p.quantity << endl;
	return os;
}

bool Purchase::Pack(IOBuffer& Buffer, int EraseOption) const {
	int numBytes;

	Buffer.Clear();
	if (EraseOption) {
		Buffer.Pack("");
		return true;
	}
	string p_pid(purchaseID, LEN_PURID+1);
	string p_sid(stockID, LEN_STOCKID+1);

	numBytes = Buffer.Pack(p_pid.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(p_sid.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(memberID.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(to_string(quantity).c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Purchase::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[MAXBUF];

	numBytes = Buffer.Unpack(purchaseID, LEN_PURID+1);
	if (numBytes == -1) return false;
	numBytes = Buffer.Unpack(stockID, LEN_STOCKID+1);
	if (numBytes == -1) return false;
	
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	memberID = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	string:: size_type sz;
	quantity = stoi(buf, &sz);
	if (strlen(buf) > sz) return false;
	if (quantity < 0 || quantity > 99) return false;

	return true;
}