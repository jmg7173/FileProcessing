#ifndef PURCHASE_H_
#define PURCHASE_H_ 

#include <string>
#include <iostream>
#include "../utils/delim.h"

using namespace std;

#define LEN_PURID 16
#define LEN_STOCKID 12

class Purchase{
	private:
		char purchaseID[LEN_PURID+1];
		char stockID[LEN_STOCKID+1];
		string memberID;
		short quantity;

	public:
		// Constructor
		Purchase() { purchaseID[0] = '\0'; }
		Purchase(
				const char* purchaseID, 
				const char* stockID, 
				const string memberID, 
				const short quantity
				);
		
		// Getter
		char* getPurchaseID(void){return purchaseID;}
		char* getStockID(void){return stockID;}
		string getMemberID(void){return memberID;}
		short getQuantity(void){return quantity;}

		// Setter
		void setPurchaseID(const char* newID){
			memcpy(purchaseID, newID, LEN_PURID); purchaseID[LEN_PURID] = '\0';}
		void setStockID(const char* newID){
			memcpy(stockID, newID, LEN_STOCKID); stockID[LEN_STOCKID] = '\0';}
		void setMemberID(const string newID){memberID = newID;}
		void setQuantity(const short newQuantity){quantity = newQuantity;}

		// Member function
		bool Pack(IOBuffer & Buffer, int EraseOption=0) const;
		bool Unpack(IOBuffer &);
		bool isEmpty(void) const { return string(purchaseID).empty(); }

		// Operator overloading
		Purchase& operator=(const Purchase &operand);
		bool operator==(const Purchase &operand);
		bool operator!=(const Purchase &operand);

		// I/O stream overloading
		friend istream& operator>>(istream& is, Purchase& p);
		friend ostream& operator<<(ostream& os, Purchase& p);
};
#endif