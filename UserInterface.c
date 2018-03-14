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
	int term = open(TERM, O_RDWR);
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
	close(term);
}

void displayAccumulator() {
	int term = open(TERM, O_RDWR);
	bc_box(1, 63, 3, 18);
	mt_gotoXY(1, 65);
	printf("ACCUM");
	mt_gotoXY(2, 69);

	if (accumValue >= 0) {printf("+%04X", accumValue); mt_gotoXY(2, 69);}
	else {printf("-%04X", (-1) * accumValue); mt_gotoXY(2, 69);}

	close(term);
	mt_gotoXY(25, 1);
}

void displayCounter() {
	int term = open(TERM, O_RDWR);
	bc_box(4, 63, 3, 18);
	mt_gotoXY(4, 65);
	printf("COUNTER");

	opCounter = memoryPointer;
	mt_gotoXY(5, 69);

	printf("+%04X", opCounter);

	close(term);

	mt_gotoXY(25, 1);
}

void displayOperation() {
	int term = open(TERM, O_RDWR);
	bc_box(7, 63, 3, 18);
	mt_gotoXY(7, 65);
	printf("OPER");
	mt_gotoXY(8, 65);
	sc_memoryGet(memoryPointer, &value);

	close(term);

	mt_gotoXY(25, 1);
}

void displayFlags() {
	int terminal = open(TERM, O_RDWR);

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
    
	mt_gotoXY(25, 1);
}

void displayMenu() {
	int term = open(TERM, O_RDWR);
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

	close(term);

	mt_gotoXY(25, 1);
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

	sprintf(buffer, "+%04X", value);

	int i;
	for (i = 0; i < 5; i++) {
		bc_setBig(BIG, buffer[i]);
		bc_printBigChar(BIG, 14, y, DEFAULT, DEFAULT);
		y += 9;
	}

	mt_gotoXY(25, 1);
}

void signalhandler (int signo)
{
	sc_regGet(F_ISRUN, &flag_key);
	sc_regGet(F_IGNORE_FLAG, &flag_ign);
	
    if (opCounter < 99 && flag_key && !flag_ign) {
		cu();		
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

void clearInput()
{
    int term = open(TERM, O_RDWR);

	int i;
    mt_gotoXY (25, 1);
    for (i = 0; i < 80; ++i)
        write (term, " ", 1);
    mt_gotoXY (25, 1);

    close (term);
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