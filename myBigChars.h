#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#define ENTER_MODE "\E(0"
#define EXIT_MODE "\E(B"

int bc_printA(char*);
int bc_box(int, int, int, int);
int bc_printBigChar(int[2], int, int, enum Color, enum Color);
int bc_setBigCharPos(int*, int, int, int);
int bc_getBigCharPos(int*, int, int, int*);
int bc_bigCharWrite(int, int*, int);
int bc_bigCharRead(int, int*, int, int*);
#endif