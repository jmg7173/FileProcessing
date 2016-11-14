#include <string>
#include <iostream>
#include <stdlib.h>

#include "testutils/modetest.h"
#include "testutils/idxtest.h"
#include "utils/rwdata.h"



using namespace std;

int main() {
	int selectNum;
	int status;
	cout << "Constructing datas..." << endl;
	
	constructDatas();
	constructAdmins();
	checkidx();	
	
	cout << "Data construct finished!" << endl;
	
	system("cls");
	
	while (true) {
		status = 0;
		cout << FirstScreen << ">> ";
		cin >> selectNum;
		fflush(stdin);
		switch (selectNum) {
		case 1:
			system("cls");
			login();
			break;
		case 2:
		default:
			return 0;
		}
	}
	return 0;
}