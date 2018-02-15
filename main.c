#include <stdio.h>
#include <stdlib.h>
#include "scLib.h"

int main() {
	sc_memoryInit();
	int i;
	for (i = 0; i < COM_COUNT; i++) {
		printf("%d ", comArr[i]);
	}
	return 0;
}