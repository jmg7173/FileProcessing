#include "idxtest.h"
#include "../utils/strings.h"

void checkidx() {
	FILE* fp = fopen(idxFileMem, "r");
	if (!fp) {
		//makeidx();
	}
	fp = fopen(idxFileMem, "r");
	// Do something
	fclose(fp);

	fp = fopen(idxFileStock, "r");
	if (!fp) {
		//makeidx();
	}
	fp = fopen(idxFileStock, "r");
	// Do something
	fclose(fp);
}