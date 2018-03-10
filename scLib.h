#ifndef SCLIB_H
#define SCLIB_H

#define MEM_COUNT 100
#define COM_COUNT 38

#define F_BOUNDS 1
#define F_WRONG_COM 2

#define ENCODE 127

int memArr[MEM_COUNT];
int comArr[COM_COUNT];
int REG, accumValue, opCounter, operand, command, memoryPointer;

int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int*);
int sc_memorySave(char*);
int sc_memoryLoad(char*);
int sc_regInit();
int sc_regSet(int, int);
int sc_regGet(int, int*);
int sc_commandEncode(int, int, int*);
int sc_commandDecode(int, int*, int*);

void printMem();

#endif