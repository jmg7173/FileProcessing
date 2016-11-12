#pragma once
#ifndef INDEXUTIL_H_
#define INDEXUTIL_H_

#include "recfile.h"
#include "textind.h"
#include "indfile.h"
#include "buffile.h"
#include <fstream>
#include <vector>

template <class Type>
void createIdxFile(const string idxfile, const string datfile, int size, int LENID);

template <class Type>
void createIdxFile(const string idxfile, const string datfile, int size, int LENID){
	DelimFieldBuffer buffer('|', MAXBUF);
	RecordFile<Type> TypeFile(buffer);
	TextIndex TypeIndex(size);

	TypeFile.Open(datfile.c_str(), ios::in);
	while (true) {
		Type t;
		unsigned char bufSize = 0;
		unsigned char skipSize = 0;
		int recaddr = TypeFile.Read(t, bufSize, skipSize);
		if (recaddr == -1) break;
		if (!bufSize) continue;
		TypeIndex.Insert(t.Key(), recaddr);
		cout << recaddr << '\n' << t;
	}
	TypeFile.Close();
	
	TextIndexBuffer idxbuf(LENID, size);
	BufferFile TypeIdxFile(idxbuf);
	TypeIdxFile.Create(idxfile.c_str(), ios::out | ios::trunc);
	TypeIdxFile.Rewind();
	idxbuf.Pack(TypeIndex);

	int result = TypeIdxFile.Write();
	TypeIdxFile.Close();
}

template <class Type>
void readIdxFile(const string filename, const string id, int size, int LENID) {
	DelimFieldBuffer buf('|', MAXBUF);
	TextIndexedFile<Type> TypeIdxedFile(buf, LENID, size);
	
	TypeIdxedFile.Open(filename.c_str());
	Type t;
	TypeIdxedFile.Read(id, t);
	cout << t;

	TypeIdxedFile.Close();
}

#endif