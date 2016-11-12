// iobuffer.cc

#include "iobuffer.h"
#include <string.h>

IOBuffer::IOBuffer (int maxBytes)
// construct with a maximum of maxFields
{
	Init (maxBytes);
}

IOBuffer & IOBuffer :: operator = (const IOBuffer & buffer)
{
	if (MaxBytes < buffer . BufferSize) return *this; // fails
	Initialized = buffer . Initialized;
	BufferSize = buffer . BufferSize;
	SkipSize = buffer.SkipSize;
	memcpy (Buffer, buffer.Buffer, buffer . BufferSize);
	NextByte = buffer . NextByte;
	Packing = Packing;
	return *this;
}

void IOBuffer::Clear ()
// clear field values from buffer
{
	NextByte = 0;
	Packing = TRUE;
}

void IOBuffer::Print (ostream & stream) const
{
	stream<<"MaxBytes "<<MaxBytes<<" BufferSize "<<BufferSize;
}

int IOBuffer::Init (int maxBytes)
{
	Initialized = FALSE;
	if (maxBytes < 0) maxBytes = 0;
	MaxBytes = maxBytes;
	Buffer = new char[MaxBytes];
	BufferSize = 0;
	SkipSize = 0;
	Clear ();
	return 1;
}

int IOBuffer::PackedLength() {
	return BufferSize;
}

int IOBuffer::DRead (istream & stream, int recref)
// read specified record
{
	unsigned char tmp, tmp2;
	stream . seekg (recref, ios::beg);
	if ((int)stream . tellg () != recref) return -1;
	return Read (stream, tmp, tmp2);
}

int IOBuffer::DWrite (ostream & stream, int recref, int skip) const
// write specified record
{
	stream . seekp (recref, ios::beg);
	if ((int)stream . tellp () != recref) return -1;
	return Write (stream, skip);
}

int IOBuffer::DDelete(ostream & stream, int recref, int skip) const
{
	stream.seekp(recref, ios::beg);
	if ((int)stream.tellp() != recref) return -1;
	return Delete(stream, skip);
}

static const char * headerStr = "IOBuffer";
//static const int headerSize = strlen (headerStr);
static const int headerSize = 8;

int IOBuffer::ReadHeader (istream & stream) 
{
	char str[headerSize+1];
	stream . seekg (0, ios::beg);
	stream . read (str, headerSize);
	if (! stream . good ()) return -1;
	if (strncmp (str, headerStr, headerSize)==0) return headerSize;
	else return -1;
}

int IOBuffer::WriteHeader (ostream & stream) const
{
	stream . seekp (0, ios::beg);
	stream . write (headerStr, headerSize);
	if (! stream . good ()) return -1;
	return headerSize;
}

