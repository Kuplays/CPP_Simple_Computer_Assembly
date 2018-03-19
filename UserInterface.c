#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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

		if (memoryPointer == i - 1) mt_setbgColor(RED);
		printf("+%04X ", value);
		mt_setbgColor(DEFAULT);

		if (i % 10 == 0 && i != 0) {k++; mt_gotoXY(k, 2);}
	}

	mt_gotoXY(25, 1);
}

void displayAccumulator() {
	bc_box(1, 63, 3, 18);
	mt_gotoXY(1, 65);
	printf("ACCUM");
	mt_gotoXY(2, 69);

	if (accumValue >= 0) {printf("+%04X", accumValue); mt_gotoXY(2, 69);}
	else {printf("-%04X", (-1) * accumValue); mt_gotoXY(2, 69);}

	mt_gotoXY(25, 1);
}

void displayCounter() {
	bc_box(4, 63, 3, 18);
	mt_gotoXY(4, 65);
	printf("COUNTER");
	opCounter = memoryPointer;
	mt_gotoXY(5, 69);
	printf("+%04X", opCounter);

	mt_gotoXY(25, 1);
}

void displayOperation() {
	int com = 0, oper = 0, val = 0;
	bc_box(7, 63, 3, 18);
	mt_gotoXY(7, 65);
	printf("OPER");
	mt_gotoXY(8, 67);
	sc_memoryGet(memoryPointer, &val);
	if (val != 0) sc_commandDecode(val, &com, &oper);
	printf("+%02d : %02X", com, oper);

	mt_gotoXY(25, 1);
}

void displayFlags() {
	bc_box(10, 63, 3, 18);
	mt_gotoXY(10, 65);
	printf("FLAGS");

	int flagVal;
    mt_gotoXY(11, 65);
	sc_regGet(F_WRONG_COM, &flagVal); if (flagVal == 1) printf("WC"); else printf("");
	mt_gotoXY(11, 68);
	sc_regGet(F_ISRUN, &flagVal); if (flagVal == 1) printf("IR"); else printf("");
	mt_gotoXY(11, 69);
	sc_regGet(F_BOUNDS, &flagVal); if (flagVal == 1) printf("OM"); else printf("");
	mt_gotoXY(11, 70);
	sc_regGet(F_ZERO, &flagVal); if (flagVal == 1) printf("ZE"); else printf("");
    
	mt_gotoXY(25, 1);
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
	printf("T - STEP");
	mt_gotoXY(19, 49);
	printf("I - RESET");
	mt_gotoXY(20, 49);
	printf("F5 - ACCUMULATOR");
	mt_gotoXY(21, 49);
	printf("F6 - COUNTER");

	mt_gotoXY(25, 1);
}

void displayBigCharArea() {
	mt_gotoXY(13, 1);
	char buffer[20];
	int y = 2;
	bc_box(13, 1, 10, 46);
	mt_gotoXY(13, 5);
	printf("BIG CHAR");

	BIG[0] = 0;
	BIG[1] = 0;

	sc_memoryGet(memoryPointer, &value);

	sprintf(buffer, "+%04X", value);

	int i;
	for (i = 0; i < 5; ++i, y += 9) {
		bc_setBig(BIG, buffer[i]);
		bc_printBigChar(BIG, 14, y, DEFAULT, DEFAULT);
	}
	mt_gotoXY(25, 1);
}

void signalhandler (int signo)
{
	sc_regGet(F_ISRUN, &flag_key);
	sc_regGet(F_IGNORE_FLAG, &flag_ign);
	
    if (opCounter < 99 && flag_key && !flag_ign) {
		cu_callBack();		
		showAll();
	} else {		
		sc_regSet(F_ISRUN, 0);
		alarm(0);     
	}
	flag_key = 0;
}

void reset()
{
     sc_memoryInit();
     sc_regInit();
     showAll();
}

void showAll() {
	mt_clrscr();
	displayMemory();
	displayAccumulator();
	displayCounter();
	displayOperation();
	displayFlags();
	displayMenu();
	displayBigCharArea();
	mt_gotoXY(25, 1);
}