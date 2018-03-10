#include <stdlib.h>
#include <stdio.h>

#include "UserInterface.h"
#include "scLib.h"
#include "myTerm.h"
#include "myBigChars.h"

int command, operand, value;

void displayMemory() {
	int k = 2, i;
	bc_box(1, 1, 12, 62);
	mt_gotoXY(1, 5);
	printf("MEMORY");

	mt_gotoXY(2, 2);

	for (i = 1; i <= 100; i++) {
		sc_memoryGet(i - 1, &value);

		sc_commandDecode(value, &command, &operand);

		if (memoryPointer == i - 1) mt_setbgColor(RED);
		printf("+%04X ", value);
		mt_setbgColor(DEFAULT);

		if (i % 10 == 0 && i != 0) {k++; mt_gotoXY(k, 2);}
	}
}

void displayAccumulator() {
	bc_box(1, 63, 3, 18);
	mt_gotoXY(1, 65);
	printf("ACCUM");
	mt_gotoXY(2, 69);

	if (accumValue >= 0) {printf("+%04X", accumValue); mt_gotoXY(2, 69);}
	else {printf("-%04X", (-1) * accumValue); mt_gotoXY(2, 69);}
}

void displayCounter() {
	bc_box(4, 63, 3, 18);
	mt_gotoXY(4, 65);
	printf("COUNTER");

	opCounter = memoryPointer;
	mt_gotoXY(5, 69);

	printf("+%04X", opCounter);
}

void displayOperation() {
	bc_box(7, 63, 3, 18);
	mt_gotoXY(7, 65);
	printf("OPERATION");
	mt_gotoXY(8, 65);
	sc_memoryGet(memoryPointer, &value);

	sc_commandDecode(value, &command, &operand);
	//printf("+%04X", value);
}

void displayFlags() {
	bc_box(10, 63, 3, 18);
	mt_gotoXY(10, 65);
	printf("FLAGS");

	int flagVal;
	sc_regGet(F_BOUNDS, &flagVal);

	if (flagVal == 1) {
		mt_gotoXY(11, 63);
		mt_setfgColor(RED);
		printf("MEM");
		mt_setfgColor(DEFAULT);
	}
}

void displayMenu() {
	bc_box(13, 47, 10, 34);
	mt_gotoXY(13, 49);
	printf("MENU");
	mt_gotoXY(15, 49);
	printf("L - LOAD");
	mt_gotoXY(16, 49);
	printf("S - SAVE");
	mt_gotoXY(17, 49);
	printf("R - RUN");
	mt_gotoXY(18, 49);
	printf("I - RESET");
	mt_gotoXY(19, 49);
	printf("F5 - ACCUMULATOR");
	mt_gotoXY(20, 49);
	printf("F6 - COUNTER");
}

void displayBigCharArea() {
	char buffer[20];
	int y = 2;
	bc_box(13, 1, 10, 46);
	mt_gotoXY(13, 5);
	printf("BIG CHAR");

	BIG[0] = 0;
	BIG[1] = 0;

	sc_memoryGet(memoryPointer, &value);
	sc_commandDecode(value, &command, &operand);

	sprintf(buffer, "+%04X", value);

	int i;
	for (i = 0; i < 5; i++) {
		bc_setBig(BIG, buffer[i]);
		bc_printBigChar(BIG, 14, y, RED, DEFAULT);
		y += 9;
	}
}