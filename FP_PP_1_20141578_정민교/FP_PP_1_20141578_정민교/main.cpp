/*#include "structure/Student.h"
#include "utils/recfile.h"
#include <fstream>
#include <vector>
*/
#include <string>
#include <iostream>
#include <stdlib.h>

#include "testutils/packtest.h"
#include "testutils/shoptest.h"
#include "testutils/showtest.h"
#include "testutils/strings.h"
#include "utils/strings.h"

using namespace std;

int main () {
	int selectNum;

	while (true) {
		cout << intro;
		cout << ">> ";
		cin >> selectNum;
		cin.get();
		switch (selectNum) {
		case 1:
			system("cls");
			showMember();
			break;
		case 2:
			system("cls");
			showStock();
			break;
		case 3:
			system("cls");
			showPurchase();
			break;
		case 4:
			system("cls");
			packTest<Member>(txtFileMem, datFileMem);
			break;
		case 5:
			system("cls");
			packTest<Stock>(txtFileStock, datFileStock);
			break;
		case 6:
			system("cls");
			packTest<Purchase>(txtFilePur, datFilePur);
			break;
		case 7:
			system("cls");
			OnlineShoppingSystem();
			break;
		case 8:
			return 0;
		}
		system("cls");
	}
	return 0;
}