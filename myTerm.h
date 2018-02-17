#ifndef MYTERM_H
#define MYTERM_H

enum Color {BLACK, WHITE, GREEN, RED};

int mt_clrscr();
int mt_gotoXY(int, int);
int mt_getScreenSize(int*, int*);
int mt_setfgColor(enum Color);
int mt_setbgColor(enum Color);

#endif