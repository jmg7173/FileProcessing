#include <cstring>
#include <sstream>
#include "member.h"

using namespace std;
Member::Member(
				string id, 
				string name, 
				string ph, 
				string addr, 
				int birth, 
				string email,
				int level
				) 
	:	id(id),
		name(name),
		ph(ph),
		addr(addr),
		birth(birth),
		email(email),
		level(level)
{}

Member& Member::operator=(const Member &operand){
	id = operand.id;
	name = operand.name;
	ph = operand.ph;
	addr = operand.addr;
	birth = operand.birth;
	email = operand.email;
	return *this;
}

bool Member::operator==(const Member &operand){
	return id == operand.id;
}

bool Member::operator!=(const Member &operand){
	return id != operand.id;
}

istream& operator>>(istream& is, Member& m){
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
	m.setID(token);
	getline(iss, token, '|');
	m.setName(token);
	getline(iss, token, '|');
	m.setPH(token);
	getline(iss, token, '|');
	m.setAddr(token);
	getline(iss, token, '|');
	m.setBirth(stoi(token));
	getline(iss, token, '|');
	m.setEmail(token);

	return is;
}

ostream& operator<<(ostream& os, Member& m){
	os << "ID : " << m.id << endl;
	os << "NAME : " << m.name << endl;
	os << "P.H. : " << m.ph << endl;
	os << "ADDRESS : " << m.addr << endl;
	os << "BIRTHDAY : " << m.birth << endl;
	os << "E-MAIL : " << m.email << endl;
	return os;
}

bool Member::Pack(IOBuffer& Buffer, int EraseOption) const {
	int numBytes;

	Buffer.Clear();
	if (EraseOption) {
		Buffer.Pack("");
		return true;
	}
	numBytes = Buffer.Pack(id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(name.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(ph.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(addr.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(to_string(birth).c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(email.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Member::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[MAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	id = buf;
	
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	name = buf;
	
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	ph = buf;
	
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	addr = buf;
	
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	string::size_type sz;
	birth = stoi(buf, &sz);
	if (strlen(buf) > sz) return false;
	if (birth < 19000000 || birth > 21000000) return false;
	
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	email = buf;

	return true;
}

char* Member::Key() {
	key.assign(id);
	return (char*)key.c_str();
}