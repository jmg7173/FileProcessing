#include "stock.h"
#include <sstream>
#include <stdio.h>

using namespace std;

Stock::Stock(
	const char* id,
	const string category,
	const string material,
	const string price,
	const short stock,
	const string wash,
	const string size
)
	:	category(category),
		material(material),
		price(price),
		stock(stock),
		wash(wash),
		size(size)
{
	setID(id);
}

Stock& Stock::operator=(const Stock &operand) {
	setID(operand.id);
	category = operand.category;
	material = operand.material;
	price = operand.price;
	stock = operand.stock;
	wash = operand.wash;
	size = operand.size;

	return *this;
}

bool Stock::operator==(const Stock &operand) {
	return !memcmp(id, operand.id, LEN_STOCKID);
}

bool Stock::operator!=(const Stock &operand) {
	return 0 != memcmp(id, operand.id, LEN_STOCKID);
}

istream& operator >> (istream& is, Stock& s) {
	string str;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, str);
	}
	catch (istream::failure e) {
		// error
		return is;
	}
	istringstream iss(str);
	string token;

	getline(iss, token, '|');
	s.setID(token.data());

	getline(iss, token, '|');
	s.setCategory(token);

	getline(iss, token, '|');
	s.setMaterial(token);

	getline(iss, token, '|');
	s.setPrice(token);

	getline(iss, token, '|');
	s.setStock(stoi(token));

	getline(iss, token, '|');
	s.setWash(token);

	getline(iss, token, '|');
	s.setSize(token);

	return is;
}

ostream& operator<<(ostream& os, Stock& s) {
	os << "ID : " << s.id << endl;
	os << "CATEGORY : " << s.category << endl;
	os << "MATERIAL : " << s.material << endl;
	os << "PRICE : " << s.price << endl;
	os << "STOCK : " << s.stock << endl;
	os << "WASH : " << s.wash << endl;
	os << "SIZE : " << s.size << endl;
	return os;
}

bool Stock::Pack(IOBuffer& Buffer, int EraseOption) const {
	int numBytes;

	Buffer.Clear();
	
	if (EraseOption) {
		Buffer.Pack("");
		return true;
	}

	string s_id(id, LEN_STOCKID+1);

	numBytes = Buffer.Pack(s_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(category.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(material.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(price.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(to_string(stock).c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(wash.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(size.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Stock::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[MAXBUF];

	numBytes = Buffer.Unpack(id, LEN_STOCKID+1);
	if (numBytes == -1) return false;
	
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	category = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	material = buf;
	

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	price = buf;
	if (price.length() > 6) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	string::size_type sz;
	stock = stoi(buf, &sz);
	if (strlen(buf) > sz) return false;
	if (stock < 0 || stock > 9999) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	wash = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	size = buf;
	if (size.length() > 2) return false;
	if (size != "S" && size != "M" && size != "L" && size != "XL") return false;

	return true;
}

char* Stock::Key() {
	key.assign(id, LEN_STOCKID);
	return (char*)key.c_str();
}