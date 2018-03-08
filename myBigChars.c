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

int bc_printBigChar(int big[2], int x, int y, enum Color fgColor, enum Color bgColor) {
	int i, j, temp, pointer = 0;
	mt_gotoXY(x, y);
    mt_setfgColor(fgColor);
    mt_setbgColor(bgColor);

    for (i = 0; i < 64; i += 8) {
        if (i == 32) pointer++;
        temp = big[pointer] >> i;
        for (j = 7; j >= 0; --j) {
            if (temp >> j & 0x1)
                bc_printA("a");
            else
                bc_printA(" ");
        }
        x++;
        mt_gotoXY(x, y);
	}

	return 0;
}