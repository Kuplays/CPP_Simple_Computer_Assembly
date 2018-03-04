#include <stdio.h>
#include <stdlib.h>

#include "scLib.h"
#include "myTerm.h"
#include "myBigChars.h"

int bc_printA(char *str) {
	printf(ENTER_MODE);
	printf(str);
	printf(EXIT_MODE);

	return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
	int i;
	mt_gotoXY(x1, y1);
	bc_printA("l");

	for (i = 0; i < y2 - 2; i++) bc_printA("q");
	
	bc_printA("k");
	for (i = 1; i <= x2 - 2; i++) {
		mt_gotoXY(x1 + i, y1);
		bc_printA("x");
		mt_gotoXY(x1 + i, y1 + y2 - 1);
		bc_printA("x");
	}
	
	mt_gotoXY(x1 + x2 - 1, y1);
	bc_printA("m");
	for (i = 0; i < y2 - 2; i++) bc_printA("q");
		
	bc_printA("j");

	return 0;
}