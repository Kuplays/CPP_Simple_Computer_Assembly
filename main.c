#include <stdio.h>
#include <stdlib.h>
#include "scLib.h"

int main() {
	sc_memoryInit();
	int i;
	printf("\nMEM ARR TEST: \n");
	for (i = 0; i < MEM_COUNT; i++) {
		printf("%X", memArr[i]);
	}
	printf("COM ARR TEST:\n");
	for (i = 0; i < COM_COUNT; i++) {
		printf("%d ", comArr[i]);
	}
	return 0;
}