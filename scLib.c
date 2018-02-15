#include <stdio.h>
#include <stdlib.h>
#include "scLib.h"

int sc_memoryInit() {
	int i;
	for (i = 0; i < MEM_COUNT; i++)
		memArr[i] = 0;

	int tempArr[] = { 10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43, 
					51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
					63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
					75, 76 };

	memcpy(comArr, tempArr, (sizeof(tempArr)));

	return 0;
}

int sc_memorySet(int address, int value) {
	if (address < 0 || address > MEM_COUNT) {
		//sc_regSet(F_BOUNDS, 1);

		return -1;
	}

	memArr[address] = value;

	return 0;
}

int sc_memoryGet(int address, int *value) {
	if (address < 0 || address > MEM_COUNT) {
		//sc_regSet(F_BOUNDS, 1);

		return -1;
	}

	*value = memArr[address];

	return 0;
}

int sc_memorySave(char *fName) {
	FILE *file = fopen(fName, "wb");

	fwrite(memArr, MEM_COUNT, sizeof(memArr), file);
	fclose(file);

	return 0;
}