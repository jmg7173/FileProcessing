#ifndef STOCK_H_
#define STOCK_H_

#include <string>
#include <iostream>
#include "../utils/delim.h"

using namespace std;

#define LEN_STOCKID 12

class Stock{
	private:
		char id[LEN_STOCKID+1];
		string category;
		string material;
		string price;
		short stock;
		string wash;
		string size;
		string key;

	public:
		// Constructor
		Stock() { id[0] = '\0'; }
		Stock(
				const char* id,
				const string category,
				const string material,
				const string price,
				const short stock,
				const string wash,
				const string size
				);
		
		// Getter
		char* getID(void){return id;}
		string getCategory(void){return category;}
		string getMaterial(void){return material;}
		string getPrice(void){return price;}
		short getStock(void){return stock;}
		string getWash(void){return wash;}
		string getSize(void){return size;}

		// Setter
		void setID(const char* newID) { 
			memcpy(id, newID, LEN_STOCKID); id[LEN_STOCKID] = '\0'; }
		void setCategory(const string newCategory){category = newCategory;}
		void setMaterial(const string newMaterial){material = newMaterial;}
		void setPrice(const string newPrice){price = newPrice;}
		void setStock(const short newStock){stock = newStock;}
		void setWash(const string newWash){wash = newWash;}
		void setSize(const string newSize){size = newSize;}
		
		// Member function
		bool Pack(IOBuffer & Buffer, int EraseOption = 0) const;
		bool Unpack(IOBuffer &);
		bool isEmpty(void) const { return string(id).empty(); }
		char* Key();

		// Operator overloading
		Stock& operator=(const Stock &operand);
		bool operator==(const Stock &operand);
		bool operator!=(const Stock &operand);

		// I/O stream overloading
		friend istream& operator>>(istream& is, Stock& s);
		friend ostream& operator<<(ostream& os, Stock& s);
};

#endif