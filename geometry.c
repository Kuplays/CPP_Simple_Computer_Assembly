#include "geometry.h"

int g_lba2chs(tLBA from, tCHS *into) {
	int sectorCopy = from.sectors;
	int L, H, C;
	L = sectorCopy / FIRST_DIV;
	H = L / SECOND_DIV;

	into->recoveryNumber = H;
	printf("REC: %d\n", into->recoveryNumber);

	if (H < 2) H = 2;
	if (H < 4 && H > 2) H = 4;
	if (H < 8 && H > 4) H = 8;
	if (H < 16 && H > 8) H = 16;
	if (H < 32 && H > 16) H = 32;
	if (H < 64 && H > 32) H = 64;
	if (H < 128 && H > 64) H = 128;
	if (H < 255 && H > 128) H = 255;

	C = L / H;

	into->cyls = C;
	into->heads = H;
	into->sectors = FIRST_DIV;
}

int g_chs2lba(tCHS from, tLBA *into) {
	int  result = from.recoveryNumber * 64449;
	printf("%d\n", result);
}

int chs_printData(tCHS obj) {
	double size = obj.cyls * obj.heads * obj.sectors * obj.sectorSize;
	double mbSize = size / 10e6;
	printf("CYLS: %d\nHEADS: %d\nSECTORS: %d\nSIZE: %f BYTES\nSIZE: %f Mb\nSIZE: %d Gb", 
		obj.cyls, obj.heads, obj.sectors, size, mbSize, size);
}