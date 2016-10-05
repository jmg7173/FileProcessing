#ifndef RECFILE_H
#define RECFILE_H

#include "buffile.h"
#include "iobuffer.h"
// template class to support direct read and write of records
// The template parameter RecType must support the following
//	int Pack (BufferType &); pack record into buffer
//	int Unpack (BufferType &); unpack record from buffer

template <class RecType>
class RecordFile: public BufferFile
{public:
	int Read (RecType & record, unsigned char& bufSize, unsigned char& skipSize, int recaddr = -1);
	int Write (const RecType & record, int recaddr = -1, int skip = 0);
	int Append (const RecType & record, int recaddr = -1);
	RecordFile (IOBuffer & buffer): BufferFile (buffer) {}
};

// template method bodies
template <class RecType>
int RecordFile<RecType>::Read (RecType & record, unsigned char& bufSize, unsigned char& skipSize, int recaddr = -1)
{
	int readAddr, result;
	readAddr = BufferFile::Read (bufSize, skipSize, recaddr);
	if (readAddr==-1) return -1;
	if (!bufSize) return readAddr;
	result = record . Unpack (Buffer);
	if (!result) return -1;
	return readAddr;
}

template <class RecType>
int RecordFile<RecType>::Write (const RecType & record, int recaddr = -1, int skip = 0)
{
	int result;
	if (record.isEmpty()) {
		record.Pack(Buffer, 1);
		return BufferFile::Write(recaddr, skip);
	}
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Write (recaddr,skip);
}

template <class RecType>
int RecordFile<RecType>::Append (const RecType & record, int recaddr = -1)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Append ();
}

#endif