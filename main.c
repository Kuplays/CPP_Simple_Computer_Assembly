#include <stdio.h>
#include <stdlib.h>
#include "scLib.h"
#include "myTerm.h"
#include "myBigChars.h"

void showMenu(int, int);

int main() {
	mt_clrscr();
	int big[2];
	bc_setBigCharPos(big, 0, 0, 1);
	bc_setBigCharPos(big, 1, 0, 1);
	bc_setBigCharPos(big, 2, 0, 1);
	bc_setBigCharPos(big, 3, 0, 1);
	bc_setBigCharPos(big, 4, 0, 1);
	bc_setBigCharPos(big, 5, 0, 1);
	bc_setBigCharPos(big, 6, 0, 1);
	bc_setBigCharPos(big, 7, 0, 1);

	bc_setBigCharPos(big, 0, 1, 0);
	bc_setBigCharPos(big, 1, 1, 0);
	bc_setBigCharPos(big, 2, 1, 0);
	bc_setBigCharPos(big, 3, 1, 0);
	bc_setBigCharPos(big, 4, 1, 0);
	bc_setBigCharPos(big, 5, 1, 0);
	bc_setBigCharPos(big, 6, 1, 0);
	bc_setBigCharPos(big, 7, 1, 0);

	bc_setBigCharPos(big, 0, 2, 1);
	bc_setBigCharPos(big, 1, 2, 1);
	bc_setBigCharPos(big, 2, 2, 1);
	bc_setBigCharPos(big, 3, 2, 1);
	bc_setBigCharPos(big, 4, 2, 1);
	bc_setBigCharPos(big, 5, 2, 1);
	bc_setBigCharPos(big, 6, 2, 1);
	bc_setBigCharPos(big, 7, 2, 1);

	bc_setBigCharPos(big, 0, 3, 0);
	bc_setBigCharPos(big, 1, 3, 0);
	bc_setBigCharPos(big, 2, 3, 0);
	bc_setBigCharPos(big, 3, 3, 0);
	bc_setBigCharPos(big, 4, 3, 0);
	bc_setBigCharPos(big, 5, 3, 0);
	bc_setBigCharPos(big, 6, 3, 0);
	bc_setBigCharPos(big, 7, 3, 0);

	bc_setBigCharPos(big, 0, 4, 1);
	bc_setBigCharPos(big, 1, 4, 1);
	bc_setBigCharPos(big, 2, 4, 1);
	bc_setBigCharPos(big, 3, 4, 1);
	bc_setBigCharPos(big, 4, 4, 1);
	bc_setBigCharPos(big, 5, 4, 1);
	bc_setBigCharPos(big, 6, 4, 1);
	bc_setBigCharPos(big, 7, 4, 1);

	bc_setBigCharPos(big, 0, 5, 0);
	bc_setBigCharPos(big, 1, 5, 0);
	bc_setBigCharPos(big, 2, 5, 0);
	bc_setBigCharPos(big, 3, 5, 0);
	bc_setBigCharPos(big, 4, 5, 0);
	bc_setBigCharPos(big, 5, 5, 0);
	bc_setBigCharPos(big, 6, 5, 0);
	bc_setBigCharPos(big, 7, 5, 0);

	bc_setBigCharPos(big, 0, 6, 1);
	bc_setBigCharPos(big, 1, 6, 1);
	bc_setBigCharPos(big, 2, 6, 1);
	bc_setBigCharPos(big, 3, 6, 1);
	bc_setBigCharPos(big, 4, 6, 1);
	bc_setBigCharPos(big, 5, 6, 1);
	bc_setBigCharPos(big, 6, 6, 1);
	bc_setBigCharPos(big, 7, 6, 1);

	bc_setBigCharPos(big, 0, 7, 0);
	bc_setBigCharPos(big, 1, 7, 0);
	bc_setBigCharPos(big, 2, 7, 0);
	bc_setBigCharPos(big, 3, 7, 0);
	bc_setBigCharPos(big, 4, 7, 0);
	bc_setBigCharPos(big, 5, 7, 0);
	bc_setBigCharPos(big, 6, 7, 0);
	bc_setBigCharPos(big, 7, 7, 0);
	bc_printBigChar(big, 1, 1, GREEN, DEFAULT);
	printf(DEFAULT_COLOR);

	// int choice, address = 0, value = 0, x, commandInput = 0, operandInput = 0, resultEncoded = 0, resultDecoded = 0;
	// int memFlag = 0, comFlag = 0;

	// int ROWS, COLS;

	// sc_memoryInit();
	// sc_regInit();
	// mt_getScreenSize(&ROWS, &COLS);
	// while(1) {
	// 	mt_clrscr();
	// 	mt_gotoXY(1, 1);
	// 	printMem();
	// 	sc_regGet(F_BOUNDS, &memFlag);
	// 	sc_regGet(F_WRONG_COM, &comFlag);
	// 	mt_gotoXY(1, COLS - 25);
	// 	printf("FLAGS");
	// 	mt_gotoXY(2, COLS - 25); if (memFlag) {mt_setfgColor(RED); printf("OUT OF MEMORY"); mt_setfgColor(WHITE);}
	// 	mt_gotoXY(3, COLS - 25); if (comFlag) {mt_setfgColor(RED); printf("INCORRECT COMMAND"); mt_setfgColor(WHITE);}
	// 	mt_gotoXY(ROWS - 10, COLS / 2);
	// 	showMenu(ROWS, COLS);
	// 	scanf("%d", &choice);

	// 	switch(choice) {
	// 		case 1:
	// 		{
	// 			mt_clrscr();
	// 			printMem();
	// 			mt_gotoXY(1, COLS - 25);
	// 			printf("FLAGS");
	// 			mt_gotoXY(2, COLS - 25); if (memFlag) {mt_setfgColor(RED); printf("OUT OF MEMORY"); mt_setfgColor(WHITE);}
	// 			mt_gotoXY(3, COLS - 25); if (comFlag) {mt_setfgColor(RED); printf("INCORRECT COMMAND"); mt_setfgColor(WHITE);}
	// 			mt_gotoXY(ROWS - 10, COLS / 2 - 20);
	// 			printf("ENTER COMMAND AND OPERAND: ");
	// 			scanf("%d %d", &commandInput, &operandInput);
	// 			if (sc_commandEncode(commandInput, operandInput, &resultEncoded) == 0) {
	// 				mt_gotoXY(ROWS - 9, COLS / 2 - 20);
	// 				printf("ENCODED COMMAND: %X", resultEncoded);
	// 				mt_gotoXY(ROWS - 8, COLS / 2 - 20);
	// 				printf("ENTER ADDRESS TO STORE: ");
	// 				scanf("%d", &address);
	// 				sc_memorySet(address, resultEncoded);
	// 			}
	// 		}
	// 		break;
	// 		case 2:
	// 		{
	// 			mt_clrscr();
	// 			printMem();
	// 			mt_gotoXY(1, COLS - 25);
	// 			printf("FLAGS");
	// 			mt_gotoXY(2, COLS - 25); if (memFlag) {mt_setfgColor(RED); printf("OUT OF MEMORY"); mt_setfgColor(WHITE);}
	// 			mt_gotoXY(3, COLS - 25); if (comFlag) {mt_setfgColor(RED); printf("INCORRECT COMMAND"); mt_setfgColor(WHITE);}
	// 			mt_gotoXY(ROWS - 10, COLS / 2 - 20);
	// 			printf("ADDRESS TO FETCH COMMAND: ");
	// 			scanf("%d", &address);
	// 			if (sc_memoryGet(address, &resultEncoded) == 0) {
	// 				mt_gotoXY(ROWS - 9, COLS / 2 - 20);
	// 				printf("FETCHED COMMAND: %X", resultEncoded);
	// 				sc_commandDecode(resultEncoded, &commandInput, &operandInput);
	// 				mt_gotoXY(ROWS - 8, COLS / 2 - 20);
	// 				printf("DECODED COMMAND: %d, DECODED OPERAND: %d", commandInput, operandInput);
	// 			}
	// 			scanf("%d", &x);
	// 		}
	// 		break;
	// 		case 3:
	// 		{
	// 			mt_clrscr();
	// 			if (sc_memorySave("mem.dat") == 0) printf("\nSUCCESSFULLY SAVED!\n");
	// 			scanf("%d", &x);
	// 		}
	// 		break;
	// 		case 4:
	// 		{
	// 			mt_clrscr();
	// 			sc_memoryLoad("mem.dat");
	// 		}
	// 		break;
	// 		case 5:
	// 		{
	// 			return 0;
	// 		}
	// 		break;
	// 	}
	// }

}

void showMenu(int ROWS, int COLS) {
	mt_gotoXY(ROWS - 10, COLS / 2 + 20);
	printf("[1]ENCODE COMMAND");
	mt_gotoXY(ROWS - 9, COLS / 2 + 20);
	printf("[2]DECODE COMMAND");
	mt_gotoXY(ROWS - 8, COLS / 2 + 20);
	printf("[3]SAVE");
	mt_gotoXY(ROWS - 7, COLS / 2 + 20);
	printf("[4]LOAD");
	mt_gotoXY(ROWS - 6, COLS / 2 + 20);
	printf("[5]EXIT");
	mt_gotoXY(ROWS - 5, COLS / 2 + 20);
	printf("CHOOSE: ");
}