#ifndef SHOWTEST_H_
#define SHOWTEST_H_

#include <vector>
#include "../utils/recfile.h"
#include "../utils/rwdata.h"

template <class Type>
bool packTest(const string txtname, const string datname) {
	vector<Type> listType;
	readTxt<Type>(txtname, listType);
	writeDat<Type>(datname, listType);
	
	DelimFieldBuffer buffer('|', MAXBUF);
	RecordFile <Type> TypeFile(buffer);
	if (!TypeFile.Open(datname.c_str(), ios::in))
		return false;
	for (int i = 0; i < 10; i++) {
		Type t;
		unsigned char tmp, tmp2;
		TypeFile.Read(t, tmp, tmp2);
		cout << i + 1 << ".\n" << t << endl;
	}

	cout << "Press any key to return menu.";
	cin.get();
	return true;
}

#endif