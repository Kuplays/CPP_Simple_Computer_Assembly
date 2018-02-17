#include <stdio.h>
#include <stdlib.h>
#include "scLib.h"
#include "myTerm.h"

void printMem();

int main() {
	int choice, address = 0, value = 0, x, commandInput = 0, operandInput = 0, resultEncoded = 0, resultDecoded = 0;
	int memFlag = 0, comFlag = 0;
	sc_memoryInit();
	sc_regInit();
	while(1) {
		clear();
		printMem();
		sc_regGet(F_BOUNDS, &memFlag);
		sc_regGet(F_WRONG_COM, &comFlag);
		printf("\nREGISTER FLAGS: OUT OF MEMORY: %d INCORRECT COMMAND: %d", memFlag, comFlag);
		printf("\n[1]ENCODE COMMAND\n[2]DECODE COMMAND\n[3]SAVE\n[4]LOAD\n[5]EXIT\nCHOOSE: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
			{
				clear();
				printMem();
				printf("\nENTER COMMAND AND OPERAND: ");
				scanf("%d %d", &commandInput, &operandInput);
				if (sc_commandEncode(commandInput, operandInput, &resultEncoded) == 0) {
					printf("\nENCODED COMMAND: %X", resultEncoded);
					printf("\nENTER ADDRESS TO STORE: ");
					scanf("%d", &address);
					sc_memorySet(address, resultEncoded);
				}
			}
			break;
			case 2:
			{
				clear();
				printMem();
				printf("\nADDRESS TO FETCH COMMAND: ");
				scanf("%d", &address);
				if (sc_memoryGet(address, &resultEncoded) == 0) {
					printf("\nFETCHED COMMAND: %X", resultEncoded);
					sc_commandDecode(resultEncoded, &commandInput, &operandInput);
					printf("\nDECODED COMMAND: %d, DECODED OPERAND: %d", commandInput, operandInput);
				}
				scanf("%d", &x);
			}
			break;
			case 3:
			{
				clear();
				if (sc_memorySave("mem.dat") == 0) printf("\nSUCCESSFULLY SAVED!\n");
				scanf("%d", &x);
			}
			break;
			case 4:
			{
				clear();
				sc_memoryLoad("mem.dat");
			}
			break;
			case 5:
			{
				return 0;
			}
			break;
		}
	}

}