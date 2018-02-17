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

int sc_regInit() {
	REG = 0;

	return 0;
}

int sc_memorySet(int address, int value) {
	if (address < 0 || address > MEM_COUNT) {
		sc_regSet(F_BOUNDS, 1);

		return -1;
	}

	memArr[address] = value;
	sc_regSet(F_BOUNDS, 0);

	return 0;
}

int sc_memoryGet(int address, int *value) {
	if (address < 0 || address > MEM_COUNT) {
		sc_regSet(F_BOUNDS, 1);

		return -1;
	}

	*value = memArr[address];
	sc_regSet(F_BOUNDS, 0);

	return 0;
}

int sc_memorySave(char *fName) {
	FILE *file = fopen(fName, "wb");

	fwrite(memArr, MEM_COUNT, sizeof(memArr[0]), file);
	fclose(file);

	return 0;
}

int sc_memoryLoad(char *fName) {
	FILE *file = fopen(fName, "rb");

	if (!file)
		return -1;

	fread(memArr, MEM_COUNT, sizeof(memArr[0]), file);
	fclose(file);

	return 0;
}

int sc_regSet(int regFlag, int value) {
	if (value < 0 || value > 1 || regFlag < 1 || regFlag > 2) //ADD MORE FLAGS
		return -1;
	
	if (value == 1)
		REG = REG | (1 << (regFlag -1));
	else
		REG = REG & (~(1 << (regFlag - 1)));

	return 0;
}

int sc_regGet(int regFlag, int *value) {
	if (regFlag < 0 || regFlag > 2)
		return -1;

	*value = (REG >> (regFlag -1)) & 0x1;
		
	return 0;
}

int sc_commandEncode(int command, int operand, int *value) {
	int i;
	for (i = 0; i < COM_COUNT; i++) {
		if (command == comArr[i]) {
			*value = command << 4 | (operand & ENCODE);
			sc_regSet(F_WRONG_COM, 0);
			return 0;
		}
	}

	sc_regSet(F_WRONG_COM, 1);
	return -1;
}

int sc_commandDecode(int value, int *command, int* operand) {
	if (value == NULL || command == NULL || operand == NULL) {
		sc_regSet(F_WRONG_COM, 1);

		return -1;
	}

	*operand = value & ENCODE;
	*command = value >> 4;

	return 0;
}

void printMem() {
	int i, lineDrop = 1;
	for (i = 0; i < MEM_COUNT; i++) {
		printf("%04X ", memArr[i]);
		if (lineDrop % 10 == 0) printf("\n");
		lineDrop++;
	}
}