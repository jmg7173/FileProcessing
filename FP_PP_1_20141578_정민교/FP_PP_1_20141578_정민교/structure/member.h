#ifndef MEMBER_H_
#define MEMBER_H_

#include <string>
#include <iostream>
#include "../utils/delim.h"

using namespace std;

#define LEN_MEMID 16

class Member{
	private:
		string id;
		string name;
		string ph;
		string addr;
		int birth;
		string email;
		string key;
		int level;
	public:
		// Constructor
		Member() {}
		Member(
				string id, 
				string name, 
				string ph, 
				string addr, 
				int birth, 
				string email,
				int level = 2
				);
		
		//Getter
		string getID(void){return id;}
		string getName(void){return name;}
		string getAddr(void){return addr;}
		int getBirth(void){return birth;}
		string getEmail(void){return email;}

		// Setter
		void setID(string newID){id = newID;}
		void setName(string newName){name = newName;}
		void setPH(string newPH) { ph = newPH; }
		void setAddr(string newAddr){addr = newAddr;}
		void setBirth(int newBirth){birth = newBirth;}
		void setEmail(string newEmail){email = newEmail;}

		// Member function
		bool Pack(IOBuffer & Buffer, int EraseOption = 0) const;
		bool Unpack(IOBuffer &);
		bool isEmpty(void) const { return id.empty(); }
		char* Key();

		// Operator overloading
		Member& operator=(const Member &operand);
		bool operator==(const Member &operand);
		bool operator!=(const Member &operand);

		// I/O stream overloading
		friend istream& operator>>(istream& is, Member& m);
		friend ostream& operator<<(ostream& os, Member& m);
};

#endif