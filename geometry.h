#ifndef GEOMETRY_H
#define GEOMETRY_H

#define FIRST_DIV 63
#define SECOND_DIV 1023

typedef struct CHS {
	int cyls;
	int heads;
	int sectors;

	int sectorSize;
	int recoveryNumber;
} tCHS;

typedef struct LBA {
	int sectorSize;
	int sectors;
} tLBA;

int g_lba2chs(tLBA, tCHS *);
int g_chs2lba(tCHS, tLBA *);

int chs_printData(tCHS);
#endif