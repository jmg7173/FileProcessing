// fixlen.h
#ifndef FIXLEN_H
#define FIXLEN_H

#include <stdlib.h>
#include <iostream>
#include "iobuffer.h"

class FixedLengthBuffer: public IOBuffer
// Abstract class designed to support fixed length records
{
   public:
	FixedLengthBuffer (int recordSize = 1000);
	FixedLengthBuffer (const FixedLengthBuffer & buffer); // copy constructor

	void Clear (); // clear values from buffer
	int Read (istream &, unsigned char&, unsigned char&);
	int Write (ostream &, int skip = 0) const;
	int Delete(ostream &, int skip = 0) const;
	//int DRead(istream &, int recref);
	//int DWrite(ostream &, int recref, int skip = 0) const;
	int ReadHeader (istream &); // read header from stream
	int WriteHeader (ostream &) const; // write a header to the stream
	void Print (ostream &) const;
	int SizeOfBuffer () const; // return size of buffer
 protected:
 	int Init (int recordSize);
	int ChangeRecordSize (int recordSize);
};

inline FixedLengthBuffer :: FixedLengthBuffer (const FixedLengthBuffer & buffer)
: IOBuffer (buffer)
{
	Init (buffer . BufferSize);
}

#endif
